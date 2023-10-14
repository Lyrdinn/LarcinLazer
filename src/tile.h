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

    Sprite sprite;

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

        sprite = Sprite(YEL);
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

        sprite = Sprite(BLA);
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

        sprite.colors[0] = { YEL,RED,YEL,RED,RED,YEL,RED,YEL };
        sprite.colors[1] = { YEL,RED,YEL,RED,RED,YEL,RED,YEL };
        sprite.colors[2] = { RED,RED,RED,RED,RED,RED,RED,RED };
        sprite.colors[3] = { YEL,RED,YEL,RED,RED,YEL,RED,YEL };
        sprite.colors[4] = { YEL,RED,YEL,RED,RED,YEL,RED,YEL };
        sprite.colors[5] = { RED,RED,RED,RED,RED,RED,RED,RED };
        sprite.colors[6] = { YEL,RED,YEL,RED,RED,YEL,RED,YEL };
        sprite.colors[7] = { YEL,RED,YEL,RED,RED,YEL,RED,YEL };
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

        sprite.colors[0] = { BLA,BLA,BLA,BLA,BLA,BLA,BLA,BLA };
        sprite.colors[1] = { YEL,YEL,YEL,YEL,YEL,YEL,YEL,YEL };
        sprite.colors[2] = { YEL,YEL,YEL,YEL,YEL,YEL,YEL,YEL };
        sprite.colors[3] = { YEL,YEL,YEL,YEL,YEL,YEL,YEL,YEL };
        sprite.colors[4] = { YEL,YEL,YEL,YEL,YEL,YEL,YEL,YEL };
        sprite.colors[5] = { YEL,YEL,YEL,YEL,YEL,YEL,YEL,YEL };
        sprite.colors[6] = { YEL,YEL,YEL,YEL,YEL,YEL,YEL,YEL };
        sprite.colors[7] = { BLA,BLA,BLA,BLA,BLA,BLA,BLA,BLA };
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

        sprite.colors[0] = { YEL,YEL,YEL,WHI,WHI,YEL,YEL,YEL };
        sprite.colors[1] = { YEL,YEL,YEL,YEL,YEL,YEL,YEL,YEL };
        sprite.colors[2] = { YEL,YEL,WHI,WHI,WHI,WHI,YEL,YEL };
        sprite.colors[3] = { YEL,YEL,YEL,YEL,YEL,YEL,YEL,YEL };
        sprite.colors[4] = { WHI,WHI,WHI,WHI,WHI,WHI,WHI,WHI };
        sprite.colors[5] = { YEL,YEL,YEL,YEL,YEL,YEL,YEL,YEL };
        sprite.colors[6] = { WHI,WHI,WHI,WHI,WHI,WHI,WHI,WHI };
        sprite.colors[7] = { WHI,WHI,WHI,WHI,WHI,WHI,WHI,WHI };
    }
};
