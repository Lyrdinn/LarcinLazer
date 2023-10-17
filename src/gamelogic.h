#pragma once
#include "draw.h"
#include <list>
#include <vector>
#include "global.h"
#include <conio.h>
#include <map>
#include <array>

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
	Level* currentLevel;

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
	vector<Level*> _levels;
	vector<LevelButton*> _buttons;
	int _currentButtonIndex;

public :

	LevelSelectScene(Screen* screen) : Scene(screen) 
	{
		_currentButtonIndex = 0;

		_levels.push_back(new Level1());
		_levels.push_back(new Level2());
		_levels.push_back(new Level3());
		_levels.push_back(new Level4());
		_levels.push_back(new Level5());
		_levels.push_back(new Level6());

		_buttons.push_back(new Level1Button(_levels[0], 30, 10));
		_buttons.push_back(new Level2Button(_levels[1], 30, 20));
		_buttons.push_back(new Level3Button(_levels[2], 30, 30));
		_buttons.push_back(new Level4Button(_levels[3], 30, 40));
		_buttons.push_back(new Level5Button(_levels[4], 30, 50));
		_buttons.push_back(new Level6Button(_levels[5], 30, 60));
	}

	void Load() override
	{
		_screen->DrawLevelSelectScreen();

		for (LevelButton* button : _buttons)
		{
			_screen->DrawLevelButton(button, false);
		}

		_screen -> DrawLevelButton(_buttons[_currentButtonIndex], true);
		_screen -> UpdateScreen();
	}

	void Unload() override
	{
		_screen->ClearScreen();
	}

	void Update() override
	{
		_screen -> ReadOutput();

		//Get player UI input.
		switch (_getch()) {
			case UP:
				_screen -> DrawLevelButton(_buttons[_currentButtonIndex], false);
				_currentButtonIndex--;
				if (_currentButtonIndex == -1) _currentButtonIndex = _buttons.size() - 1;
				_screen -> DrawLevelButton(_buttons[_currentButtonIndex], true);
				_screen -> UpdateScreen();
				break;
			case DOWN:
				_screen->DrawLevelButton(_buttons[_currentButtonIndex], false);
				_currentButtonIndex++;
				if (_currentButtonIndex == _buttons.size()) _currentButtonIndex = 0;
				_screen->DrawLevelButton(_buttons[_currentButtonIndex], true);
				_screen->UpdateScreen();
				break;
			case CONFIRM:
				SceneManager::Instance() -> currentLevel = _buttons[_currentButtonIndex]->GetLevel();
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
	Level* _level;
	typedef map<pair<int, int>, Tile*> TileMap;

	TileMap _tileMap;
	vector <Tile*> _lasers;
	Tile* _playerPos;
	Player* _player;
	int _playerDir;
	bool _firstMove;
	int _keyCount;
	bool _jewelIsPickedUp;

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
			if (_playerDir == -1) {
				_playerDir = 1;
				_player->FlipSprite();
			}
			newPlayerPos = _tileMap.at(make_pair(_playerPos->GetY(), _playerPos->GetX() + 1));
			break;
		case LEFT:
			if (_playerDir == 1) {
				_playerDir = -1;
				_player->FlipSprite();
			}
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

		if (object != nullptr && object->name == "Jewel")
		{
			delete(object);
			_jewelIsPickedUp = true;
		}

		if (newPlayerPos->isDeadly) 
		{
			SceneManager::Instance()->RestartScene();
			return;
		}

		if (newPlayerPos->isWining) 
		{
			if (_jewelIsPickedUp) _level->jewelIsUnlocked = true;
			SceneManager::Instance()->ChangeScene(SceneManager::Instance()->levelSelectScene);
			return;
		}

		if (newPlayerPos->isPortal)
		{
			MovePlayer(((PortalTile*)newPlayerPos)->partner);
			return;
		}

		if (newPlayerPos->isWalkable) 
		{
			_playerPos->sprite = Sprite(BEI);
			MovePlayer(newPlayerPos);
		}
	}

public :

	GameScene(Screen* screen) : Scene(screen) {}

	void Load() override
	{
		_level = SceneManager::Instance()->currentLevel;
		_keyCount = 0;
		_jewelIsPickedUp = false;
		_firstMove = true;

		PortalTile* firstPortalOfPair[10]{ nullptr };

		// Build TileMap
		for (int y = 0; y < LEVEL_HEIGHT; y++)
		{
			for (int x = 0; x < LEVEL_WIDTH; x++)
			{
				char tileType = _level->lvlMap[y][x];

				Tile* tile = nullptr;

				switch (tileType) {
				case 'w':
					tile = new WallTile(y, x);
					break;
				case 'l':
					tile = new LaserTile(y, x);
					_lasers.push_back(tile);
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
				case 'j':
					tile = new FloorTile(y, x);
					tile->object = new Jewel();
					break;
				case 'p':
					tile = new FloorTile(y, x);
					_player = new Player();
					tile->object = _player;
					_playerPos = tile;

					_playerDir = _level->playerStartDir;
					if (_playerDir == -1) _player->FlipSprite();
					break;
				default:
					if (!isdigit(tileType)) break;

					PortalTile* portalTile = new PortalTile(y, x);
					tile = portalTile;
					int index = (tileType - '0');

					if (firstPortalOfPair[index] == nullptr)
					{
						firstPortalOfPair[index] = portalTile;
					}

					else
					{
						firstPortalOfPair[index]->partner = portalTile;
						portalTile->partner = firstPortalOfPair[index];
					}
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
		_lasers.clear();
		
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
		if (_firstMove)
		{
			char c = _getch();
			if (c != QUIT)
			{
				FloorTile ft = FloorTile(0, 0);

				for (Tile* laser : _lasers)
				{
					_screen->DrawSprite(*laser, ft.sprite);
				}

				_screen->UpdateScreen();
				_firstMove = false;
			}
		}

		CheckForPlayerMovement();
	}
};