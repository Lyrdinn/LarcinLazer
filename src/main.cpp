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

    SceneManager* instance = SceneManager::instance();
    instance -> menuScene = &menuScene;
    instance -> levelSelectScene = &levelSelectScene;
    instance -> gameScene = &gameScene;

    instance -> ChangeScene(instance -> menuScene);

    while (true)
    {   
        instance -> Update();
    }
    
    return 0;
}


