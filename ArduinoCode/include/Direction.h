#pragma once
#include "Arduino.h"
class Direction // LEFT UP RIGHT DOWN
{
public:
    enum class Dir: uint8_t
    {
        RIGHT,
        UP,
        LEFT,
        DOWN,
    };
    static Dir fromRad(float rad)
    {
        Dir outDir;
        if(abs(rad - PI ) < 0.1) outDir = Direction::Dir::LEFT;
        else if(abs(rad - PI / 2) < 0.1) outDir = Direction::Dir::UP;
        else if(abs(rad) < 0.1) outDir = Direction::Dir::RIGHT;
        else outDir = Direction::Dir::DOWN;
        return outDir;
    }
    static float toRad(Dir dir)
    {
        if(dir == Dir::LEFT) return PI;
        else if(dir == Dir::UP) return PI / 2;
        else if(dir == Dir::RIGHT) return 0;
        else return 3.0 / 2.0 * PI;
    }
};