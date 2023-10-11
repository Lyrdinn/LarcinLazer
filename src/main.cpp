#include <iostream>
#include <Windows.h>
#include <conio.h>
#include <map>
#include "gamelogic.h"
#include "global.h"
#include "draw.h"
#include "ui.h"

using namespace std;

int main()
{
    Screen screen = Screen();
    MenuScene menuScene =  MenuScene(&screen);
    LevelSelectScene levelSelectScene =  LevelSelectScene(&screen);
    GameScene gameScene =  GameScene(&screen);

    SceneManager* Instance = SceneManager::Instance();
    Instance -> menuScene = &menuScene;
    Instance -> levelSelectScene = &levelSelectScene;
    Instance -> gameScene = &gameScene;

    Instance -> ChangeScene(Instance -> menuScene);

    while (true)
    {   
        Instance -> Update();
    }
    
    return 0;
}


