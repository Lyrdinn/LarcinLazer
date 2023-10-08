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

class GameObject
{
public :
    Sprite sprite;
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
                sprite.characters[y][x] = 'p';
                sprite.colors[y][x] = 0; //95
            }
        }
    }
};

class Key : public GameObject
{
public:
    Key()
    {
        for (int y = 0; y < TILE_HEIGHT; y++)
        {
            for (int x = 0; x < TILE_WIDTH; x++)
            {
                sprite.characters[y][x] = 'k';
                sprite.colors[y][x] = 95;
            }
        }
    }
};

class Door : public GameObject
{
public:
    Door()
    {
        for (int y = 0; y < TILE_HEIGHT; y++)
        {
            for (int x = 0; x < TILE_WIDTH; x++)
            {
                sprite.characters[y][x] = 'd';
                sprite.colors[y][x] = 95;
            }
        }
    }
};
