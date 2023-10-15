#pragma once
#include <iostream>
#include <iostream>
#include <windows.h>
#include <string>
#include "tile.h"
#include "gameobject.h"
#include "global.h"
#include "ui.h"
#include <fstream>

using namespace std;

class Screen
{
private:
    HANDLE hOutput = (HANDLE)GetStdHandle(STD_OUTPUT_HANDLE);

    COORD dwBufferSize = { SCREEN_WIDTH,SCREEN_HEIGHT };
    COORD dwBufferCoord = { 0, 0 };
    SMALL_RECT rcRegion = { 0, 0, SCREEN_WIDTH - 1, SCREEN_HEIGHT - 1 };

    CHAR_INFO buffer[SCREEN_HEIGHT][SCREEN_WIDTH];
    CHAR_INFO menuImage[SCREEN_HEIGHT][SCREEN_WIDTH];

    void InitScreen()
    {
        ReadConsoleOutput(hOutput, (CHAR_INFO*)buffer, dwBufferSize, dwBufferCoord, &rcRegion);

        WriteConsoleOutput(hOutput, (CHAR_INFO*)buffer, dwBufferSize, dwBufferCoord, &rcRegion);
    }

public:
    Screen()
    {
        InitScreen();
        LoadMenuScreenImage();
    };

    void ReadOutput()
    {
        ReadConsoleOutput(hOutput, (CHAR_INFO*)buffer, dwBufferSize, dwBufferCoord, &rcRegion);
    }

    void ClearScreen()
    {
        for (int i = 0; i < SCREEN_HEIGHT; i++)
        {
            for (int j = 0; j < SCREEN_WIDTH; j++)
            {
                buffer[i][j].Char.AsciiChar = '\0';
                buffer[i][j].Attributes = 0;
            }
        }

        UpdateScreen();
    }

    void LoadMenuScreenImage()
    {
        fstream myfile;
        myfile.open("logo.txt", ios::in);

        if (!myfile) {
            cout << "Can't find file";
        }
        else {
            char ch;
            int i = 21;
            int j = 11;
            bool negative = false;

            while (1) {
                myfile >> ch;

                if (myfile.eof()) break;
                else if (ch == '\n') {
                    j++;
                    i = 21;
                }
                else if (isdigit(ch)) {
                    if (ch == '0') menuImage[j][i].Attributes = 0;
                    else if (ch == '1') menuImage[j][i].Attributes = WHI;
                    else if (ch == '2') menuImage[j][i].Attributes = BLA;
                    i++;
                }
            }
        }
    }

    void DrawMenuScreen()
    {
        for (int j = 0; j < SCREEN_HEIGHT; j++)
        {
            for (int i = 0; i < SCREEN_WIDTH; i++)
            {
                buffer[j][i].Char.AsciiChar = ' ';
                buffer[j][i].Attributes = YEL;
            }
        }

        for (int j = 10; j < 50; j++)
        {
            for (int i = 20; i < 100; i++)
            {
                buffer[j][i].Char.AsciiChar = ' ';
                buffer[j][i].Attributes = BLA;
            }
        }
        
        //buffer[12] = {BLA,WHI,BLA,WHI,WHI,WHI,WHI,BLA,BLA,0,0,0,0,BLA,BLA,WHI,WHI,WHI,WHI,WHI,WHI,WHI,WHI,WHI,BLA,BLA,BLA,BLA,WHI,WHI,WHI,WHI,WHI,WHI,WHI,WHI,BLA,BLA,BLA,0,0,BLA,BLA,WHI,WHI,WHI,WHI,WHI,WHI,WHI,WHI,WHI,BLA,BLA,BLA,BLA,WHI,WHI,WHI,WHI,BLA,BLA,BLA,BLA,WHI,WHI,WHI,WHI,BLA,BLA,0,BLA,WHI,WHI}
    }

    void DrawButtonUnHovered(Button* button)
    {
        int x = button->GetX();
        int y = button->GetY();

        for (int i = 0; i < BUTTON_HEIGHT; i++)
        {
            for (int j = 0; j < BUTTON_WIDTH; j++)
            {
                buffer[y + i][x + j].Char.AsciiChar = button -> characters[i][j];
                buffer[y + i][x + j].Attributes = button -> colors[i][j];
            }
        }
    }

    void DrawButtonHovered(Button * button)
    {
        int x = button->GetX();
        int y = button->GetY();

        for (int i = 0; i < BUTTON_HEIGHT; i++)
        {
            for (int j = 0; j < BUTTON_WIDTH; j++)
            {
                buffer[y + i][x + j].Attributes = 10;
            }
        }
    }

    void DrawLevelSelectScreen()
    {

    }

    void DrawSprite(Tile& tile, Sprite& sprite)
    {
        int x = tile.GetX();
        int y = tile.GetY();

        for (int i = 0; i < TILE_HEIGHT; i++)
        {
            for (int j = 0; j < TILE_WIDTH; j++)
            {
               buffer[y * TILE_HEIGHT + i][x * TILE_WIDTH + j].Char.AsciiChar = sprite.characters[i][j];
               buffer[y * TILE_HEIGHT + i][x * TILE_WIDTH + j].Attributes = sprite.colors[i][j];
            }
        }
    }

    void MoveObject(Tile& oldTile, Tile& newTile)
    {
        //Drawing the sprite on the new tile.
        DrawSprite(newTile, oldTile.object->sprite);

        //Recoloring the old tile.
        DrawSprite(oldTile, oldTile.sprite);

        //Update.
        UpdateScreen();
    }

    void UpdateScreen()
    {
        WriteConsoleOutput(hOutput, (CHAR_INFO*)buffer, dwBufferSize, dwBufferCoord, &rcRegion);
    }
};