#pragma once
#include <Windows.h>
#include <vector>
#include "global.h"
using namespace std;

class Level
{
public:
	char map[LEVEL_HEIGHT][LEVEL_WIDTH];

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
		{ ' ', ' ', ' ', ' ', 'l', ' ' , 'p'},
		{ 'e', 'l', ' ', ' ', ' ', ' ' , ' '} };
		
		int yOffset = 3;
		int xOffset = 16;

		for (int y = 0; y < height; y++)
		{
			for (int x = 0; x < width; x++)
			{
				map[yOffset + y][xOffset + x] = smallLevel[y][x];
			}
		}
	}
};

class Level2 : public Level
{
public:

	Level2() : Level()
	{
		const int width = 8;
		const int height = 5;

		char smallLevel[height][width] = {
		{ 'w', 'w', 'w', 'l', ' ', 'd' , 'e', 'w'},
		{ 'w', 'w', 'w', ' ', ' ', 'w' , 'w', 'w'},
		{ 'p', ' ', ' ', ' ', ' ', 'l' , ' ', ' '},
		{ ' ', ' ', 'l', ' ', ' ', 'l' , ' ', 'k'},
		{ ' ', ' ', 'l', ' ', ' ', ' ' , ' ', ' '} };

		int yOffset = 3;
		int xOffset = 16;

		for (int y = 0; y < height; y++)
		{
			for (int x = 0; x < width; x++)
			{
				map[yOffset + y][xOffset + x] = smallLevel[y][x];
			}
		}
	}
};



