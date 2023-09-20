#pragma once
#include <Windows.h>
#include "gameobject.h"
using namespace std;

class Tile
{
private:
    int _y, _x;

    GameObject _object;

public:
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

    void SetGameObject(GameObject& object) 
    {
        _object = object;
    }
};
