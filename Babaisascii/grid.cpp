#include <iostream>
using namespace std;

class Object
{
    private:
        string _name;

    public :
        Object(){}

        Object(string name)
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
        Object Object;

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

int main()
{
    Tile tile(2, 5);
    Object Object("Baba");
    tile.Object = Object;

    cout << tile.Object.GetName() << " " << tile.GetX() << " " << tile.GetY()<< endl;
    return 0;
}

