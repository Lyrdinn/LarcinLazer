#pragma once
#include "draw.h"
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

	// Gets called everyframe
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
	LevelButton* b_level_1 = new LevelButton(Level1(), 10, 10, 3, 5);
	LevelButton* b_level_2 = new LevelButton(Level2(), 15, 10, 3, 5);
	LevelButton* currentButton = nullptr;

public :

	LevelSelectScene(Screen* screen) : Scene(screen) {}

	void Load() override
	{
		_screen -> DrawButtonUnHovered(b_level_1);
		_screen -> DrawButtonUnHovered(b_level_2);

		_screen -> DrawLevelSelectScreen();

		currentButton = b_level_1;
		_screen -> DrawButtonHovered(currentButton);

		_screen -> UpdateScreen();
	}

	void Unload() override
	{
		_screen->ClearScreen();
		// Free everything
	}

	// Gets called every frame
	void Update() override
	{
		_screen -> ReadOutput();

		//Get player UI input.
		switch (_getch()) {
			case UP:
				//Replace with a more advanced list of buttons system.
				_screen -> DrawButtonUnHovered(currentButton);
				if (currentButton == b_level_1) currentButton = b_level_2;
				else currentButton = b_level_1;
				_screen -> DrawButtonHovered(currentButton);

				_screen -> UpdateScreen();
				break;
			case DOWN:
				//Replace with a more advanced list of buttons system.
				_screen -> DrawButtonUnHovered(currentButton);
				if (currentButton == b_level_1) currentButton = b_level_2;
				else currentButton = b_level_1;
				_screen -> DrawButtonHovered(currentButton);

				_screen -> UpdateScreen();
				break;
			case CONFIRM:
				SceneManager::Instance() -> currentLevel = currentButton->GetLevel();
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
	Tile* _playerPos;
	int _keyCount;

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
			delete(newPlayerPos->object);
			_keyCount++;
		}

		if (newPlayerPos->isWalkable) MovePlayer(newPlayerPos);
		if (newPlayerPos->isDeadly) Load();
		if (newPlayerPos->isWining) SceneManager::Instance()->ChangeScene(SceneManager::Instance()->levelSelectScene);
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

		_screen -> UpdateScreen();
	}

	void Unload() override
	{
		_screen->ClearScreen();
		
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

	// Gets called every frame
	void Update() override
	{
		CheckForPlayerMovement();
	}
};