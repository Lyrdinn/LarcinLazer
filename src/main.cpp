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
Screen screen;

void InitTileMap()
{
    for (int x = 0; x < LEVEL_WIDTH; x++)
    {
        for (int y = 0; y < LEVEL_HEIGHT; y++)
        {
            WallTile* tile = new WallTile(y, x);
            tileMap[make_pair(y, x)] = tile;
            screen.DrawSprite(*tile, tile->sprite);
        }
    }
}

void DrawLevel1() 
{
    for (int y = 4; y < 7; y++)
    {
        for (int x = 15; x < 24; x++)
        {
            Tile* oldTile = tileMap.at(make_pair(y, x));
            delete(oldTile);

            Tile* tile = new FloorTile(y, x);
            tileMap[make_pair(y, x)] = tile;
            screen.DrawSprite(*tile, tile->sprite);
        }
    }

    player = new Player();
    playerPos = tileMap.at(make_pair(5, 15));
    playerPos->object = player;
    screen.DrawSprite(*playerPos, player->sprite);
    screen.UpdateScreen();
}

void MovePlayer(Tile* newPlayerPos)
{
    screen.MoveObject(*playerPos, *newPlayerPos);
    newPlayerPos->object = player;
    playerPos->object = nullptr;
    playerPos = newPlayerPos;
}

void CheckForMovement() 
{
    Tile* newPlayerPos;

    switch (_getch()) {
    case 'z':
        newPlayerPos = tileMap.at(make_pair(playerPos->GetY() - 1, playerPos->GetX()));
        break;
    case 's':
        newPlayerPos = tileMap.at(make_pair(playerPos->GetY() + 1, playerPos->GetX()));
        break;
    case 'd':
        newPlayerPos = tileMap.at(make_pair(playerPos->GetY(), playerPos->GetX() + 1));
        break;
    case 'q':
        newPlayerPos = tileMap.at(make_pair(playerPos->GetY(), playerPos->GetX() - 1));
        break;
    default:
        return;
    }

    string s = typeid(*newPlayerPos).name();
    if (newPlayerPos->isWalkable) MovePlayer(newPlayerPos);
    screen.UpdateScreen();
}

int main()
{
    InitTileMap();
    DrawLevel1();

    while (true)
    {
        CheckForMovement();
    }

    return 0;
}


