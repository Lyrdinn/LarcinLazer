#include <iostream>
#include <Windows.h>
#include <conio.h>
#include <map>
#include "tile.h"
#include "draw.h"
#include "level.h"

using namespace std;
typedef map<pair<int, int>, Tile*> TileMap;

TileMap tileMap;
Tile* startPos;
Tile* playerPos;
Player* player;
Screen screen;

void StartLevel(Level level)
{
    // Build TileMap
    for (int y = 0; y < LEVEL_HEIGHT; y++)
    {
        for (int x = 0; x < LEVEL_WIDTH; x++)
        {
            char tileType = level.map[y][x];

            Tile* tile;

            switch (tileType) {
            case 'w':
                tile = new WallTile(y, x);
                break;
            case ' ':
                tile = new FloorTile(y, x);
                break;
            case 'l':
                tile = new LaserTile(y, x);
                break;
            case 'd':
                tile = new DoorTile(y, x);
                break;
            default:
                tile = new Tile(y, x);
                break;
            }
            
            tileMap[make_pair(y, x)] = tile;
            screen.DrawSprite(*tile, tile->sprite);
        }
    }

    // Init Start Position
    startPos = tileMap.at(level.startPosCoordinates);

    // Init Player
    player = new Player();
    playerPos = startPos;
    playerPos->object = player;
    screen.DrawSprite(*playerPos, player->sprite);

    // Draw everything on screen
    screen.UpdateScreen();
}

void MovePlayer(Tile* newPlayerPos)
{
    screen.MoveObject(*playerPos, *newPlayerPos);
    newPlayerPos->object = player;
    playerPos->object = nullptr;
    playerPos = newPlayerPos;
}

void CheckForMovement() 
{
    Tile* newPlayerPos;

    switch (_getch()) {
    case 'z':
        newPlayerPos = tileMap.at(make_pair(playerPos->GetY() - 1, playerPos->GetX()));
        break;
    case 's':
        newPlayerPos = tileMap.at(make_pair(playerPos->GetY() + 1, playerPos->GetX()));
        break;
    case 'd':
        newPlayerPos = tileMap.at(make_pair(playerPos->GetY(), playerPos->GetX() + 1));
        break;
    case 'q':
        newPlayerPos = tileMap.at(make_pair(playerPos->GetY(), playerPos->GetX() - 1));
        break;
    default:
        return;
    }

    if (newPlayerPos->isWalkable) MovePlayer(newPlayerPos);
    if (newPlayerPos->isDeadly) MovePlayer(startPos);
    screen.UpdateScreen();
}

int main()
{
    Level level = Level1();
    StartLevel(level);

    while (true)
    {
        CheckForMovement();
    }
    
    return 0;
}


