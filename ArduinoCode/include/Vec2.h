#pragma once
class Vec2
{
public:
    int x, y;
    bool operator ==(const Vec2& second) const
    {
        return x == second.x && y == second.y;
    } 
    bool operator !=(const Vec2& second) const
    {
        return x != second.x || y != second.y;
    }
    Vec2 operator +(const Vec2& second) const
    {
        return {x + second.x, y + second.y};
    }
    Vec2 operator -(const Vec2& second) const
    {
        return {x - second.x, y - second.y};
    }
    String string()
    {
        return ("{" + (String)x + ";" + (String)y + "}");
    }
};