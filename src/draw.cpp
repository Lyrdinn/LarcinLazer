#include <Windows>
#include "grid.h"

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

        for (int i = 0; i < TILE_WIDTH; i++)
        {
            buffer[y - 1][x].Char.AsciiChar = object.string[i];
            buffer[y - 1][x].Attributes = object.color[i];
        }

        for (int i = TILE_WIDTH; i < 2 * TILE_WIDTH; i++)
        {
            buffer[y][x].Char.AsciiChar = object.string[i];
            buffer[y][x].Attributes = object.color[i];
        }

        buffer[y - 1][x].Char.AsciiChar = 'B';
        buffer[y - 1][x].Attributes = color;
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

    /*
        We move from 2 in the y axis and from 3 in the axis.
    */
    void MoveObject(Tile tile, int xdir, int ydir)
    {
        int x = tile.GetX();
        int y = tile.GetY();
        int color = buffer[y][x].Attributes;

        //moving upper 3 characters
        buffer[y + 2 * ydir][x + 3 * xdir].Char.AsciiChar = buffer[y][x].Char.AsciiChar;
        buffer[y + 2 * ydir][x + 3 * xdir].Attributes = color;
        buffer[y + 2 * ydir][x + 1 + 3 * xdir].Char.AsciiChar = buffer[y][x + 1].Char.AsciiChar;
        buffer[y + 2 * ydir][x + 1 + 3 * xdir].Attributes = color;
        buffer[y + 2 * ydir][x + 2 + 3 * xdir].Char.AsciiChar = buffer[y][x + 2].Char.AsciiChar;
        buffer[y + 2 * ydir][x + 2 + 3 * xdir].Attributes = color;

        //moving bottom 3 characters
        buffer[y + 1 + 2 * ydir][x + 3 * xdir].Char.AsciiChar = buffer[y + 1][x].Char.AsciiChar;
        buffer[y + 1 + 2 * ydir][x + 3 * xdir].Attributes = color;
        buffer[y + 1 + 2 * ydir][x + 1 + 3 * xdir].Char.AsciiChar = buffer[y + 1][x + 1].Char.AsciiChar;
        buffer[y + 1 + 2 * ydir][x + 1 + 3 * xdir].Attributes = color;
        buffer[y + 1 + 2 * ydir][x + 2 + 3 * xdir].Char.AsciiChar = buffer[y + 1][x + 2].Char.AsciiChar;
        buffer[y + 1 + 2 * ydir][x + 2 + 3 * xdir].Attributes = color;

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