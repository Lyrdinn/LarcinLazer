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
	int playerStartDir; //Direction at which the player starts

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
		{ 'p', ' ', 'l', ' ', ' ', ' ' , ' '},
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
		{ 'w', 'w', 'w', 'l', ' ', 'd' , 'e', 'w'},
		{ 'w', 'w', 'w', ' ', ' ', 'w' , 'w', 'w'},
		{ 'p', ' ', ' ', ' ', ' ', 'l' , ' ', ' '},
		{ ' ', ' ', 'l', ' ', ' ', 'l' , ' ', 'k'},
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
		{ 'w', ' ', ' ', ' ', 'l', 'w' , ' ', ' ', 'l', 'k', 'w'} };

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
		{ ' ', ' ', '0', 'w', 'w' , 'w', 'l', ' ', 'l'} };

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

// Empty Template 
/*
char smallLevel[height][width] = {
{ ' ', ' ', ' ', ' ', ' ', ' ' , ' ', ' '},
{ ' ', ' ', ' ', ' ', ' ', ' ' , ' ', ' '},
{ ' ', ' ', ' ', ' ', ' ', ' ' , ' ', ' '},
{ ' ', ' ', ' ', ' ', ' ', ' ' , ' ', ' '},
{ ' ', ' ', ' ', ' ', ' ', ' ' , ' ', ' '} };
*/
