#include <iostream>
#include <Windows.h>
#include <map>
#include "tile.h"
#include "draw.h"
#include <conio.h>

using namespace std;
typedef map<pair<int, int>, Tile*> TileMap;

TileMap tileMap;
Tile* playerPos;
Player* player;
Screen s;

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

void DrawLevel1() 
{
    player = new Player();
    Tile* tile = tileMap.at(make_pair(3, 5));
    s.DrawSprite(*tile, player->sprite);
    tile->object = player;

    playerPos = tile;

    s.UpdateScreen();
}

int main()
{
    InitTileMap();
    DrawLevel1();

    Tile* newPlayerPos;
    
    //Check if player can move to the tile -> if the tile has a wall or not.
    while (true)
    {
        switch (_getch()) {
        case 'z':
            newPlayerPos = tileMap.at(make_pair(playerPos->GetY() - 1, playerPos->GetX()));
            s.MoveObject(*playerPos, *newPlayerPos);
            newPlayerPos->object = player;
            playerPos->object = nullptr;
            playerPos = newPlayerPos;
        case 's' :
            newPlayerPos = tileMap.at(make_pair(playerPos->GetY() + 1, playerPos->GetX()));
            s.MoveObject(*playerPos, *newPlayerPos);
            newPlayerPos->object = player;
            playerPos->object = nullptr;
            playerPos = newPlayerPos;
        case 'q' :
            newPlayerPos = tileMap.at(make_pair(playerPos->GetY(), playerPos->GetX() - 1));
            s.MoveObject(*playerPos, *newPlayerPos);
            newPlayerPos->object = player;
            playerPos->object = nullptr;
            playerPos = newPlayerPos;
        case 'd' :
            newPlayerPos = tileMap.at(make_pair(playerPos->GetY(), playerPos->GetX() + 1));
            s.MoveObject(*playerPos, *newPlayerPos);
            newPlayerPos->object = player;
            playerPos->object = nullptr;
            playerPos = newPlayerPos;
        
        }

        s.UpdateScreen();

    }

    return 0;
}


