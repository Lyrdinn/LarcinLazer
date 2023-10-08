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

	virtual void load() {}

	void unload()
	{
		_screen -> ClearScreen();
	}
	virtual void update() {}
	virtual void freescene() {}
};

class SceneManager {
private:
	bool canUpdate;
	static SceneManager* instancePtr;

	SceneManager() { 
		canUpdate = false;
		_currentScene = nullptr;
		menuScene = nullptr;
		levelSelectScene = nullptr;
		gameScene = nullptr;
	}

public:
	Scene* _currentScene;
	Level currentLevel;

	Scene* menuScene;
	Scene * levelSelectScene;
	Scene * gameScene;

	static SceneManager* instance()
	{
		if (instancePtr == NULL)
		{
			instancePtr = new SceneManager();
			return instancePtr;
		}
		else
		{
			return instancePtr;
		}
	}

	void ChangeScene(Scene* newScene)
	{
		canUpdate = false;
		if (_currentScene != nullptr) {
			this -> _currentScene->unload();
			this -> _currentScene = &(*newScene);
			this -> _currentScene->load();
		}
		else
		{
			this -> _currentScene = &(*newScene);
			this -> _currentScene->load();
		}
		canUpdate = true;
	}

	void Update()
	{
		if (_currentScene != nullptr && canUpdate == true) _currentScene->update();
	}

	void QuitGame()
	{
		//free everything
		exit(0);
	}
};

SceneManager* SceneManager::instancePtr = NULL;

class MenuScene : public Scene
{
private :

public :

	MenuScene(Screen* screen) : Scene(screen) {}

	//Gets called everyframe
	void update() override
	{
		char c = _getch();
		if (c == QUIT) {
			SceneManager* sceneManager = SceneManager::instance();
			sceneManager -> QuitGame();
		}
		else {
			SceneManager* sceneManager = SceneManager::instance();
			sceneManager -> ChangeScene(sceneManager -> levelSelectScene);
		}
	}

	void load() override
	{
		_screen -> DrawMenuScreen();
		_screen -> UpdateScreen();
	}

	void freescene() override {}
};

class LevelSelectScene : public Scene
{
private :
	//Later on add all the buttons with all the levels
	LevelButton* b_level_1 = new LevelButton(Level1(), 10, 10, 3, 5);
	LevelButton* b_level_2 = new LevelButton(Level2(), 15, 10, 3, 5);
	LevelButton* currentButton = nullptr;

public :

	LevelSelectScene(Screen* screen) : Scene(screen) {}

	void load() override
	{
		_screen -> DrawButtonUnHovered(b_level_1);
		_screen -> DrawButtonUnHovered(b_level_2);

		_screen -> DrawLevelSelectScreen();

		currentButton = b_level_1;
		_screen -> DrawButtonHovered(currentButton);

		_screen -> UpdateScreen();

	}

	//Gets called every frame
	void update() override
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
				SceneManager::instance() -> currentLevel = currentButton->GetLevel();
				SceneManager::instance() -> ChangeScene(SceneManager::instance() -> gameScene);
				break;
			case QUIT:
				SceneManager::instance() -> ChangeScene(SceneManager::instance() -> menuScene);
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

	TileMap tileMap;
	Tile* startPos;
	Tile* playerPos;
	Player* _player;

	void MovePlayer(Tile* newPlayerPos)
	{
		_screen -> MoveObject(*playerPos, *newPlayerPos);
		newPlayerPos->object = _player;
		playerPos->object = nullptr;
		playerPos = newPlayerPos;
	}

	void CheckForPlayerMovement()
	{
		Tile* newPlayerPos = nullptr;

		switch (_getch()) {
		case UP:
			newPlayerPos = tileMap.at(make_pair(playerPos->GetY() - 1, playerPos->GetX()));
			break;
		case DOWN:
			newPlayerPos = tileMap.at(make_pair(playerPos->GetY() + 1, playerPos->GetX()));
			break;
		case RIGHT:
			newPlayerPos = tileMap.at(make_pair(playerPos->GetY(), playerPos->GetX() + 1));
			break;
		case LEFT:
			newPlayerPos = tileMap.at(make_pair(playerPos->GetY(), playerPos->GetX() - 1));
			break;
		case QUIT:
			SceneManager::instance()->ChangeScene(SceneManager::instance()->levelSelectScene);
			break;
		default:
			return;
		}

		if (newPlayerPos != nullptr && newPlayerPos->isWalkable) MovePlayer(newPlayerPos);
		if (newPlayerPos != nullptr && newPlayerPos->isDeadly) MovePlayer(startPos);
		_screen -> UpdateScreen();
	}

public :

	GameScene(Screen* screen) : Scene(screen) 
	{
		_player = new Player();
		startPos = nullptr;
		playerPos = nullptr;
	}

	void load() override
	{
		_level = SceneManager::instance()->currentLevel;

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
					startPos = tile;
					playerPos = startPos;
					playerPos->object = _player;
					break;
				default:
					tile = new Tile(y, x);
					break;
				}

				tileMap[make_pair(y, x)] = tile;

				if (tile->object == nullptr) 
				{
					_screen->DrawSprite(*tile, tile->sprite);
				}

				else _screen->DrawSprite(*tile, tile->object->sprite);
			}
		}

		// Draw everything on screen
		_screen -> UpdateScreen();
	}

	//Gets called every frame
	void update() override
	{
		//check win conditions
		CheckForPlayerMovement();
	}

	void freescene() override
	{
		free(_player);
	}
};