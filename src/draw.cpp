#include "draw.h"

void Screen::ReadOutput()
{
    ReadConsoleOutput(hOutput, (CHAR_INFO*)buffer, dwBufferSize, dwBufferCoord, &rcRegion);
}

void Screen::ClearScreen()
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

void Screen::LoadImage(string path, CHAR_INFO buf[SCREEN_HEIGHT][SCREEN_WIDTH])
{
    fstream myfile;
    myfile.open(path, ios::in);

    if (!myfile) {
        cout << "Can't find file";
    }
    else {
        char ch;
        int i = 0;
        int j = 0;
        bool negative = false;

        while (1) {
            myfile >> ch;

            if (myfile.eof()) break;
            else if (isdigit(ch)) {
                if (ch == '0') buf[j][i].Attributes = YEL;
                else if (ch == '1') buf[j][i].Attributes = WHI;
                else if (ch == '2') buf[j][i].Attributes = BLA;
                else if (ch == '3') buf[j][i].Attributes = RED;

                i++;
                if (i == 120) {
                    i = 0;
                    j++;
                }
            }
        }
    }
}

void Screen::DrawMenuScreen()
{
    for (int j = 0; j < SCREEN_HEIGHT; j++)
    {
        for (int i = 0; i < SCREEN_WIDTH; i++)
        {
            buffer[j][i] = menuImage[j][i];
        }
    }
}

void Screen::DrawWinScreen()
{
    for (int j = 0; j < SCREEN_HEIGHT; j++)
    {
        for (int i = 0; i < SCREEN_WIDTH; i++)
        {
            buffer[j][i] = winImage[j][i];
        }
    }
}

void Screen::DrawButton(Button* button, bool hovered)
{
    int x = button->GetX();
    int y = button->GetY();
    ButtonSprite buttonSprite = hovered ? button->hovered : button->unhovered;

    for (int i = 0; i < BUTTON_HEIGHT; i++)
    {
        for (int j = 0; j < BUTTON_WIDTH; j++)
        {
            buffer[y + i][x + j].Char.AsciiChar = buttonSprite.characters[i][j];
            buffer[y + i][x + j].Attributes = buttonSprite.colors[i][j];
        }
    }
}

void Screen::DrawLevelButton(LevelButton* levelButton, bool hovered)
{
    DrawButton(levelButton, hovered);

    if (!levelButton->GetLevel()->jewelIsUnlocked) return;

    Sprite jewelSprite = Jewel().sprite;
    int x = levelButton->GetX() + 46;
    int y = levelButton->GetY();

    for (int i = 0; i < TILE_HEIGHT; i++)
    {
        for (int j = 0; j < TILE_WIDTH; j++)
        {
            if (jewelSprite.colors[i][j] == YEL) continue;
            buffer[y + i][x + j].Char.AsciiChar = jewelSprite.characters[i][j];
            buffer[y + i][x + j].Attributes = jewelSprite.colors[i][j];
        }
    }
}

void Screen::DrawLevelSelectScreen()
{
    for (int i = 0; i < SCREEN_HEIGHT; i++)
    {
        for (int j = 0; j < SCREEN_WIDTH; j++)
        {
            buffer[i][j].Char.AsciiChar = ' ';
            buffer[i][j].Attributes = YEL;
        }
    }

    for (int j = 0; j < SCREEN_HEIGHT; j++) buffer[j][10].Attributes = RED;
    for (int j = 0; j < SCREEN_HEIGHT; j++) buffer[j][40].Attributes = RED;
    for (int j = 0; j < SCREEN_HEIGHT; j++) buffer[j][80].Attributes = RED;
    for (int j = 0; j < SCREEN_HEIGHT; j++) buffer[j][110].Attributes = RED;

    for (int i = 0; i < SCREEN_WIDTH; i++) buffer[35][i].Attributes = RED;
    for (int i = 0; i < SCREEN_WIDTH; i++) buffer[36][i].Attributes = RED;
    for (int i = 0; i < SCREEN_WIDTH; i++) buffer[37][i].Attributes = RED;
}

void Screen::DrawSprite(Tile& tile, Sprite& sprite)
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

void Screen::MoveObject(Tile& oldTile, Tile& newTile)
{
    //Drawing the sprite on the new tile.
    DrawSprite(newTile, oldTile.object->sprite);

    //Recoloring the old tile.
    DrawSprite(oldTile, oldTile.sprite);

    //Update.
    UpdateScreen();
}

void Screen::UpdateScreen()
{
    WriteConsoleOutput(hOutput, (CHAR_INFO*)buffer, dwBufferSize, dwBufferCoord, &rcRegion);
}