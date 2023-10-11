#pragma once
#include "draw.h"
#include <list>
#include <vector>
#include "global.h"
#include <conio.h>
#include <map>

class Scene {
protected :
	Screen* _screen;

public :
	Scene(Screen* screen)
	{
		_screen = screen;
	}

	virtual void Load() {}

	virtual void Unload() {}

	virtual void Update() {}
};

class SceneManager {
private:
	bool _canUpdate;
	static SceneManager* _instancePtr;

	SceneManager() 
	{ 
		_canUpdate = false;
		currentScene = nullptr;
		menuScene = nullptr;
		levelSelectScene = nullptr;
		gameScene = nullptr;
	}

public:
	Scene* currentScene;
	Level currentLevel;

	Scene* menuScene;
	Scene* levelSelectScene;
	Scene* gameScene;

	static SceneManager* Instance()
	{
		if (_instancePtr == NULL)
		{
			_instancePtr = new SceneManager();
			return _instancePtr;
		}
		else
		{
			return _instancePtr;
		}
	}

	void ChangeScene(Scene* newScene)
	{
		_canUpdate = false;

		if (currentScene != nullptr) 
		{
			this->currentScene->Unload();
		}

		this -> currentScene = &(*newScene);
		this -> currentScene->Load();
		_canUpdate = true;
	}

	void RestartScene() 
	{
		ChangeScene(currentScene);
	}

	void Update()
	{
		if (currentScene != nullptr && _canUpdate == true) currentScene->Update();
	}

	void QuitGame()
	{
		// Free everything
		exit(0);
	}
};

SceneManager* SceneManager::_instancePtr = NULL;

class MenuScene : public Scene
{
private :

public :

	MenuScene(Screen* screen) : Scene(screen) {}

	void Load() override
	{
		_screen -> DrawMenuScreen();
		_screen -> UpdateScreen();
	}

	void Unload() override 
	{
		_screen->ClearScreen();
		// Free everything
	}

	void Update() override
	{
		char c = _getch();
		if (c == QUIT) {
			SceneManager* sceneManager = SceneManager::Instance();
			sceneManager->QuitGame();
		}
		else {
			SceneManager* sceneManager = SceneManager::Instance();
			sceneManager->ChangeScene(sceneManager->levelSelectScene);
		}
	}
};

class LevelSelectScene : public Scene
{
private :
	// Later on add all the buttons with all the levels
	vector<LevelButton*> buttons;
	int _currentButtonIndex;

public :

	LevelSelectScene(Screen* screen) : Scene(screen) {}

	void Load() override
	{
		buttons.push_back(new LevelButton(Level1(), 5, 5));
		buttons.push_back(new LevelButton(Level2(), 5, 10));
		buttons.push_back(new LevelButton(Level3(), 5, 15));

		for (LevelButton* button : buttons)
		{
			_screen->DrawButtonUnHovered(button);
		}

		_screen -> DrawLevelSelectScreen();
		_screen -> DrawButtonHovered(buttons[0]);
		_currentButtonIndex = 0;

		_screen -> UpdateScreen();
	}

	void Unload() override
	{
		_screen->ClearScreen();
		// Free everything
	}

	void Update() override
	{
		_screen -> ReadOutput();

		//Get player UI input.
		switch (_getch()) {
			case UP:
				_screen -> DrawButtonUnHovered(buttons[_currentButtonIndex]);
				_currentButtonIndex--;
				if (_currentButtonIndex == -1) _currentButtonIndex = buttons.size() - 1;
				_screen -> DrawButtonHovered(buttons[_currentButtonIndex]);
				_screen -> UpdateScreen();
				break;
			case DOWN:
				_screen->DrawButtonUnHovered(buttons[_currentButtonIndex]);
				_currentButtonIndex++;
				if (_currentButtonIndex == buttons.size()) _currentButtonIndex = 0;
				_screen->DrawButtonHovered(buttons[_currentButtonIndex]);
				_screen->UpdateScreen();
				break;
			case CONFIRM:
				SceneManager::Instance() -> currentLevel = buttons[_currentButtonIndex]->GetLevel();
				SceneManager::Instance() -> ChangeScene(SceneManager::Instance() -> gameScene);
				break;
			case QUIT:
				SceneManager::Instance() -> ChangeScene(SceneManager::Instance() -> menuScene);
				break;
			default:
				break;
		}
	}
};

class GameScene : public Scene
{
private : 
	Level _level;
	typedef map<pair<int, int>, Tile*> TileMap;

	TileMap _tileMap;
	vector <Tile*> lasers;
	Tile* _playerPos;
	int _keyCount;
	bool firstMove;

	void MovePlayer(Tile* newPlayerPos)
	{
		_screen -> MoveObject(*_playerPos, *newPlayerPos);
		newPlayerPos->object = _playerPos->object;
		_playerPos->object = nullptr;
		_playerPos = newPlayerPos;
	}

	void CheckForPlayerMovement()
	{
		Tile* newPlayerPos = nullptr;

		switch (_getch()) {
		case UP:
			newPlayerPos = _tileMap.at(make_pair(_playerPos->GetY() - 1, _playerPos->GetX()));
			break;
		case DOWN:
			newPlayerPos = _tileMap.at(make_pair(_playerPos->GetY() + 1, _playerPos->GetX()));
			break;
		case RIGHT:
			newPlayerPos = _tileMap.at(make_pair(_playerPos->GetY(), _playerPos->GetX() + 1));
			break;
		case LEFT:
			newPlayerPos = _tileMap.at(make_pair(_playerPos->GetY(), _playerPos->GetX() - 1));
			break;
		case QUIT:
			SceneManager::Instance()->ChangeScene(SceneManager::Instance()->levelSelectScene);
			return;
		default:
			return;
		}

		GameObject* object = newPlayerPos->object;

		if (object != nullptr && object->name == "Door")
		{
			if (_keyCount == 0) return;

			delete(object);
			_keyCount--;
		}

		if (object != nullptr && object->name == "Key")
		{
			delete(object);
			_keyCount++;
		}

		if (newPlayerPos->isDeadly) 
		{
			SceneManager::Instance()->RestartScene();
			return;
		}
		if (newPlayerPos->isWining) 
		{
			SceneManager::Instance()->ChangeScene(SceneManager::Instance()->levelSelectScene);
			return;
		}

		if (newPlayerPos->isWalkable) MovePlayer(newPlayerPos);
	}

public :

	GameScene(Screen* screen) : Scene(screen) {}

	void Load() override
	{
		_level = SceneManager::Instance()->currentLevel;
		_keyCount = 0;

		// Build TileMap
		for (int y = 0; y < LEVEL_HEIGHT; y++)
		{
			for (int x = 0; x < LEVEL_WIDTH; x++)
			{
				char tileType = _level.map[y][x];

				Tile* tile;

				switch (tileType) {
				case 'w':
					tile = new WallTile(y, x);
					break;
				case 'l':
					tile = new LaserTile(y, x);
					lasers.push_back(tile);
					break;
				case 'e':
					tile = new ExitTile(y, x);
					break;
				case ' ':
					tile = new FloorTile(y, x);
					break;
				case 'k':
					tile = new FloorTile(y, x);
					tile->object = new Key();
					break;
				case 'd':
					tile = new FloorTile(y, x);
					tile->object = new Door();
					break;
				case 'p':
					tile = new FloorTile(y, x);
					tile->object = new Player();
					_playerPos = tile;
					break;
				default:
					tile = new Tile(y, x);
					break;
				}

				_tileMap[make_pair(y, x)] = tile;

				if (tile->object == nullptr) _screen->DrawSprite(*tile, tile->sprite);

				else _screen->DrawSprite(*tile, tile->object->sprite);
			}
		}

		firstMove = true;
		_screen -> UpdateScreen();
	}

	void Unload() override
	{
		_screen->ClearScreen();
		lasers.clear();
		
		for (int y = 0; y < LEVEL_HEIGHT; y++)
		{
			for (int x = 0; x < LEVEL_WIDTH; x++)
			{
				Tile* tile = _tileMap[make_pair(y, x)];
				if (tile->object != nullptr) delete(tile->object);
				delete(tile);
			}
		}
	}

	// Gets called every new input
	void Update() override
	{
		//If it's our first move we want to erase the lasers
		if (firstMove)
		{
			char c = _getch();
			if (c != QUIT)
			{
				FloorTile ft = FloorTile(0, 0);

				for (Tile* laser : lasers)
				{
					_screen->DrawSprite(*laser, ft.sprite);
				}

				_screen->UpdateScreen();
				firstMove = false;
			}
		}

		//buffer[y * TILE_HEIGHT + i][x * TILE_WIDTH + j].Char.AsciiChar = ' ';
		//buffer[y * TILE_HEIGHT + i][x * TILE_WIDTH + j].Attributes = 230;
		CheckForPlayerMovement();
	}
};