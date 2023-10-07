#pragma once
#include <iostream>
#include <windows.h>
#include <string>
#include "tile.h"
#include "gameobject.h"
#include "global.h"
#include "ui.h"

class Screen
{
private:
    HANDLE hOutput = (HANDLE)GetStdHandle(STD_OUTPUT_HANDLE);

    COORD dwBufferSize = { SCREEN_WIDTH,SCREEN_HEIGHT };
    COORD dwBufferCoord = { 0, 0 };
    SMALL_RECT rcRegion = { 0, 0, SCREEN_WIDTH - 1, SCREEN_HEIGHT - 1 };

    CHAR_INFO buffer[SCREEN_HEIGHT][SCREEN_WIDTH];

    void InitScreen()
    {
        ReadConsoleOutput(hOutput, (CHAR_INFO*)buffer, dwBufferSize, dwBufferCoord, &rcRegion);

        WriteConsoleOutput(hOutput, (CHAR_INFO*)buffer, dwBufferSize, dwBufferCoord, &rcRegion);
    }

public:
    Screen()
    {
        InitScreen();
    };

    void ReadOutput()
    {
        ReadConsoleOutput(hOutput, (CHAR_INFO*)buffer, dwBufferSize, dwBufferCoord, &rcRegion);
    }

    void ClearScreen()
    {
        for (int i = 0; i < SCREEN_HEIGHT; i++)
        {
            for (int j = 0; j < SCREEN_WIDTH; j++)
            {
                buffer[i][j].Char.AsciiChar = '\0';
                buffer[i][j].Attributes = 0;
            }
        }

        UpdateScreen();
    }

    void DrawMenuScreen()
    {
        string s = "press any button to continue or ESC to quit.";

        for (int j = 0; j < s.length(); j ++)
        {
            buffer[10][j + 5].Char.AsciiChar = s[j];
            buffer[10][j + 5].Attributes = 10;
        }
    }

    void DrawButtonUnHovered(Button* button)
    {
        int x = button->GetX();
        int y = button->GetY();

        for (int i = 0; i < BUTTON_HEIGHT; i++)
        {
            for (int j = 0; j < BUTTON_WIDTH; j++)
            {
                buffer[y + i][x + j].Char.AsciiChar = button -> characters[i][j];
                buffer[y + i][x + j].Attributes = button -> colors[i][j];
            }
        }
    }

    void DrawButtonHovered(Button * button)
    {
        int x = button->GetX();
        int y = button->GetY();

        for (int i = 0; i < BUTTON_HEIGHT; i++)
        {
            for (int j = 0; j < BUTTON_WIDTH; j++)
            {
                buffer[y + i][x + j].Attributes = 10;
            }
        }
    }

    void DrawLevelSelectScreen()
    {

    }

    void DrawSprite(Tile& tile, Sprite& sprite)
    {
        int x = tile.GetX();
        int y = tile.GetY();

        for (int i = 0; i < TILE_HEIGHT; i++)
        {
            for (int j = 0; j < TILE_WIDTH; j++)
            {
               buffer[y * TILE_HEIGHT + i][x * TILE_WIDTH + j].Char.AsciiChar = sprite.characters[i][j];
               buffer[y * TILE_HEIGHT + i][x * TILE_WIDTH + j].Attributes = sprite.colors[i][j];
            }
        }
    }

    void MoveObject(Tile& oldTile, Tile& newTile)
    {
        //Drawing the sprite on the new tile.
        DrawSprite(newTile, oldTile.object->sprite);

        //Recoloring the old tile.
        DrawSprite(oldTile, oldTile.sprite);
    }

    void UpdateScreen()
    {
        WriteConsoleOutput(hOutput, (CHAR_INFO*)buffer, dwBufferSize, dwBufferCoord, &rcRegion);
    }
};