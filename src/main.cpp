#include <iostream>
#include <Windows.h>
#include <map>
#include "tile.h"
#include "gameobject.h"

#define SCREEN_WIDTH 200
#define SCREEN_HEIGHT 200
#define LEVEL_WIDTH 30
#define LEVEL_HEIGHT 20

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
}


int main()
{
    InitTileMap();
    AddBaba();
    return 0;
}


