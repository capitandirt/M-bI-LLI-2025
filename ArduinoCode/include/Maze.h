#pragma once
#include "Arduino.h"
#include "ASMR.h"
struct Vec2
{
    int x, y;
};

#define MAZE_MEMORY_SIZE (MAZE_SIZE*MAZE_SIZE)

#define SET_WALL(wallStoraged, wall) wallStoraged = ((wallStoraged) != UNDEFINED ? (wall) : (wallStoraged))

#define cellXY(x, y) (data[MAZE_SIZE *  (y) + (x)])

class Maze
{
private:
    enum WALL_STATE: byte
    {
        UNDEFINED,
        NO,
        YES
    };
    enum Wall: byte
    {
        DOWN,
        LEFT,
        UP,
        RIGHT
    };
    struct Cell
    {
        Wall down : 2; //bitfield, эта ПЕРЕМЕННАЯ занимает ровно 2 бита, кайф вообще
        Wall left : 2;
        Wall up : 2;
        Wall right : 2;
    };
    struct CellStorageUnit
    {
        Wall right : 2;
        Wall down : 2;
    };
    CellStorageUnit data[MAZE_MEMORY_SIZE];
public:
    Cell getWalls(Vec2 coord)
    {
        
    }
    void setWall(Vec2 coord, Cell walls)
    {
        SET_WALL(cellXY(coord.x, coord.y).down, walls.down);
        SET_WALL(cellXY(coord.x, coord.y).right, walls.right);
    }
    void printMaze()
    {
        Serial.println("\n\n");
        Serial.print("+");
        for(int j = 0; j < MAZE_SIZE; j++)
        {
            Serial.print(String(" - ") + "+");
        }
        for(int i = 0; i < MAZE_SIZE; i++)
        {
            Serial.print("\n|");
            for(int j = 0; j < MAZE_SIZE; j++)
            {
                Serial.print(String("   "));
                if(cellXY(i, j).right) Serial.print("|");
                else Serial.print(".");
            }
            Serial.print("\n+");
            for(int j = 0; j < MAZE_SIZE; j++)
            {
                if(cellXY(i, j).down) Serial.print(" - ");
                else Serial.print(" . ");
                Serial.print("+");
            }
        }
    }
};
