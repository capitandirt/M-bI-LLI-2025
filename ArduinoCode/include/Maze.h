#pragma once
#include "Arduino.h"
#include "ASMR.h"
#include "Vec2.h"

enum WallState: byte
{
    UNDEFINED,
    PASS,
    WALL
};

struct CellWalls
    {
        WallState down : 2; //bitfield, эта ПЕРЕМЕННАЯ занимает ровно 2 бита, кайф вообще
        WallState left : 2;
        WallState up : 2;
        WallState right : 2;
        CellWalls(byte down_ = UNDEFINED, byte left_ = UNDEFINED, byte up_ = UNDEFINED, byte right_ = UNDEFINED)   
        {
            down = (WallState)down_;
            left = (WallState)left_;
            up = (WallState)up_;
            right = (WallState)right_;
        }
    };

#define MAZE_MEMORY_SIZE (MAZE_SIZE*MAZE_SIZE)

#define SET_WALL(wallStoraged, wall) wallStoraged = ((wallStoraged) != UNDEFINED ? (wall) : (wallStoraged))

#define cellXY(x, y) (data[MAZE_SIZE *  (y) + (x)])
#define cellVec(coord) (data[MAZE_SIZE *  (coord.y) + (coord.x)])

class Maze
{
private:
    enum Wall: byte
    {
        DOWN,
        LEFT,
        UP,
        RIGHT
    };
    struct CellStorageUnit
    {
        WallState right : 2;
        WallState down : 2;
    };
    CellStorageUnit data[MAZE_MEMORY_SIZE];
public:
    Maze()
    {
        for(int i = 0; i < MAZE_MEMORY_SIZE; i++)
        {
            data[i].right = UNDEFINED;
            data[i].down = UNDEFINED;
        }
    }
    CellWalls getWalls(Vec2 coord) const //конст метод никак не изменяет класс, поэтому const ставится после
    {
        CellWalls walls;
        if(coord.y != MAZE_SIZE - 1 ) walls.down = cellXY(coord.x, coord.y).down;
        else walls.down = WALL;
        if(coord.x != MAZE_SIZE - 1 ) walls.right = cellXY(coord.x, coord.y).right;  
        else walls.right = WALL;
        if(coord.x != 0 && coord.x) walls.left = cellXY(coord.x - 1, coord.y).right;
        else walls.left = WALL;
        if(coord.y != 0 && coord.y) walls.up = cellXY(coord.x, coord.y - 1).down;
        else walls.up = WALL;
        return walls;
    }
    // {DOWN, LEFT, UP, RIGHT}  
    void setWall(Vec2 coord, CellWalls walls)
    {
        cellXY(coord.x, coord.y).down = walls.down;
        cellXY(coord.x, coord.y).right = walls.right;
        cellXY(coord.x - 1, coord.y).right = walls.left;        
        cellXY(coord.x, coord.y - 1).down = walls.up;
    }
};

#undef CellXY