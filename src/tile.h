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
                sprite.colors[y][x] = 100;
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
                sprite.colors[y][x] = 2;
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

        sprite.colors[0] = { 100,72,100,72,72,100,72,100 };
        sprite.colors[1] = { 100,72,100,72,72,100,72,100 };
        sprite.colors[2] = { 72,72,72,72,72,72,72,72 };
        sprite.colors[3] = { 100,72,100,72,72,100,72,100 };
        sprite.colors[4] = { 100,72,100,72,72,100,72,100 };
        sprite.colors[5] = { 72,72,72,72,72,72,72,72 };
        sprite.colors[6] = { 100,72,100,72,72,100,72,100 };
        sprite.colors[7] = { 100,72,100,72,72,100,72,100 };

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
    int portal_nb;

    PortalTile(int y, int x) : Tile(y, x)
    {
        portal_nb = 0;
        isWalkable = true;
        isDeadly = false;
        isWining = false;
        isPortal = true;

        sprite.colors[0] = { 2,2,2,2,2,2,2,2 };
        sprite.colors[1] = { 100,100,100,100,100,100,100,100 };
        sprite.colors[2] = { 100,100,100,100,100,100,100,100 };
        sprite.colors[3] = { 100,100,100,100,100,100,100,100 };
        sprite.colors[4] = { 100,100,100,100,100,100,100,100 };
        sprite.colors[5] = { 100,100,100,100,100,100,100,100 };
        sprite.colors[6] = { 100,100,100,100,100,100,100,100 };
        sprite.colors[7] = { 2,2,2,2,2,2,2,2 };

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

        sprite.colors[0] = { 100,100,100,255,255,100,100,100 };
        sprite.colors[1] = { 100,100,100,100,100,100,100,100 };
        sprite.colors[2] = { 100,100,255,255,255,255,100,100 };
        sprite.colors[3] = { 100,100,100,100,100,100,100,100 };
        sprite.colors[4] = { 255,255,255,255,255,255,255,255 };
        sprite.colors[5] = { 100,100,100,100,100,100,100,100 };
        sprite.colors[6] = { 255,255,255,255,255,255,255,255 };
        sprite.colors[7] = { 255,255,255,255,255,255,255,255 };

        for (int y = 0; y < TILE_HEIGHT; y++)
        {
            for (int x = 0; x < TILE_WIDTH; x++)
            {
                sprite.characters[y][x] = ' ';
            }
        }
    }
};
