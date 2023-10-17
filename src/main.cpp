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
    //Resize de la fenetre pour qu'elle soit en grand écran obligatoire ainsi qu'en mode pixel art.
    keybd_event(VK_MENU, 0x38, 0, 0);
    keybd_event(VK_RETURN, 0x1c, 0, 0);
    keybd_event(VK_RETURN, 0x1c, KEYEVENTF_KEYUP, 0);
    keybd_event(VK_MENU, 0x38, KEYEVENTF_KEYUP, 0);

    CONSOLE_FONT_INFOEX cfi;
    cfi.cbSize = sizeof(cfi);
    cfi.nFont = 0;
    cfi.dwFontSize.X = 10;
    cfi.dwFontSize.Y = 8;
    cfi.FontFamily = FF_DONTCARE;
    cfi.FontWeight = FW_NORMAL;
    SetCurrentConsoleFontEx(GetStdHandle(STD_OUTPUT_HANDLE), FALSE, &cfi);

    Screen screen = Screen();
    MenuScene menuScene =  MenuScene(&screen);
    LevelSelectScene levelSelectScene =  LevelSelectScene(&screen);
    GameScene gameScene =  GameScene(&screen);
    WinScene winScene = WinScene(&screen);

    SceneManager* Instance = SceneManager::Instance();
    Instance -> menuScene = &menuScene;
    Instance -> levelSelectScene = &levelSelectScene;
    Instance -> gameScene = &gameScene;
    Instance -> winScene = &winScene;

    Instance -> ChangeScene(Instance -> menuScene);

    while (true)
    {   
        Instance -> Update();
    }
    
    return 0;
}


