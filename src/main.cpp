#include <iostream>
#include <Windows.h>
#include <map>
#include "tile.h"
#include "gameobject.h"

<<<<<<< HEAD
#define SCREEN_WIDTH 200
#define SCREEN_HEIGHT 200
#define LEVEL_WIDTH 30
#define LEVEL_HEIGHT 20

<<<<<<< HEAD
using namespace std;
typedef map<pair<int, int>, Tile*> TileMap;

TileMap tileMap;

void InitTileMap()
{
    for (int x = 0; x < LEVEL_WIDTH; x++)
    {
        for (int y = 0; y < LEVEL_HEIGHT; y++)
        {
            Tile* tile = new Tile(y, x);
            tileMap[make_pair(y, x)] = tile;
        }
    }
}

void AddBaba() 
{
    Baba* baba = new Baba();
    Tile* tile = tileMap.at(make_pair(6, 11));
    (*tile).SetGameObject(*baba);

    // DrawObject(*tile, *baba);
    // Updtale Console
=======
void InitializeBuffer()
=======
/*void InitializeBuffer()
>>>>>>> 5dcef8d (Classe Screen)
{
    HANDLE hOutput = (HANDLE)GetStdHandle(STD_OUTPUT_HANDLE);

    COORD dwBufferSize = { SCREEN_WIDTH,SCREEN_HEIGHT };
    COORD dwBufferCoord = { 0, 0 };
    SMALL_RECT rcRegion = { 0, 0, SCREEN_WIDTH - 1, SCREEN_HEIGHT - 1 };

    CHAR_INFO buffer[SCREEN_HEIGHT][SCREEN_WIDTH];
    ReadConsoleOutput(hOutput, (CHAR_INFO*)buffer, dwBufferSize, dwBufferCoord, &rcRegion);

    buffer[6 + 2][14].Char.AsciiChar = 'I';
    buffer[6 + 2][14].Attributes = 15;
    buffer[6 + 2][15].Char.AsciiChar = ' ';
    buffer[6 + 2][15].Attributes = 15;
    buffer[6 + 2][16].Char.AsciiChar = 'S';
    buffer[6 + 2][16].Attributes = 15;

    buffer[5 + 2][17].Char.AsciiChar = ' ';
    buffer[5 + 2][17].Attributes = 95;
    buffer[5 + 2][18].Char.AsciiChar = ' ';
    buffer[5 + 2][18].Attributes = 95;
    buffer[5 + 2][19].Char.AsciiChar = ' ';
    buffer[5 + 2][19].Attributes = 95;
    buffer[6 + 2][17].Char.AsciiChar = 'Y';
    buffer[6 + 2][17].Attributes = 95;
    buffer[6 + 2][18].Char.AsciiChar = 'O';
    buffer[6 + 2][18].Attributes = 95;
    buffer[6 + 2][19].Char.AsciiChar = 'U';
    buffer[6 + 2][19].Attributes = 95;


    buffer[5 + 2][11].Char.AsciiChar = 'B';
    buffer[5 + 2][11].Attributes = 95;
    buffer[5 + 2][12].Char.AsciiChar = ' ';
    buffer[5 + 2][12].Attributes = 95;
    buffer[5 + 2][13].Char.AsciiChar = 'A';
    buffer[5 + 2][13].Attributes = 95;
    buffer[6 + 2][11].Char.AsciiChar = 'B';
    buffer[6 + 2][11].Attributes = 95;
    buffer[6 + 2][12].Char.AsciiChar = ' ';
    buffer[6 + 2][12].Attributes = 95;
    buffer[6 + 2][13].Char.AsciiChar = 'A';
    buffer[6 + 2][13].Attributes = 95;

<<<<<<< HEAD
    GameObject baba("Baba");
    Tile tile(8,11);

    //MoveHorizontal(buffer, tile, -1);
    MoveVertical(buffer, tile, -1);

    WriteConsoleOutput(hOutput, (CHAR_INFO*)buffer, dwBufferSize, dwBufferCoord, &rcRegion);
>>>>>>> 8fdcd05 (Fini les fonction de redessinage de cases)
}
=======
}*/
>>>>>>> 5dcef8d (Classe Screen)


int main()
{
<<<<<<< HEAD
<<<<<<< HEAD
    InitTileMap();
    AddBaba();
    return 0;
}









/*

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
*/

/*
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
*/
=======
    InitializeBuffer();
=======
    Screen screen;

    GameObject baba("Baba");
    Tile tile(6, 6);
    screen.DrawBaba(tile);
    screen.UpdateScreen();

    screen.MoveObject(tile, 0,1);
    screen.UpdateScreen();

>>>>>>> 5dcef8d (Classe Screen)
    return 0;
}
>>>>>>> 8fdcd05 (Fini les fonction de redessinage de cases)
