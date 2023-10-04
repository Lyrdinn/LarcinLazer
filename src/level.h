#pragma once
#include <Windows.h>
#include <vector>
#include "global.h"
using namespace std;

class Level
{
public:
	char map[LEVEL_HEIGHT][LEVEL_WIDTH];

	pair<int, int> startPosCoordinates;

	Level()
	{
		for (int y = 0; y < LEVEL_HEIGHT; y++)
		{
			for (int x = 0; x < LEVEL_WIDTH; x++)
			{
				map[y][x] = 'w';
			}
		}
	}
};

class Level1 : public Level
{
public:

	Level1() : Level()
	{
		const int width = 7;
		const int height = 3;

		char smallLevel[height][width] = {
		{ ' ', 'l', ' ', ' ', ' ', ' ' , ' '},
		{ ' ', ' ', ' ', ' ', 'l', ' ' , ' '},
		{ 'd', 'l', ' ', ' ', ' ', ' ' , ' '} };
		
		int yOffset = 3; //(LEVEL_HEIGHT / 2) -(height / 2);
		int xOffset = 16; //(LEVEL_WIDTH / 2) -(width / 2);

		for (int y = 0; y < height; y++)
		{
			for (int x = 0; x < width; x++)
			{
				int yFinal = yOffset + y;
				int xFinal = xOffset + x;
				map[yOffset + y][xOffset + x] = smallLevel[y][x];
			}
		}

		startPosCoordinates = make_pair(yOffset + height - 1, xOffset + width - 1);
	}
};



