#include "gamelogic.h"


/* SCENE MANAGER */


SceneManager* SceneManager::_instancePtr = NULL;

void SceneManager::ChangeScene(Scene* newScene)
{
	_canUpdate = false;

	if (currentScene != nullptr)
	{
		this->currentScene->Unload();
	}

	this->currentScene = &(*newScene);
	this->currentScene->Load();
	_canUpdate = true;
}

void SceneManager::RestartScene()
{
	ChangeScene(currentScene);
}

void SceneManager::Update()
{
	if (currentScene != nullptr && _canUpdate == true) currentScene->Update();
}

void SceneManager::QuitGame()
{
	exit(0);
}


/* MENU SCENE */


void MenuScene::Load()
{
	_screen->DrawMenuScreen();
	_screen->UpdateScreen();
}

void MenuScene::Unload()
{
	_screen->ClearScreen();
}

void MenuScene::Update()
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


/* LEVEL SELECT SCENE */


void LevelSelectScene::Load()
{
	_screen->DrawLevelSelectScreen();

	for (LevelButton* button : _buttons)
	{
		_screen->DrawLevelButton(button, false);
	}

	_screen->DrawLevelButton(_buttons[_currentButtonIndex], true);
	_screen->UpdateScreen();
}

void LevelSelectScene::Unload()
{
	_screen->ClearScreen();
}

void LevelSelectScene::Update()
{
	_screen->ReadOutput();

	//Get player UI input.
	switch (_getch()) {
	case UP:
		_screen->DrawLevelButton(_buttons[_currentButtonIndex], false);
		_currentButtonIndex--;
		if (_currentButtonIndex == -1) _currentButtonIndex = _buttons.size() - 1;
		_screen->DrawLevelButton(_buttons[_currentButtonIndex], true);
		_screen->UpdateScreen();
		break;
	case DOWN:
		_screen->DrawLevelButton(_buttons[_currentButtonIndex], false);
		_currentButtonIndex++;
		if (_currentButtonIndex == _buttons.size()) _currentButtonIndex = 0;
		_screen->DrawLevelButton(_buttons[_currentButtonIndex], true);
		_screen->UpdateScreen();
		break;
	case CONFIRM:
		SceneManager::Instance()->currentLevel = _buttons[_currentButtonIndex]->GetLevel();
		SceneManager::Instance()->ChangeScene(SceneManager::Instance()->gameScene);
		break;
	case QUIT:
		SceneManager::Instance()->ChangeScene(SceneManager::Instance()->menuScene);
		break;
	default:
		break;
	}
}


/* GAME SCENE */


void GameScene::Load()
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

	_screen->UpdateScreen();
}

void GameScene::Unload()
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
void GameScene::Update()
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


/* WIN SCENE */

void WinScene::Load()
{
	_screen->DrawWinScreen();
	_screen->UpdateScreen();
}

void WinScene::Unload()
{
	_screen->ClearScreen();
}

void WinScene::Update()
{
	char c = _getch();
	if (c == QUIT) {
		SceneManager* sceneManager = SceneManager::Instance();
		sceneManager->ChangeScene(sceneManager->levelSelectScene);
	}
	else {
		SceneManager* sceneManager = SceneManager::Instance();
		sceneManager->ChangeScene(sceneManager->levelSelectScene);
	}
}