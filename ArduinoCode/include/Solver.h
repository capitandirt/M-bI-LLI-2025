#pragma once
#include "Vec2.h"
#include "Maze.h"
#include "config.h"

#define MAX_QUEUE_SIZE (MAZE_SIZE * 4) //периметр

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
        //Serial.println("begin: " + String(begin) + " end: " + String(end) + " ");
        int oldBegin = begin;
        begin = (begin + 1) % MAX_QUEUE_SIZE;
        return arr[oldBegin];
    }

    int size()
    {
        if(end >= begin) return end - begin;
        else return end + (MAX_QUEUE_SIZE - begin);
    }

    T operator [] (int i)
    {
        if(i > MAX_QUEUE_SIZE) Serial.println("i'll do it, but it's out of range >");
        else if(i < 0) Serial.println("i'll do it, but it's out of range <");
        return arr[(begin + i) % MAX_QUEUE_SIZE];
    }
};


class Solver
{
private:
    Queue<Vec2> queue; 
    enum class fromDirection : uint8_t
    {
        UP,
        DOWN,
        LEFT,
        RIGHT,
        UNDEFINED
    };
public:
    fromDirection parent[MAZE_SIZE][MAZE_SIZE] = {fromDirection::UNDEFINED};
    fromDirection path[255];
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
        int counter = 0;
        while(!queue.isEmpty())
        {
            Vec2 correct = queue.pop_front();
            Serial.print(" correct: " + correct.string());
            CellWalls cell = maze->getWalls(correct);
            Serial.print("counter: " + String(counter) + " ");
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

            char symbols[] = {'U', 'P', 'W'};
            Serial.print(String(symbols[(int)cell.down]) + " ");
            Serial.print(String(symbols[(int)cell.left]) + " "); 
            Serial.print(String(symbols[(int)cell.up]) + " "); 
            Serial.print(String(symbols[(int)cell.right]) + " ");  
            if(cell.left == PASS)
            {
                Vec2 left = {correct.x - 1, correct.y};
                //Serial.println("left: " + left.string() + " finish: " + finish.string()); 
                if(left != finish)
                {
                    if(parent[left.x][left.y] == fromDirection::UNDEFINED)
                    {
                        queue.push_back(left);
                        parent[left.x][left.y] = fromDirection::RIGHT;
                        Serial.println("push left");
                    }
                }
                else
                {
                    Serial.println(" left is finish"); 
                    return;
                }
            }
            if(cell.up == PASS)
            {
                Vec2 up = {correct.x, correct.y - 1};
                if(up != finish)
                {
                    if(parent[up.x][up.y] == fromDirection::UNDEFINED)
                    {
                        queue.push_back(up);
                        parent[up.x][up.y] = fromDirection::DOWN;
                        Serial.println("push up");
                    }
                }
                else
                {
                    Serial.println(" left is finish");
                    return;
                }
            }
            if(cell.right == PASS)
            {
                Vec2 right = {correct.x + 1, correct.y};
                if(right != finish)
                {
                    if(parent[right.x][right.y] == fromDirection::UNDEFINED)
                    {
                        queue.push_back(right);
                        parent[right.x][right.y] = fromDirection::LEFT;
                        Serial.println("push right");
                    }
                }
                else
                {
                    Serial.println(" left is finish");
                    return;
                }
            }
            if(cell.down == PASS)
            {
                Vec2 down = {correct.x, correct.y + 1};
                if(down != finish)
                {
                    if(parent[down.x][down.y] == fromDirection::UNDEFINED)
                    {
                        queue.push_back(down);
                        parent[down.x][down.y] = fromDirection::UP;
                        Serial.println("push down");
                    }
                }
                else
                {
                    Serial.println(" left is finish");
                    return;
                }
            }
            counter++;
        }
    }
    void writePath(Vec2 finish, Vec2 start)
    {
        Serial.println("path:");
        Vec2 iterator = finish;
        Serial.println("imalive1");
        for(int i = 0; iterator != start; i++)
        {
            path[i] = parent[iterator.x][iterator.y];
            if(path[i] == fromDirection::DOWN) iterator = {iterator.x, iterator.y + 1};
            else if(path[i] == fromDirection::UP) iterator = {iterator.x, iterator.y - 1};
            else if(path[i] == fromDirection::LEFT) iterator = {iterator.x - 1, iterator.y};
            else if(path[i] == fromDirection::RIGHT) iterator = {iterator.x + 1, iterator.y};
            Serial.println("imalive" + String(i));
        }
    }
    void printPath()
    {
        for(int i = 0; path[i] != fromDirection::UNDEFINED; i++)
        {
            if(path[i] == fromDirection::DOWN) Serial.print("D");
            else if(path[i] == fromDirection::UP) Serial.print("U");
            else if(path[i] == fromDirection::LEFT) Serial.print("L");
            else if(path[i] == fromDirection::RIGHT) Serial.print("R");
            Serial.print(" ");
        }
        Serial.println();
    }
};