#pragma once
#include "Arduino.h"
class MazeCoord
{
public:
    int8_t x, y;
    bool operator ==(const MazeCoord& second) const
    {
        return x == second.x && y == second.y;
    } 
    bool operator !=(const MazeCoord& second) const
    {
        return x != second.x || y != second.y;
    }
    MazeCoord operator +(const MazeCoord& second) const
    {
        return {x + second.x, y + second.y};
    }
    MazeCoord operator -(const MazeCoord& second) const
    {
        return {x - second.x, y - second.y};
    }
    String string()
    {
        return ("{" + (String)x + ";" + (String)y + "}");
    }
};