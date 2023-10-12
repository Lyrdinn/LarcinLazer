#pragma once
#include <Windows.h>
#include "gameobject.h"
using namespace std;

class Tile
{
private:
    int _y, _x;

public:
    bool isWalkable, isDeadly, isWining, isPortal = false;

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
        isDeadly = false;
        isWining = false;
        isPortal = false;

        for (int y = 0; y < TILE_HEIGHT; y++)
        {
            for (int x = 0; x < TILE_WIDTH; x++)
            {
                sprite.characters[y][x] = ' ';
                sprite.colors[y][x] = YELLOW;
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
        isDeadly = false;
        isWining = false;
        isPortal = false;

        for (int y = 0; y < TILE_HEIGHT; y++)
        {
            for (int x = 0; x < TILE_WIDTH; x++)
            {
                sprite.characters[y][x] = ' ';
                sprite.colors[y][x] = BLACK;
            }
        }
    }
};

class LaserTile : public Tile
{
public:
    LaserTile(int y, int x) : Tile(y, x)
    {
        isWalkable = true;
        isDeadly = true;
        isWining = false;
        isPortal = false;

        sprite.colors[0] = { YELLOW,RED,YELLOW,RED,RED,YELLOW,RED,YELLOW };
        sprite.colors[1] = { YELLOW,RED,YELLOW,RED,RED,YELLOW,RED,YELLOW };
        sprite.colors[2] = { RED,RED,RED,RED,RED,RED,RED,RED };
        sprite.colors[3] = { YELLOW,RED,YELLOW,RED,RED,YELLOW,RED,YELLOW };
        sprite.colors[4] = { YELLOW,RED,YELLOW,RED,RED,YELLOW,RED,YELLOW };
        sprite.colors[5] = { RED,RED,RED,RED,RED,RED,RED,RED };
        sprite.colors[6] = { YELLOW,RED,YELLOW,RED,RED,YELLOW,RED,YELLOW };
        sprite.colors[7] = { YELLOW,RED,YELLOW,RED,RED,YELLOW,RED,YELLOW };

        for (int y = 0; y < TILE_HEIGHT; y++)
        {
            for (int x = 0; x < TILE_WIDTH; x++)
            {
                sprite.characters[y][x] = ' ';
            }
        }
    }
};

class PortalTile : public Tile
{
public :
    PortalTile* partner = nullptr;

    PortalTile(int y, int x) : Tile(y, x)
    {
        isWalkable = true;
        isDeadly = false;
        isWining = false;
        isPortal = true;

        sprite.colors[0] = { BLACK,BLACK,BLACK,BLACK,BLACK,BLACK,BLACK,BLACK };
        sprite.colors[1] = { YELLOW,YELLOW,YELLOW,YELLOW,YELLOW,YELLOW,YELLOW,YELLOW };
        sprite.colors[2] = { YELLOW,YELLOW,YELLOW,YELLOW,YELLOW,YELLOW,YELLOW,YELLOW };
        sprite.colors[3] = { YELLOW,YELLOW,YELLOW,YELLOW,YELLOW,YELLOW,YELLOW,YELLOW };
        sprite.colors[4] = { YELLOW,YELLOW,YELLOW,YELLOW,YELLOW,YELLOW,YELLOW,YELLOW };
        sprite.colors[5] = { YELLOW,YELLOW,YELLOW,YELLOW,YELLOW,YELLOW,YELLOW,YELLOW };
        sprite.colors[6] = { YELLOW,YELLOW,YELLOW,YELLOW,YELLOW,YELLOW,YELLOW,YELLOW };
        sprite.colors[7] = { BLACK,BLACK,BLACK,BLACK,BLACK,BLACK,BLACK,BLACK };

        for (int y = 0; y < TILE_HEIGHT; y++)
        {
            for (int x = 0; x < TILE_WIDTH; x++)
            {
                sprite.characters[y][x] = ' ';
            }
        }
    }
};

class ExitTile : public Tile
{
public:
    ExitTile(int y, int x) : Tile(y, x)
    {
        isWalkable = true;
        isDeadly = false;
        isWining = true;
        isPortal = false;

        sprite.colors[0] = { YELLOW,YELLOW,YELLOW,WHITE,WHITE,YELLOW,YELLOW,YELLOW };
        sprite.colors[1] = { YELLOW,YELLOW,YELLOW,YELLOW,YELLOW,YELLOW,YELLOW,YELLOW };
        sprite.colors[2] = { YELLOW,YELLOW,WHITE,WHITE,WHITE,WHITE,YELLOW,YELLOW };
        sprite.colors[3] = { YELLOW,YELLOW,YELLOW,YELLOW,YELLOW,YELLOW,YELLOW,YELLOW };
        sprite.colors[4] = { WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,WHITE };
        sprite.colors[5] = { YELLOW,YELLOW,YELLOW,YELLOW,YELLOW,YELLOW,YELLOW,YELLOW };
        sprite.colors[6] = { WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,WHITE };
        sprite.colors[7] = { WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,WHITE };

        for (int y = 0; y < TILE_HEIGHT; y++)
        {
            for (int x = 0; x < TILE_WIDTH; x++)
            {
                sprite.characters[y][x] = ' ';
            }
        }
    }
};
