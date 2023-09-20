#pragma once
#include <iostream>
#include <windows.h>
#include "grid.h"
#include "global.h"


#define SCREEN_WIDTH 300
#define SCREEN_HEIGHT 200

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

    void DrawBaba(Tile tile)
    {
        int x = tile.GetX();
        int y = tile.GetY();

        buffer[y - 1][x].Char.AsciiChar = 'B';
        buffer[y - 1][x].Attributes = 95;
        buffer[y - 1][x + 1].Char.AsciiChar = ' ';
        buffer[y - 1][x + 1].Attributes = 95;
        buffer[y - 1][x + 2].Char.AsciiChar = 'A';
        buffer[y - 1][x + 2].Attributes = 95;
        buffer[y][x].Char.AsciiChar = 'B';
        buffer[y][x].Attributes = 95;
        buffer[y][x + 1].Char.AsciiChar = ' ';
        buffer[y][x + 1].Attributes = 95;
        buffer[y][x + 2].Char.AsciiChar = 'A';
        buffer[y][x + 2].Attributes = 95;
    }
    void MoveObject(Tile tile, int xdir, int ydir)
    {
        int x = tile.GetX();
        int y = tile.GetY();
        int color = buffer[y][x].Attributes;

        //moving upper 3 characters
        buffer[y - 1 + 2 * ydir][x + 3 * xdir].Char.AsciiChar = buffer[y][x].Char.AsciiChar;
        buffer[y - 1 + 2 * ydir][x + 3 * xdir].Attributes = color;
        buffer[y - 1 + 2 * ydir][x + 1 + 3 * xdir].Char.AsciiChar = buffer[y][x + 1].Char.AsciiChar;
        buffer[y - 1 + 2 * ydir][x + 1 + 3 * xdir].Attributes = color;
        buffer[y - 1 + 2 * ydir][x + 2 + 3 * xdir].Char.AsciiChar = buffer[y][x + 2].Char.AsciiChar;
        buffer[y - 1 + 2 * ydir][x + 2 + 3 * xdir].Attributes = color;

        //moving bottom 3 characters
        buffer[y + 2 * ydir][x + 3 * xdir].Char.AsciiChar = buffer[y][x].Char.AsciiChar;
        buffer[y + 2 * ydir][x + 3 * xdir].Attributes = color;
        buffer[y + 2 * ydir][x + 1 + 3 * xdir].Char.AsciiChar = buffer[y][x + 1].Char.AsciiChar;
        buffer[y + 2 * ydir][x + 1 + 3 * xdir].Attributes = color;
        buffer[y + 2 * ydir][x + 2 + 3 * xdir].Char.AsciiChar = buffer[y][x + 2].Char.AsciiChar;
        buffer[y + 2 * ydir][x + 2 + 3 * xdir].Attributes = color;

        //we clean the previous buffer characters
        buffer[y - 1][x].Char.AsciiChar = '\0';
        buffer[y - 1][x + 1].Char.AsciiChar = '\0';
        buffer[y - 1][x + 2].Char.AsciiChar = '\0';
        buffer[y][x].Char.AsciiChar = '\0';
        buffer[y][x + 1].Char.AsciiChar = '\0';
        buffer[y][x + 2].Char.AsciiChar = '\0';
        buffer[y - 1][x].Attributes = 0;
        buffer[y - 1][x + 1].Attributes = 0;
        buffer[y - 1][x + 2].Attributes = 0;
        buffer[y][x].Attributes = 0;
        buffer[y][x + 1].Attributes = 0;
        buffer[y][x + 2].Attributes = 0;
    }

    void MoveHorizontal(Tile tile, int dir)
    {
        int x = tile.GetX();
        int y = tile.GetY();
        int color = buffer[y][x].Attributes;

        //moving upper 3 characters
        buffer[y - 1][x + 3 * dir].Char.AsciiChar = buffer[y][x].Char.AsciiChar;
        buffer[y - 1][x + 3 * dir].Attributes = color;
        buffer[y - 1][x + 1 + 3 * dir].Char.AsciiChar = buffer[y][x + 1].Char.AsciiChar;
        buffer[y - 1][x + 1 + 3 * dir].Attributes = color;
        buffer[y - 1][x + 2 + 3 * dir].Char.AsciiChar = buffer[y][x + 2].Char.AsciiChar;
        buffer[y - 1][x + 2 + 3 * dir].Attributes = color;

        //moving bottom 3 characters
        buffer[y][x + 3 * dir].Char.AsciiChar = buffer[y][x].Char.AsciiChar;
        buffer[y][x + 3 * dir].Attributes = color;
        buffer[y][x + 1 + 3 * dir].Char.AsciiChar = buffer[y][x + 1].Char.AsciiChar;
        buffer[y][x + 1 + 3 * dir].Attributes = color;
        buffer[y][x + 2 + 3 * dir].Char.AsciiChar = buffer[y][x + 2].Char.AsciiChar;
        buffer[y][x + 2 + 3 * dir].Attributes = color;

        //we clean the previous buffer characters
        buffer[y - 1][x].Char.AsciiChar = '\0';
        buffer[y - 1][x + 1].Char.AsciiChar = '\0';
        buffer[y - 1][x + 2].Char.AsciiChar = '\0';
        buffer[y][x].Char.AsciiChar = '\0';
        buffer[y][x + 1].Char.AsciiChar = '\0';
        buffer[y][x + 2].Char.AsciiChar = '\0';
        buffer[y - 1][x].Attributes = 0;
        buffer[y - 1][x + 1].Attributes = 0;
        buffer[y - 1][x + 2].Attributes = 0;
        buffer[y][x].Attributes = 0;
        buffer[y][x + 1].Attributes = 0;
        buffer[y][x + 2].Attributes = 0;
    }

    void MoveVertical(Tile tile, int dir)
    {
        int x = tile.GetX();
        int y = tile.GetY();
        int color = buffer[y][x].Attributes;

        //moving upper 3 characters
        buffer[y - 1 + 2 * dir][x].Char.AsciiChar = buffer[y - 1][x].Char.AsciiChar;
        buffer[y - 1 + 2 * dir][x].Attributes = color;
        buffer[y - 1 + 2 * dir][x + 1].Char.AsciiChar = buffer[y - 1][x + 1].Char.AsciiChar;
        buffer[y - 1 + 2 * dir][x + 1].Attributes = color;
        buffer[y - 1 + 2 * dir][x + 2].Char.AsciiChar = buffer[y - 1][x + 2].Char.AsciiChar;
        buffer[y - 1 + 2 * dir][x + 2].Attributes = color;

        //moving bottom 3 characters
        buffer[y + 2 * dir][x].Char.AsciiChar = buffer[y][x].Char.AsciiChar;
        buffer[y + 2 * dir][x].Attributes = color;
        buffer[y + 2 * dir][x + 1].Char.AsciiChar = buffer[y][x + 1].Char.AsciiChar;
        buffer[y + 2 * dir][x + 1].Attributes = color;
        buffer[y + 2 * dir][x + 2].Char.AsciiChar = buffer[y][x + 2].Char.AsciiChar;
        buffer[y + 2 * dir][x + 2].Attributes = color;

        //we clean the previous buffer characters
        buffer[y - 1][x].Char.AsciiChar = '\0';
        buffer[y - 1][x + 1].Char.AsciiChar = '\0';
        buffer[y - 1][x + 2].Char.AsciiChar = '\0';
        buffer[y][x].Char.AsciiChar = '\0';
        buffer[y][x + 1].Char.AsciiChar = '\0';
        buffer[y][x + 2].Char.AsciiChar = '\0';
        buffer[y - 1][x].Attributes = 0;
        buffer[y - 1][x + 1].Attributes = 0;
        buffer[y - 1][x + 2].Attributes = 0;
        buffer[y][x].Attributes = 0;
        buffer[y][x + 1].Attributes = 0;
        buffer[y][x + 2].Attributes = 0;
    }

    void UpdateScreen()
    {
        WriteConsoleOutput(hOutput, (CHAR_INFO*)buffer, dwBufferSize, dwBufferCoord, &rcRegion);
    }
};