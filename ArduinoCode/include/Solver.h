#pragma once
#include "Vec2.h"
#include "Maze.h"
#include "config.h"

#define MAX_QUEUE_SIZE MAZE_SIZE * 4 //периметр

template<typename T> //так создаётся шаблон

class Queue
{
private:
    int begin = 0, end = 0;
    T arr[MAX_QUEUE_SIZE];
public:
    Queue()
    {
        begin = 0;
        end = 0;
    }

    bool isEmpty()
    {
        return begin == end;
    }
    bool isFull()
    {
        return isEmpty(); //таков путь.
    }

    bool push_back(T value)
    {
        arr[end] = value;
        end = (end+1) % MAX_QUEUE_SIZE;
        return isFull();
    }

    T pop_front()
    {
        return arr[begin];
        begin = (begin + 1) % MAX_QUEUE_SIZE;
    }

    int size()
    {
        if(end > begin) return end - begin;
        else return end + (MAX_QUEUE_SIZE - begin);
    }

    T operator [] (int i)
    {
        return arr[(begin + i) % MAX_QUEUE_SIZE];
    }
};


class Solver
{
private:
    Queue<Vec2> queue; 
    enum class fromDirection
    {
        UP,
        DOWN,
        LEFT,
        RIGHT,
        UNDEFINED
    };
    fromDirection parent[MAZE_SIZE][MAZE_SIZE] = {fromDirection::UNDEFINED};
public:
    Vec2 path[255];
    void solve(Vec2 start, Vec2 finish, const Maze* maze)
    {
        for(int i = 0; i < MAZE_SIZE; i++)
        {
            for(int j = 0; j < MAZE_SIZE; j++)
            {
                parent[i][j] = fromDirection::UNDEFINED;
            }
        }
        queue.push_back(start);
        while(!queue.isEmpty())
        {
            Vec2 correct = queue.pop_front();
            CellWalls cell = maze->getWalls(correct);
            Serial.print("size: ");
            Serial.print(queue.size());
            Serial.print(" {");
            for(int i = 0; i < queue.size(); i++)
            {
                Serial.print("{");
                Serial.print(queue[i].x);
                Serial.print(", ");
                Serial.print(queue[i].y);
                Serial.print("} ");
            }
            Serial.println("}");
            if(cell.left != UNDEFINED)
            {
                Vec2 left = {correct.x - 1, correct.y};
                if(left != finish)
                {
                    if(parent[left.x][left.y] != fromDirection::UNDEFINED)
                    {
                        queue.push_back(left);
                        parent[left.x][left.y] = fromDirection::RIGHT;
                    }
                }
                else
                {
                    return;
                }
            }
            if(cell.up != UNDEFINED)
            {
                Vec2 up = {correct.x, correct.y + 1};
                if(up != finish)
                {
                    if(parent[up.x][up.y] != fromDirection::UNDEFINED)
                    {
                        queue.push_back(up);
                        parent[up.x][up.y] = fromDirection::DOWN;
                    }
                }
                else
                {
                    return;
                }
            }
            if(cell.right != UNDEFINED)
            {
                Vec2 right = {correct.x + 1, correct.y};
                if(right != finish)
                {
                    if(parent[right.x][right.y] != fromDirection::UNDEFINED)
                    {
                        queue.push_back(right);
                        parent[right.x][right.y] = fromDirection::LEFT;
                    }
                }
                else
                {
                    return;
                }
            }
            if(cell.down != UNDEFINED)
            {
                Vec2 down = {correct.x, correct.y - 1};
                if(down != finish)
                {
                    if(parent[down.x][down.y] != fromDirection::UNDEFINED)
                    {
                        queue.push_back(down);
                        parent[down.x][down.y] = fromDirection::UP;
                    }
                }
                else
                {
                    return;
                }
            }
        }
    }
    void writePath(Vec2 finish, Vec2 start)
    {
        Vec2 iterator = finish;
        for(int i = 0; iterator != start; i++)
        {
            path[i] = iterator;
            if(parent[iterator.x][iterator.y] == fromDirection::DOWN) iterator = {iterator.x, iterator.y - 1};
            else if(parent[iterator.x][iterator.y] == fromDirection::UP) iterator = {iterator.x, iterator.y + 1};
            else if(parent[iterator.x][iterator.y] == fromDirection::LEFT) iterator = {iterator.x - 1, iterator.y};
            else if(parent[iterator.x][iterator.y] == fromDirection::RIGHT) iterator = {iterator.x + 1, iterator.y};
        }
    }
};