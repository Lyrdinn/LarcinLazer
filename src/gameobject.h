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

    Sprite(int color) 
    {
        for (int y = 0; y < TILE_HEIGHT; y++)
        {
            for (int x = 0; x < TILE_WIDTH; x++)
            {
                characters[y][x] = ' ';
                colors[y][x] = color;
            }
        }
    }

    Sprite() : Sprite(BLA) { };
};

class ButtonSprite
{
public :

    char characters[BUTTON_HEIGHT][BUTTON_WIDTH];

    array< array<int, BUTTON_WIDTH>, BUTTON_HEIGHT> colors;

    ButtonSprite(int color)
    {
        for (int y = 0; y < BUTTON_HEIGHT; y++)
        {
            for (int x = 0; x < BUTTON_WIDTH; x++)
            {
                characters[y][x] = ' ';
                colors[y][x] = color;
            }
        }
    }

    ButtonSprite() : ButtonSprite(BLA) { };
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

        sprite.colors[0] = { BEI,BEI,BEI,BLA,BLA,BEI,BEI,BEI };
        sprite.colors[1] = { BEI,BEI,BLA,BLA,BLA,BEI,BEI,BEI };
        sprite.colors[2] = { BLA,BEI,BEI,BLA,BLA,BEI,BEI,BEI };
        sprite.colors[3] = { BLA,BLA,BLA,BLA,BLA,BLA,BLA,BEI };
        sprite.colors[4] = { BEI,BEI,BEI,BLA,BLA,BEI,BLA,BEI };
        sprite.colors[5] = { BEI,BEI,BEI,BLA,BLA,BEI,BEI,BLA };
        sprite.colors[6] = { BEI,BEI,BLA,BEI,BEI,BLA,BLA,BEI };
        sprite.colors[7] = { BEI,BLA,BLA,BEI,BEI,BEI,BEI,BEI };

        FlipSprite();
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

        sprite.colors[0] = { YEL,YEL,YEL,YEL,YEL,YEL,YEL,YEL };
        sprite.colors[1] = { YEL,YEL,YEL,YEL,YEL,YEL,YEL,YEL };
        sprite.colors[2] = { YEL,WHI,WHI,YEL,YEL,YEL,YEL,YEL };
        sprite.colors[3] = { WHI,YEL,YEL,WHI,WHI,WHI,WHI,WHI };
        sprite.colors[4] = { WHI,YEL,YEL,WHI,YEL,WHI,YEL,WHI };
        sprite.colors[5] = { YEL,WHI,WHI,YEL,YEL,YEL,YEL,YEL };
        sprite.colors[6] = { YEL,YEL,YEL,YEL,YEL,YEL,YEL,YEL };
        sprite.colors[7] = { YEL,YEL,YEL,YEL,YEL,YEL,YEL,YEL };
    }
};

class Door : public GameObject
{
public:
    Door()
    {
        name = "Door";

        sprite.colors[0] = { YEL,YEL,BLA,BLA,BLA,BLA,YEL,YEL };
        sprite.colors[1] = { YEL,BLA,YEL,YEL,YEL,YEL,BLA,YEL };
        sprite.colors[2] = { YEL,BLA,YEL,YEL,YEL,YEL,BLA,YEL };
        sprite.colors[3] = { BLA,BLA,BLA,BLA,BLA,BLA,BLA,BLA };
        sprite.colors[4] = { BLA,BLA,BLA,YEL,YEL,BLA,BLA,BLA };
        sprite.colors[5] = { BLA,BLA,BLA,YEL,YEL,BLA,BLA,BLA };
        sprite.colors[6] = { BLA,BLA,YEL,BLA,BLA,YEL,BLA,BLA };
        sprite.colors[7] = { BLA,BLA,BLA,BLA,BLA,BLA,BLA,BLA };
    }
};
