#pragma once
#include "Arduino.h"
#include "ASMR.h"
#include "MazeCoord.h"

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

#define MAZE_MEMORY_SIZE ((MAZE_SIZE*MAZE_SIZE + 1) / 2)

#define SET_WALL(wallStoraged, wall) wallStoraged = ((wallStoraged) != UNDEFINED ? (wall) : (wallStoraged))

#define cellXY(x, y) (data[(MAZE_SIZE *  (y) + (x) + 1) / 2])
#define cellVec(coord) (cellXY(coord.x, coord.y))
#define highOrLow(x, y) (((y) * MAZE_SIZE + (x)) % 2 != 0) //если так, то high
#define highOrLowVec(coord) (highOrLow(coord.x, coord.y))

class Maze
{
private:
    struct CellStorageUnit
    {
        WallState highRight : 2;
        WallState highDown : 2;
        WallState lowRight : 2;
        WallState lowDown : 2;
    };
    CellStorageUnit data[MAZE_MEMORY_SIZE];
public:
    Maze()
    {
        for(int i = 0; i < MAZE_MEMORY_SIZE; i++)
        {
            data[i].highRight = UNDEFINED;
            data[i].highDown = UNDEFINED;
            data[i].lowDown = UNDEFINED;
            data[i].lowRight = UNDEFINED;
        }
    }
    CellWalls getWalls(MazeCoord coord) const //конст метод никак не изменяет класс, поэтому const ставится после
    {
        CellWalls walls;
        if(coord.y != MAZE_SIZE - 1)
        {
            if(highOrLowVec(coord) ) walls.down = cellVec(coord).highDown;
            else walls.down = cellVec(coord).lowDown;
        }
        else walls.down = WALL;
        if(coord.x != MAZE_SIZE - 1 ) 
        {
            if(highOrLowVec(coord) ) walls.right = cellVec(coord).highRight;
            else walls.right = cellVec(coord).lowRight;
        }  
        else walls.right = WALL;
        if(coord.x != 0 && coord.x)
        {
            if(highOrLow(coord.x - 1, coord.y) ) walls.left = cellXY(coord.x - 1, coord.y).highRight;
            else walls.left = cellXY(coord.x - 1, coord.y).lowRight;
        }
        else walls.left = WALL;
        if(coord.y != 0 && coord.y)
        {
            if(highOrLow(coord.x, coord.y - 1) ) walls.up = cellXY(coord.x, coord.y - 1).highDown;
            else walls.up = cellXY(coord.x, coord.y - 1).lowDown;
        }
        else walls.up = WALL;
        return walls;
        // if(coord.x != MAZE_SIZE - 1 ) walls.right = cellXY(coord.x, coord.y).right;  
        // else walls.right = WALL;
        // if(coord.x != 0 && coord.x) walls.left = cellXY(coord.x - 1, coord.y).right;
        // else walls.left = WALL;
        // if(coord.y != 0 && coord.y) walls.up = cellXY(coord.x, coord.y - 1).down;
        // else walls.up = WALL;
        // return walls;
    }
    // {DOWN, LEFT, UP, RIGHT}  
    void setWall(MazeCoord coord, CellWalls walls)
    {
        if(highOrLowVec(coord))
        {
            cellVec(coord).highRight = walls.right;
            cellVec(coord).highDown = walls.down;
            cellXY(coord.x - 1, coord.y).lowRight = walls.left;
        }
        else
        {
            cellVec(coord).lowRight = walls.right;
            cellVec(coord).lowDown = walls.down;
            cellXY(coord.x - 1, coord.y).highRight = walls.left;
        }
        if(highOrLow(coord.x, coord.y - 1)) cellXY(coord.x, coord.y - 1).highDown = walls.up;
        else cellXY(coord.x, coord.y - 1).lowDown = walls.up;
        // cellXY(coord.x, coord.y).down = walls.down;
        // cellXY(coord.x, coord.y).right = walls.right;
        // cellXY(coord.x - 1, coord.y).right = walls.left;        
        // cellXY(coord.x, coord.y - 1).down = walls.up;
    }
};

#undef CellXY
#undef CellVec
#undef highOrLow
#undef highOrLowVec