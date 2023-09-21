#pragma once
#include <iostream>
#include <windows.h>
#include "tile.h"
#include "gameobject.h"
#include "global.h"

#define TILE_HEIGHT
#define TILE_WIDTH

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

    void DrawObject(Tile tile, GameObject object)
    {
        int x = tile.GetX();
        int y = tile.GetY();

        for (int i = 0; i < TILE_HEIGHT; i++)
        {
            for (int j = 0; j < TILE_WIDTH; j++)
            {
               buffer[y * TILE_HEIGHT + i][x * TILE_WIDTH + j].Char.AsciiChar = object.sprite[i][j];
               buffer[y * TILE_HEIGHT + i][x * TILE_WIDTH + j].Attributes = object.color[i][j];
            }
        }
    }

    /*
        We move from 2 in the y axis and from 3 in the axis.
    */
    void MoveObject(Tile tile, GameObject object, int xdir, int ydir)
    {
        int x = tile.GetX() + xdir;
        int y = tile.GetY() + ydir;

        DrawObject(Tile tile, GameObject object);
           
        //Decoloring the old tile.
        for (int i = 0; i < TILE_HEIGHT; i++)
        {
            for (int j = 0; j < TILE_WIDTH; j++)
            {
                buffer[y * TILE_HEIGHT + i][x * TILE_WIDTH + j].Char.AsciiChar = '\0';
                buffer[y * TILE_HEIGHT + i][x * TILE_WIDTH + j].Attributes = 0;
            }
        }
    }

    void UpdateScreen()
    {
        WriteConsoleOutput(hOutput, (CHAR_INFO*)buffer, dwBufferSize, dwBufferCoord, &rcRegion);
    }
};