#pragma once
#include <string>
#include <array>
#include "global.h"
using namespace std;

class Sprite
{
public:
    char characters[TILE_HEIGHT][TILE_WIDTH];

    array< array<int, TILE_WIDTH>, TILE_HEIGHT> colors;
};

class GameObject
{
public :
    string name;

    Sprite sprite;
};

class Player : public GameObject
{
public:

    Player()
    {
        name = "Player";

        sprite.colors[0] = { 100,100,100,2,2,100,100,100 };
        sprite.colors[1] = { 100,100,2,2,2,100,100,100 };
        sprite.colors[2] = { 2,100,100,2,2,100,100,100 };
        sprite.colors[3] = { 2,2,2,2,2,2,2,100 };
        sprite.colors[4] = { 100,100,100,2,2,100,2,100 };
        sprite.colors[5] = { 100,100,100,2,2,100,100,2 };
        sprite.colors[6] = { 100,100,2,100,100,2,2,100 };
        sprite.colors[7] = { 100,2,2,100,100,100,100,100 };

        FlipSprite();

        for (int y = 0; y < TILE_HEIGHT; y++)
        {
            for (int x = 0; x < TILE_WIDTH; x++)
            {
                sprite.characters[y][x] = ' ';
            }
        }
    }

    void FlipSprite()
    {
        Sprite tmp = sprite;
        for (int y = 0; y < TILE_HEIGHT; y++)
        {
            for (int x = 0; x < TILE_WIDTH; x++)
            {
                sprite.colors[y][ TILE_WIDTH - 1 - x] = tmp.colors[y][x];
            }
        }
    }
};

class Key : public GameObject
{
public:
    Key()
    {
        name = "Key";

        sprite.colors[0] = { 100,100,100,100,100,100,100,100 };
        sprite.colors[1] = { 100,100,100,100,100,100,100,100 };
        sprite.colors[2] = { 100,255,255,100,100,100,100,100 };
        sprite.colors[3] = { 255,100,100,255,255,255,255,255 };
        sprite.colors[4] = { 255,100,100,255,100,255,100,255 };
        sprite.colors[5] = { 100,255,255,100,100,100,100,100 };
        sprite.colors[6] = { 100,100,100,100,100,100,100,100 };
        sprite.colors[7] = { 100,100,100,100,100,100,100,100 };

        for (int y = 0; y < TILE_HEIGHT; y++)
        {
            for (int x = 0; x < TILE_WIDTH; x++)
            {
                sprite.characters[y][x] = ' ';
            }
        }
    }
};

class Door : public GameObject
{
public:
    Door()
    {
        name = "Door";

        sprite.colors[0] = { 100,100,2,2,2,2,100,100 };
        sprite.colors[1] = { 100,2,100,100,100,100,2,100 };
        sprite.colors[2] = { 100,2,100,100,100,100,2,100 };
        sprite.colors[3] = { 2,2,2,2,2,2,2,2 };
        sprite.colors[4] = { 2,2,2,100,100,2,2,2 };
        sprite.colors[5] = { 2,2,2,100,100,2,2,2 };
        sprite.colors[6] = { 2,2,100,2,2,100,2,2 };
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
