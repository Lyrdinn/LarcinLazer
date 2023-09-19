#include <iostream>
#include <Windows.h>
#include "grid.h"
#include "draw.h"

#define SCREEN_WIDTH 200
#define SCREEN_HEIGHT 200

void MoveDown(CHAR_INFO buffer[SCREEN_HEIGHT][SCREEN_WIDTH], Tile tile)
{
    int x = tile.GetX();
    int y = tile.GetY();
    int color = buffer[y][x].Attributes;

    //moving upper 3 characters
    buffer[y + 1][x].Char.AsciiChar = buffer[y - 1][x].Char.AsciiChar;
    buffer[y + 1][x].Attributes = color;
    buffer[y + 1][x + 1].Char.AsciiChar = buffer[y - 1][x + 1].Char.AsciiChar;
    buffer[y + 1][x + 1].Attributes = color;
    buffer[y + 1][x + 2].Char.AsciiChar = buffer[y - 1][x + 2].Char.AsciiChar;
    buffer[y + 1][x + 2].Attributes = color;

    //moving bottom 3 characters
    buffer[y + 2][x].Char.AsciiChar = buffer[y][x].Char.AsciiChar;
    buffer[y + 2][x].Attributes = color;
    buffer[y + 2][x + 1].Char.AsciiChar = buffer[y][x + 1].Char.AsciiChar;
    buffer[y + 2][x + 1].Attributes = color;
    buffer[y + 2][x + 2].Char.AsciiChar = buffer[y][x + 2].Char.AsciiChar;
    buffer[y + 2][x + 2].Attributes = color;

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

void InitializeBuffer()
{
    HANDLE hOutput = (HANDLE)GetStdHandle(STD_OUTPUT_HANDLE);

    COORD dwBufferSize = { SCREEN_WIDTH,SCREEN_HEIGHT };
    COORD dwBufferCoord = { 0, 0 };
    SMALL_RECT rcRegion = { 0, 0, SCREEN_WIDTH - 1, SCREEN_HEIGHT - 1 };

    CHAR_INFO buffer[SCREEN_HEIGHT][SCREEN_WIDTH];
    ReadConsoleOutput(hOutput, (CHAR_INFO*)buffer, dwBufferSize, dwBufferCoord, &rcRegion);

    buffer[6][14].Char.AsciiChar = 'I';
    buffer[6][14].Attributes = 15;
    buffer[6][15].Char.AsciiChar = ' ';
    buffer[6][15].Attributes = 15;
    buffer[6][16].Char.AsciiChar = 'S';
    buffer[6][16].Attributes = 15;

    buffer[5][17].Char.AsciiChar = ' ';
    buffer[5][17].Attributes = 95;
    buffer[5][18].Char.AsciiChar = ' ';
    buffer[5][18].Attributes = 95;
    buffer[5][19].Char.AsciiChar = ' ';
    buffer[5][19].Attributes = 95;
    buffer[6][17].Char.AsciiChar = 'Y';
    buffer[6][17].Attributes = 95;
    buffer[6][18].Char.AsciiChar = 'O';
    buffer[6][18].Attributes = 95;
    buffer[6][19].Char.AsciiChar = 'U';
    buffer[6][19].Attributes = 95;


    buffer[5][11].Char.AsciiChar = 'B';
    buffer[5][11].Attributes = 95;
    buffer[5][12].Char.AsciiChar = ' ';
    buffer[5][12].Attributes = 95;
    buffer[5][13].Char.AsciiChar = 'A';
    buffer[5][13].Attributes = 95;
    buffer[6][11].Char.AsciiChar = 'B';
    buffer[6][11].Attributes = 95;
    buffer[6][12].Char.AsciiChar = ' ';
    buffer[6][12].Attributes = 95;
    buffer[6][13].Char.AsciiChar = 'A';
    buffer[6][13].Attributes = 95;

    GameObject baba("Baba");
    Tile tile(6,11);

    MoveDown(buffer, tile);

    WriteConsoleOutput(hOutput, (CHAR_INFO*)buffer, dwBufferSize, dwBufferCoord, &rcRegion);
}


int main()
{
    InitializeBuffer();
    return 0;
}
