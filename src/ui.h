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

	ButtonSprite hovered;
	ButtonSprite unhovered;

	Button(int x, int y)
	{
		_x = x;
		_y = y;
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
	Level* _level;
public :
	LevelButton(Level* level, int x, int y) : Button(x, y)
	{
		_level = level;

		for (int i = 0; i < BUTTON_HEIGHT; i++)
		{
			for (int j = 0; j < BUTTON_WIDTH; j++)
			{
				//Unhovered
				unhovered.characters[i][j] = ' ';
				unhovered.colors[i][j] = BLA;

				//Hovered
				hovered.characters[i][j] = ' ';
				hovered.colors[i][j] = GRE;
			}
		}

		for (int i = 2; i < 59; i++)
		{
			unhovered.characters[1][i] = ' ';
			unhovered.colors[1][i] = WHI;
			hovered.characters[1][i] = ' ';
			hovered.colors[1][i] = WHI;
		}
		for (int i = 2; i < 59; i++)
		{
			unhovered.characters[7][i] = ' ';
			unhovered.colors[7][i] = WHI;
			hovered.characters[7][i] = ' ';
			hovered.colors[7][i] = WHI;
		}
		for (int i = 1; i < 7; i++)
		{
			unhovered.characters[i][2] = ' ';
			unhovered.colors[i][2] = WHI;
			hovered.characters[i][2] = ' ';
			hovered.colors[i][2] = WHI;
		}
		for (int i = 1; i < 7; i++)
		{
			unhovered.characters[i][58] = ' ';
			unhovered.colors[i][58] = WHI;
			hovered.characters[i][58] = ' ';
			hovered.colors[i][58] = WHI;
		}
	}

	Level* GetLevel()
	{
		return _level;
	}
};

class Level1Button : public LevelButton
{
public:
	Level1Button(Level* level, int x, int y) : LevelButton(level, x, y)
	{
		unhovered.colors[2][30] = WHI;
		unhovered.colors[3][29] = WHI;
		unhovered.colors[3][30] = WHI;
		unhovered.colors[4][30] = WHI;
		unhovered.colors[5][30] = WHI;
		unhovered.colors[6][30] = WHI;
		unhovered.colors[6][29] = WHI;
		unhovered.colors[6][31] = WHI;

		hovered.colors[2][30] = WHI;
		hovered.colors[3][29] = WHI;
		hovered.colors[3][30] = WHI;
		hovered.colors[4][30] = WHI;
		hovered.colors[5][30] = WHI;
		hovered.colors[6][30] = WHI;
		hovered.colors[6][29] = WHI;
		hovered.colors[6][31] = WHI;
	}
};

class Level2Button : public LevelButton
{
public:
	Level2Button(Level* level, int x, int y) : LevelButton(level, x, y)
	{
		unhovered.colors[2][29] = WHI;
		unhovered.colors[2][30] = WHI;
		unhovered.colors[3][28] = WHI;
		unhovered.colors[3][31] = WHI;
		unhovered.colors[4][30] = WHI;
		unhovered.colors[5][29] = WHI;
		unhovered.colors[6][28] = WHI;
		unhovered.colors[6][29] = WHI;
		unhovered.colors[6][30] = WHI;
		unhovered.colors[6][31] = WHI;

		hovered.colors[2][29] = WHI;
		hovered.colors[2][30] = WHI;
		hovered.colors[3][28] = WHI;
		hovered.colors[3][31] = WHI;
		hovered.colors[4][30] = WHI;
		hovered.colors[5][29] = WHI;
		hovered.colors[6][28] = WHI;
		hovered.colors[6][29] = WHI;
		hovered.colors[6][30] = WHI;
		hovered.colors[6][31] = WHI;
	}
};

class Level3Button : public LevelButton
{
public:
	Level3Button(Level* level, int x, int y) : LevelButton(level, x, y)
	{
		unhovered.colors[2][29] = WHI;
		unhovered.colors[2][30] = WHI;
		unhovered.colors[3][31] = WHI;
		unhovered.colors[4][29] = WHI;
		unhovered.colors[4][30] = WHI;
		unhovered.colors[5][31] = WHI;
		unhovered.colors[6][29] = WHI;
		unhovered.colors[6][30] = WHI;

		hovered.colors[2][29] = WHI;
		hovered.colors[2][30] = WHI;
		hovered.colors[3][31] = WHI;
		hovered.colors[4][29] = WHI;
		hovered.colors[4][30] = WHI;
		hovered.colors[5][31] = WHI;
		hovered.colors[6][29] = WHI;
		hovered.colors[6][30] = WHI;
	}
};

class Level4Button : public LevelButton
{
public:
	Level4Button(Level* level, int x, int y) : LevelButton(level, x, y)
	{
		unhovered.colors[2][29] = WHI;
		unhovered.colors[2][30] = WHI;
		unhovered.colors[3][28] = WHI;
		unhovered.colors[3][30] = WHI;
		unhovered.colors[4][28] = WHI;
		unhovered.colors[4][29] = WHI;
		unhovered.colors[4][30] = WHI;
		unhovered.colors[4][31] = WHI;
		unhovered.colors[5][30] = WHI;
		unhovered.colors[6][30] = WHI;

		hovered.colors[2][29] = WHI;
		hovered.colors[2][30] = WHI;
		hovered.colors[3][28] = WHI;
		hovered.colors[3][30] = WHI;
		hovered.colors[4][28] = WHI;
		hovered.colors[4][29] = WHI;
		hovered.colors[4][30] = WHI;
		hovered.colors[4][31] = WHI;
		hovered.colors[5][30] = WHI;
		hovered.colors[6][30] = WHI;
	}
};

class Level5Button : public LevelButton
{
public:
	Level5Button(Level* level, int x, int y) : LevelButton(level, x, y)
	{
		unhovered.colors[2][28] = WHI;
		unhovered.colors[2][29] = WHI;
		unhovered.colors[2][30] = WHI;
		unhovered.colors[2][31] = WHI;
		unhovered.colors[3][28] = WHI;
		unhovered.colors[4][28] = WHI;
		unhovered.colors[4][29] = WHI;
		unhovered.colors[4][30] = WHI;
		unhovered.colors[5][31] = WHI;
		unhovered.colors[6][28] = WHI;
		unhovered.colors[6][29] = WHI;
		unhovered.colors[6][30] = WHI;
		unhovered.colors[6][31] = WHI;

		hovered.colors[2][28] = WHI;
		hovered.colors[2][29] = WHI;
		hovered.colors[2][30] = WHI;
		hovered.colors[2][31] = WHI;
		hovered.colors[3][28] = WHI;
		hovered.colors[4][28] = WHI;
		hovered.colors[4][29] = WHI;
		hovered.colors[4][30] = WHI;
		hovered.colors[5][31] = WHI;
		hovered.colors[6][28] = WHI;
		hovered.colors[6][29] = WHI;
		hovered.colors[6][30] = WHI;
		hovered.colors[6][31] = WHI;
	}
};

class Level6Button : public LevelButton
{
public:
	Level6Button(Level* level, int x, int y) : LevelButton(level, x, y)
	{
		unhovered.colors[2][28] = WHI;
		unhovered.colors[2][29] = WHI;
		unhovered.colors[2][30] = WHI;
		unhovered.colors[2][31] = WHI;
		unhovered.colors[3][28] = WHI;
		unhovered.colors[4][28] = WHI;
		unhovered.colors[4][29] = WHI;
		unhovered.colors[4][30] = WHI;
		unhovered.colors[4][31] = WHI;
		unhovered.colors[5][28] = WHI;
		unhovered.colors[5][31] = WHI;
		unhovered.colors[6][28] = WHI;
		unhovered.colors[6][29] = WHI;
		unhovered.colors[6][30] = WHI;
		unhovered.colors[6][31] = WHI;

		hovered.colors[2][28] = WHI;
		hovered.colors[2][29] = WHI;
		hovered.colors[2][30] = WHI;
		hovered.colors[2][31] = WHI;
		hovered.colors[3][28] = WHI;
		hovered.colors[4][28] = WHI;
		hovered.colors[4][29] = WHI;
		hovered.colors[4][30] = WHI;
		hovered.colors[4][31] = WHI;
		hovered.colors[5][28] = WHI;
		hovered.colors[5][31] = WHI;
		hovered.colors[6][28] = WHI;
		hovered.colors[6][29] = WHI;
		hovered.colors[6][30] = WHI;
		hovered.colors[6][31] = WHI;
	}
};