#pragma once
#include <Windows.h>
#include "gameobject.h"
using namespace std;

class Tile
{
private:
    int _y, _x;

public:
    GameObject* object;

    Sprite sprite;

    Tile(int y, int x) : object(nullptr), _y(y), _x(x) {}

    int GetX()
    {
        return _x;
    }

    int GetY()
    {
        return _y;
    }
};
