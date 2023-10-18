#pragma once
#include "draw.h"
#include <list>
#include <vector>
#include "global.h"
#include <conio.h>
#include <map>
#include <array>


	class Scene {
	protected:
		Screen* _screen;

	public:
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
		Scene* winScene;

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

		void ChangeScene(Scene* newScene);
		void RestartScene();
		void Update();
		void QuitGame();
	};

	class MenuScene : public Scene
	{
	private:

	public:

		MenuScene(Screen* screen) : Scene(screen) {}

		void Load() override;

		void Unload() override;

		void Update() override;
	};

	class LevelSelectScene : public Scene
	{
	private:
		// Later on add all the buttons with all the levels
		vector<Level*> _levels;
		vector<LevelButton*> _buttons;
		int _currentButtonIndex;

	public:

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

		void Load() override;

		void Unload() override;

		void Update() override;
	};

	class GameScene : public Scene
	{
	private:
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
			_screen->MoveObject(*_playerPos, *newPlayerPos);
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
				SceneManager::Instance()->ChangeScene(SceneManager::Instance()->winScene);
				return;
			}

			if (newPlayerPos->isPortal)
			{
				MovePlayer(((PortalTile*)newPlayerPos)->partner);
				return;
			}

			if (newPlayerPos->isWalkable)
			{
				if (!_playerPos->isPortal) _playerPos->sprite = Sprite(BEI);
				MovePlayer(newPlayerPos);
			}
		}

	public:

		GameScene(Screen* screen) : Scene(screen) {}

		void Load() override;
		void Unload() override;
		void Update() override;
	};

	class WinScene : public Scene
	{
	private:

	public:

		WinScene(Screen* screen) : Scene(screen) {}

		void Load() override;
		void Unload() override;
		void Update() override;
	};
