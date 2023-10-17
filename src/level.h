#pragma once
#include <Windows.h>
#include <vector>
#include <map>
#include "global.h"
using namespace std;

class Level
{
public:
	char lvlMap[LEVEL_HEIGHT][LEVEL_WIDTH];
	bool jewelIsUnlocked = false;
	int playerStartDir;

	Level()
	{
		for (int y = 0; y < LEVEL_HEIGHT; y++)
		{
			for (int x = 0; x < LEVEL_WIDTH; x++)
			{
				lvlMap[y][x] = 'w';
			}
		}
	}
};

class Level1 : public Level
{
public:

	Level1() : Level()
	{
		playerStartDir = 1;
		const int width = 7;
		const int height = 3;

		char smallLevel[height][width] = {
		{ ' ', ' ', ' ', ' ', ' ', 'l' , ' '},
		{ 'p', ' ', 'l', 'j', ' ', ' ' , ' '},
		{ ' ', ' ', ' ', ' ', ' ', 'l' , 'e'} };
		
		int yOffset = 3;
		int xOffset = 4;

		for (int y = 0; y < height; y++)
		{
			for (int x = 0; x < width; x++)
			{
				lvlMap[yOffset + y][xOffset + x] = smallLevel[y][x];
			}
		}
	}
};

class Level2 : public Level
{
public:

	Level2() : Level()
	{
		playerStartDir = 1;
		const int width = 8;
		const int height = 5;

		char smallLevel[height][width] = {
		{ 'w', 'w', 'w', 'l', ' ', ' ' , 'e', 'w'},
		{ 'w', 'w', 'w', ' ', ' ', 'w' , 'w', 'w'},
		{ 'p', ' ', ' ', ' ', ' ', 'l' , ' ', ' '},
		{ ' ', ' ', 'l', ' ', ' ', 'l' , ' ', 'j'},
		{ ' ', ' ', 'l', ' ', ' ', ' ' , ' ', ' '} };

		int yOffset = 2;
		int xOffset = 4;

		for (int y = 0; y < height; y++)
		{
			for (int x = 0; x < width; x++)
			{
				lvlMap[yOffset + y][xOffset + x] = smallLevel[y][x];
			}
		}
	}
};

class Level3 : public Level
{
public:

	Level3() : Level()
	{
		playerStartDir = -1;
		const int width = 11;
		const int height = 4;

		char smallLevel[height][width] = {
		{ 'e', 'd', ' ', ' ', ' ', 'd' , ' ', ' ', ' ', ' ', 'p'},
		{ 'w', 'w', 'l', ' ', 'w', 'w' , 'w', ' ', 'l', 'w', 'w'},
		{ 'w', 'k', 'l', ' ', ' ', 'w' , 'l', ' ', ' ', ' ', 'w'},
		{ 'w', ' ', ' ', ' ', 'l', 'w' , 'j', ' ', 'l', 'k', 'w'} };

		int yOffset = 3;
		int xOffset = 3;

		for (int y = 0; y < height; y++)
		{
			for (int x = 0; x < width; x++)
			{
				lvlMap[yOffset + y][xOffset + x] = smallLevel[y][x];
			}
		}
	}
};

class Level4 : public Level
{
public:

	Level4() : Level()
	{
		playerStartDir = -1;
		const int width = 9;
		const int height = 3;

		char smallLevel[height][width] = {
		{ 'e', ' ', ' ', 'w', 'w' , 'w', '0', 'l', 'p'},
		{ ' ', 'l', ' ', 'w', 'w' , 'w', ' ', ' ', ' '},
		{ ' ', ' ', '0', 'w', 'w' , 'w', 'l', 'j', 'l'} };

		int yOffset = 3;
		int xOffset = 3;

		for (int y = 0; y < height; y++)
		{
			for (int x = 0; x < width; x++)
			{
				lvlMap[yOffset + y][xOffset + x] = smallLevel[y][x];
			}
		}
	}
};

class Level5 : public Level
{
public:

	Level5() : Level()
	{
		playerStartDir = 1;
		const int width = 13;
		const int height = 3;

		char smallLevel[height][width] = {
		{ 'j', 'l', '2', 'w', ' ' , ' ', 'e', 'l', '0', 'w', 'l', ' ', '1'},
		{ ' ', 'l', ' ', 'w', ' ' , 'l', 'l', 'l', ' ', 'w', 'l', ' ', 'l'},
		{ '1', ' ', ' ', 'w', '2' , 'l', 'p', ' ', ' ', 'w', '0', ' ', ' '} };

		int yOffset = 3;
		int xOffset = 1;

		for (int y = 0; y < height; y++)
		{
			for (int x = 0; x < width; x++)
			{
				lvlMap[yOffset + y][xOffset + x] = smallLevel[y][x];
			}
		}
	}
};

class Level6 : public Level
{
public:

	Level6() : Level()
	{
		playerStartDir = 1;
		const int width = 13;
		const int height = 8;

		char smallLevel[height][width] = {
		{ 'p', ' ', 'w', 'w', 'k' , 'l', 'l', ' ', ' ', ' ', ' ', 'l', '1'},
		{ 'l', ' ', 'w', 'w', ' ' , 'l', 'l', ' ', 'l', 'l', ' ', 'l', ' '},
		{ 'l', ' ', 'w', 'w', ' ' , 'l', 'l', ' ', 'l', 'l', ' ', ' ', ' '},
		{ ' ', ' ', 'w', 'w', ' ' , ' ', ' ', ' ', 'l', 'j', ' ', 'l', ' '},
		{ ' ', 'l', 'w', 'w', 'w' , 'w', 'w', 'w', 'w', 'w', 'w', 'w', 'w'},
		{ ' ', 'l', 'w', 'w', ' ' , 'l', 'l', 'l', 'l', ' ', ' ', ' ', ' '},
		{ ' ', ' ', 'w', 'w', ' ' , ' ', ' ', ' ', 'd', ' ', 'l', 'l', ' '},
		{ '2', '1', 'w', 'w', '2' , 'l', 'l', 'l', 'l', 'l', 'l', 'l', 'e'} };
		 
		int yOffset = 1;
		int xOffset = 1;

		for (int y = 0; y < height; y++)
		{
			for (int x = 0; x < width; x++)
			{
				lvlMap[yOffset + y][xOffset + x] = smallLevel[y][x];
			}
		}
	}
};

// Empty Template 
/*
char smallLevel[height][width] = {
{ ' ', ' ', ' ', ' ', ' ', ' ' , ' ', ' '},
{ ' ', ' ', ' ', ' ', ' ', ' ' , ' ', ' '},
{ ' ', ' ', ' ', ' ', ' ', ' ' , ' ', ' '},
{ ' ', ' ', ' ', ' ', ' ', ' ' , ' ', ' '},
{ ' ', ' ', ' ', ' ', ' ', ' ' , ' ', ' '} };
*/
