#include <iostream>
#include <Windows.h>

void InitializeBuffer()
{
    const int SCREEN_WIDTH = 200;
    const int SCREEN_HEIGHT = 200;

    HANDLE hOutput = (HANDLE)GetStdHandle(STD_OUTPUT_HANDLE);

    COORD dwBufferSize = { SCREEN_WIDTH,SCREEN_HEIGHT };
    COORD dwBufferCoord = { 0, 0 };
    SMALL_RECT rcRegion = { 0, 0, SCREEN_WIDTH - 1, SCREEN_HEIGHT - 1 };

    CHAR_INFO buffer[SCREEN_HEIGHT][SCREEN_WIDTH];

    ReadConsoleOutput(hOutput, (CHAR_INFO*)buffer, dwBufferSize, dwBufferCoord, &rcRegion);

    buffer[6][14].Char.AsciiChar = 'I';
    buffer[6][14].Attributes = 15;
    buffer[6][15].Char.AsciiChar = ' ';
    buffer[6][15].Attributes = 15;
    buffer[6][16].Char.AsciiChar = 'S';
    buffer[6][16].Attributes = 15;

    buffer[5][17].Char.AsciiChar = ' ';
    buffer[5][17].Attributes = 95;
    buffer[5][18].Char.AsciiChar = ' ';
    buffer[5][18].Attributes = 95;
    buffer[5][19].Char.AsciiChar = ' ';
    buffer[5][19].Attributes = 95;
    buffer[6][17].Char.AsciiChar = 'Y';
    buffer[6][17].Attributes = 95;
    buffer[6][18].Char.AsciiChar = 'O';
    buffer[6][18].Attributes = 95;
    buffer[6][19].Char.AsciiChar = 'U';
    buffer[6][19].Attributes = 95;


    buffer[5][11].Char.AsciiChar = 'B';
    buffer[5][11].Attributes = 95;
    buffer[5][12].Char.AsciiChar = ' ';
    buffer[5][12].Attributes = 95;
    buffer[5][13].Char.AsciiChar = 'A';
    buffer[5][13].Attributes = 95;
    buffer[6][11].Char.AsciiChar = 'B';
    buffer[6][11].Attributes = 95;
    buffer[6][12].Char.AsciiChar = ' ';
    buffer[6][12].Attributes = 95;
    buffer[6][13].Char.AsciiChar = 'A';
    buffer[6][13].Attributes = 95;

    buffer[9][10].Char.AsciiChar = 'B';
    buffer[9][10].Attributes = 95;
    buffer[9][11].Char.AsciiChar = ' ';
    buffer[9][11].Attributes = 95;
    buffer[9][12].Char.AsciiChar = 'A';
    buffer[9][12].Attributes = 95;
    buffer[10][10].Char.AsciiChar = ' ';
    buffer[10][10].Attributes = 95;
    buffer[10][11].Char.AsciiChar = ' ';
    buffer[10][11].Attributes = 95;
    buffer[10][12].Char.AsciiChar = ' ';
    buffer[10][12].Attributes = 95;
    buffer[11][10].Char.AsciiChar = 'B';
    buffer[11][10].Attributes = 95;
    buffer[11][11].Char.AsciiChar = ' ';
    buffer[11][11].Attributes = 95;
    buffer[11][12].Char.AsciiChar = 'A';
    buffer[11][12].Attributes = 95;

    buffer[9][22].Char.AsciiChar = 'A';
    buffer[9][22].Attributes = 15;
    buffer[10][20].Char.AsciiChar = 'A';
    buffer[10][20].Attributes = 15;
    buffer[10][21].Char.AsciiChar = 'A';
    buffer[10][21].Attributes = 15;
    buffer[10][22].Char.AsciiChar = 'A';
    buffer[10][22].Attributes = 15;
    buffer[11][20].Char.AsciiChar = 'A';
    buffer[11][20].Attributes = 15;
    buffer[11][21].Char.AsciiChar = 'A';
    buffer[11][21].Attributes = 15;
    buffer[11][22].Char.AsciiChar = 'A';
    buffer[11][22].Attributes = 15;

    WriteConsoleOutput(hOutput, (CHAR_INFO*)buffer, dwBufferSize, dwBufferCoord, &rcRegion);
}


int main()
{
    InitializeBuffer();
    return 0;
}
