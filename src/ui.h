#pragma once
#include "level.h"
#include "string.h"
#include <vector> 


//using namespace std;

class Button
{
private :
	//the real position in the buffer of your button
	int _x;
	int _y;
	int _width;
	int _height;

public :
	char characters[BUTTON_HEIGHT][BUTTON_WIDTH];
	int colors[BUTTON_HEIGHT][BUTTON_WIDTH];

	Button(int x, int y, int width, int height)
	{
		_x = x;
		_y = y;
		_width = width;
		_height = height;
		
		for (int y = 0; y < BUTTON_HEIGHT; y++)
		{
			for (int x = 0; x < BUTTON_WIDTH; x++)
			{
				characters[y][x] = 'B';
				colors[y][x] = 5; //95
			}
		}
	}

	int GetX()
	{
		return _x;
	}

	int GetY()
	{
		return _y;
	}

	int GetWidth()
	{
		return _width;
	}

	int getHeight()
	{
		return _height;
	}
};

class MenuButton : public Button
{
private :
	string _scene;
public :
	MenuButton(string scene, int x, int y, int width, int height) : Button(x,y, width, height)
	{
		_scene = scene;
	}

	string getScene()
	{
		return _scene;
	}
};

class LevelButton : public Button
{
private :
	Level _level;
public :
	LevelButton(Level level, int x, int y, int width, int height) : Button(x,y, width, height)
	{
		_level = level;
	}

	Level GetLevel()
	{
		return _level;
	}
};