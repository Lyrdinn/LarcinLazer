#include <iostream>
#include <Windows.h>

CHAR_INFO MoveDown(CHAR_INFO buffer, Tile tile)
{
	//moving bottom 3 characters
	buffer[tile.GetY() + 2][tile.GetX()] = buffer[tile.GetY()][tile.GetX()];
	buffer[tile.GetY() + 2][tile.GetX() + 1] = buffer[tile.GetY()][tile.GetX() + 1];
	buffer[tile.GetY() + 2][tile.GetX() + 2] = buffer[tile.GetY()][tile.GetX() + 2];
		
	//moving upper 3 characters
	buffer[tile.GetY() + 1][tile.GetX()] = buffer[tile.GetY() - 1][tile.GetX()];
	buffer[tile.GetY() + 1][tile.GetX() + 1] = buffer[tile.GetY() - 1][tile.GetX() + 1];
	buffer[tile.GetY() + 1][tile.GetX() + 2] = buffer[tile.GetY() - 1][tile.GetX() + 2];
	
	//we clean the previous buffer characters
	/*buffer[tile.GetY()][buffer.GetY() + 2] = '';
	buffer[tile.GetY() + 1][buffer.GetY() + 2] = '';
	buffer[tile.GetY() + 2][buffer.GetY() + 2] = '';
	buffer[tile.GetY()][buffer.GetY() + 2] = '';
	buffer[tile.GetY() + 1][buffer.GetY() + 2] = '';
	buffer[tile.GetY() + 2][buffer.GetY() + 2] = '';*/
}