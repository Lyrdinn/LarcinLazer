#pragma once
#include <string>
using namespace std;

class GameObject
{
public:
    string name;

    string text;

    int colors[6];
};

class Baba : public GameObject
{
public:
    Baba()
    {
        name = "Baba";
        text = "      ";

        for (auto& color : colors) {
            color = 95;
        }    
    }
};

class BabaText : public GameObject
{
public:
    BabaText()
    {
        name = "BabaText";
        text = "B AB A";
        
        for (auto& color : colors) {
            color = 95;
        }
    }
};