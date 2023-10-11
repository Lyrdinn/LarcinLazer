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

public :
	char characters[BUTTON_HEIGHT][BUTTON_WIDTH];
	int colors[BUTTON_HEIGHT][BUTTON_WIDTH];

	Button(int x, int y)
	{
		_x = x;
		_y = y;
		
		for (int i = 0; i < BUTTON_HEIGHT; i++)
		{
			for (int j = 0; j < BUTTON_WIDTH; j++)
			{
				characters[i][j] = 'B';
				colors[i][j] = 5; //95
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
};

class MenuButton : public Button
{
private :
	string _scene;
public :
	MenuButton(string scene, int x, int y) : Button(x, y)
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
	LevelButton(Level level, int x, int y) : Button(x, y)
	{
		_level = level;
	}

	Level GetLevel()
	{
		return _level;
	}
};