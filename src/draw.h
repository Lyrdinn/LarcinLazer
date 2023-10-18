#pragma once
#include <iostream>
#include <iostream>
#include <windows.h>
#include <string>
#include "tile.h"
#include "gameobject.h"
#include "global.h"
#include "ui.h"
#include <fstream>


class Screen
{
private:
    HANDLE hOutput = (HANDLE)GetStdHandle(STD_OUTPUT_HANDLE);

    COORD dwBufferSize = { SCREEN_WIDTH,SCREEN_HEIGHT };
    COORD dwBufferCoord = { 0, 0 };
    SMALL_RECT rcRegion = { 0, 0, SCREEN_WIDTH - 1, SCREEN_HEIGHT - 1 };

    CHAR_INFO buffer[SCREEN_HEIGHT][SCREEN_WIDTH];
    CHAR_INFO menuImage[SCREEN_HEIGHT][SCREEN_WIDTH];
    CHAR_INFO winImage[SCREEN_HEIGHT][SCREEN_WIDTH];

    void InitScreen()
    {
        ReadConsoleOutput(hOutput, (CHAR_INFO*)buffer, dwBufferSize, dwBufferCoord, &rcRegion);

        WriteConsoleOutput(hOutput, (CHAR_INFO*)buffer, dwBufferSize, dwBufferCoord, &rcRegion);
    }

public:
    Screen()
    {
        InitScreen();

        for (int i = 0; i < SCREEN_HEIGHT; i++)
        {
            for (int j = 0; j < SCREEN_WIDTH; j++)
            {
                menuImage[i][j].Char.AsciiChar = ' ';
                winImage[i][j].Char.AsciiChar = ' ';
            }
        }

        LoadImage("menu.txt", menuImage);
        LoadImage("win.txt", winImage);
    };

    void ReadOutput();
    void ClearScreen();
    void LoadImage(string path, CHAR_INFO buf[SCREEN_HEIGHT][SCREEN_WIDTH]);
    void DrawMenuScreen();
    void DrawWinScreen();
    void DrawButton(Button* button, bool hovered);
    void DrawLevelButton(LevelButton* levelButton, bool hovered);
    void DrawLevelSelectScreen();
    void DrawSprite(Tile& tile, Sprite& sprite);
    void MoveObject(Tile& oldTile, Tile& newTile);
    void UpdateScreen();
};