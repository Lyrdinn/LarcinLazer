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

        sprite.colors[0] = { YELLOW,YELLOW,YELLOW,BLACK,BLACK,YELLOW,YELLOW,YELLOW };
        sprite.colors[1] = { YELLOW,YELLOW,BLACK,BLACK,BLACK,YELLOW,YELLOW,YELLOW };
        sprite.colors[2] = { BLACK,YELLOW,YELLOW,BLACK,BLACK,YELLOW,YELLOW,YELLOW };
        sprite.colors[3] = { BLACK,BLACK,BLACK,BLACK,BLACK,BLACK,BLACK,YELLOW };
        sprite.colors[4] = { YELLOW,YELLOW,YELLOW,BLACK,BLACK,YELLOW,BLACK,YELLOW };
        sprite.colors[5] = { YELLOW,YELLOW,YELLOW,BLACK,BLACK,YELLOW,YELLOW,BLACK };
        sprite.colors[6] = { YELLOW,YELLOW,BLACK,YELLOW,YELLOW,BLACK,BLACK,YELLOW };
        sprite.colors[7] = { YELLOW,BLACK,BLACK,YELLOW,YELLOW,YELLOW,YELLOW,YELLOW };

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

        sprite.colors[0] = { YELLOW,YELLOW,YELLOW,YELLOW,YELLOW,YELLOW,YELLOW,YELLOW };
        sprite.colors[1] = { YELLOW,YELLOW,YELLOW,YELLOW,YELLOW,YELLOW,YELLOW,YELLOW };
        sprite.colors[2] = { YELLOW,WHITE,WHITE,YELLOW,YELLOW,YELLOW,YELLOW,YELLOW };
        sprite.colors[3] = { WHITE,YELLOW,YELLOW,WHITE,WHITE,WHITE,WHITE,WHITE };
        sprite.colors[4] = { WHITE,YELLOW,YELLOW,WHITE,YELLOW,WHITE,YELLOW,WHITE };
        sprite.colors[5] = { YELLOW,WHITE,WHITE,YELLOW,YELLOW,YELLOW,YELLOW,YELLOW };
        sprite.colors[6] = { YELLOW,YELLOW,YELLOW,YELLOW,YELLOW,YELLOW,YELLOW,YELLOW };
        sprite.colors[7] = { YELLOW,YELLOW,YELLOW,YELLOW,YELLOW,YELLOW,YELLOW,YELLOW };

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

        sprite.colors[0] = { YELLOW,YELLOW,BLACK,BLACK,BLACK,BLACK,YELLOW,YELLOW };
        sprite.colors[1] = { YELLOW,BLACK,YELLOW,YELLOW,YELLOW,YELLOW,BLACK,YELLOW };
        sprite.colors[2] = { YELLOW,BLACK,YELLOW,YELLOW,YELLOW,YELLOW,BLACK,YELLOW };
        sprite.colors[3] = { BLACK,BLACK,BLACK,BLACK,BLACK,BLACK,BLACK,BLACK };
        sprite.colors[4] = { BLACK,BLACK,BLACK,YELLOW,YELLOW,BLACK,BLACK,BLACK };
        sprite.colors[5] = { BLACK,BLACK,BLACK,YELLOW,YELLOW,BLACK,BLACK,BLACK };
        sprite.colors[6] = { BLACK,BLACK,YELLOW,BLACK,BLACK,YELLOW,BLACK,BLACK };
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
