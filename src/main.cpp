#include <iostream>
#include <Windows.h>
#include <map>
#include "tile.h"
#include "draw.h"

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

void DrawLevel1() 
{
    Player* player = new Player();
    Tile* oldtile = tileMap.at(make_pair(6, 11));
    oldtile->object = player;

    Screen s;
    s.DrawSprite(*oldtile, player->sprite);

    Tile* newtile = tileMap.at(make_pair(8, 11));
    s.MoveObject(*oldtile, *newtile);
    s.UpdateScreen();
}


int main()
{
    InitTileMap();
    DrawLevel1();

    return 0;
}


