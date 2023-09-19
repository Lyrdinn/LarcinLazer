#include <iostream>
#include "grid.h"
using namespace std;

class GameObject
{
    private:
        string _name;

    public :
        GameObject(){}

        GameObject(string name)
        {
            _name = name;
        }

        string GetName()
        {
            return _name;
        }
};

class Tile
{
    private :
        int _x, _y;

    public : 
        GameObject Object;

        Tile(int x, int y)
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
