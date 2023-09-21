#pragma once
#include <string>
#include "global.h"
using namespace std;

class Sprite
{
public:
    char characters[TILE_HEIGHT][TILE_WIDTH];

    int colors[TILE_HEIGHT][TILE_WIDTH];
};

class GameObject : public Sprite 
{

};


class Player : public GameObject
{
public:
    Player()
    {
        for (int y = 0; y < TILE_HEIGHT; y++)
        {
            for (int x = 0; x < TILE_WIDTH; x++)
            {
                characters[y][x] = 'p';
                colors[y][x] = 95;
            }
        }
    }
};
