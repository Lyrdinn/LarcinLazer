#pragma once
#include <Windows.h>
#include "gameobject.h"
using namespace std;

class Tile
{
private:
    int _y, _x;

public:
    bool isWalkable;

    Sprite sprite = Sprite();

    GameObject* object = nullptr;

    Tile(int y, int x) 
    {
        _y = y;
        _x = x;
    }

    int GetX()
    {
        return _x;
    }

    int GetY()
    {
        return _y;
    }
};

class FloorTile : public Tile 
{
public:
    FloorTile(int y, int x) : Tile(y, x)
    {
        isWalkable = true;

        for (int y = 0; y < TILE_HEIGHT; y++)
        {
            for (int x = 0; x < TILE_WIDTH; x++)
            {
                sprite.characters[y][x] = 'f';
                sprite.colors[y][x] = 230;
            }
        }
    }
};

class WallTile : public Tile
{
public:
    WallTile(int y, int x) : Tile(y, x)
    {
        isWalkable = false;

        for (int y = 0; y < TILE_HEIGHT; y++)
        {
            for (int x = 0; x < TILE_WIDTH; x++)
            {
                sprite.characters[y][x] = ' ';
                sprite.colors[y][x] = 100;
            }
        }
    }
};
