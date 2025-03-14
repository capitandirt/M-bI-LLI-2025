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

#define MAX_PATH_SIZE (MAZE_SIZE * MAZE_SIZE - 1)

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
    fromDirection whereFrom[MAZE_SIZE][MAZE_SIZE] = {fromDirection::UNDEFINED};
    
    fromDirection path[MAX_PATH_SIZE];
    uint8_t pathEndIndex = 255;
    void solve(Vec2 start, Vec2 finish, const Maze* maze)
    {
        for(int i = 0; i < MAZE_SIZE; i++)
        {
            for(int j = 0; j < MAZE_SIZE; j++)
            {
                whereFrom[i][j] = fromDirection::UNDEFINED;
            }
        }
        
        queue.push_back(start);
        int counter = 0;
        while(!queue.isEmpty())
        {
            sizeof(Vec2);
            sizeof(queue);
            sizeof(whereFrom);
            sizeof(path);
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
            Serial.println(String(symbols[(int)cell.right]) + " ");  
            if(cell.left != WALL)
            {
                Vec2 left = {correct.x - 1, correct.y};
                //Serial.println("left: " + left.string() + " finish: " + finish.string()); 
                if(left != finish)
                {
                    if(whereFrom[left.x][left.y] == fromDirection::UNDEFINED)
                    {
                        queue.push_back(left);
                        whereFrom[left.x][left.y] = fromDirection::RIGHT;
                        Serial.println("push left");
                    }
                }
                else
                {
                    whereFrom[left.x][left.y] = fromDirection::RIGHT;
                    Serial.println(" left is finish"); 
                    return;
                }
            }
            if(cell.up != WALL)
            {
                Vec2 up = {correct.x, correct.y - 1};
                if(up != finish)
                {
                    if(whereFrom[up.x][up.y] == fromDirection::UNDEFINED)
                    {
                        queue.push_back(up);
                        whereFrom[up.x][up.y] = fromDirection::DOWN;
                        Serial.println("push up");
                    }
                }
                else
                {
                    whereFrom[up.x][up.y] = fromDirection::DOWN;
                    Serial.println(" up is finish");
                    return;
                }
            }
            if(cell.right != WALL)
            {
                Vec2 right = {correct.x + 1, correct.y};
                if(right != finish)
                {
                    if(whereFrom[right.x][right.y] == fromDirection::UNDEFINED)
                    {
                        queue.push_back(right);
                        whereFrom[right.x][right.y] = fromDirection::LEFT;
                        Serial.println("push right");
                    }
                }
                else
                {
                    whereFrom[right.x][right.y] = fromDirection::LEFT;
                    Serial.println(" right is finish");
                    return;
                }
            }
            if(cell.down != WALL)
            {
                Vec2 down = {correct.x, correct.y + 1};
                if(down != finish)
                {
                    if(whereFrom[down.x][down.y] == fromDirection::UNDEFINED)
                    {
                        queue.push_back(down);
                        whereFrom[down.x][down.y] = fromDirection::UP;
                        Serial.println("push down");
                    }
                }
                else
                {
                    whereFrom[down.x][down.y] = fromDirection::UP;
                    Serial.println(" down is finish");
                    return;
                }
            }
            counter++;
        }
    }
    void writePath(Vec2 start, Vec2 finish)
    {
        Serial.println("path:");
        Vec2 correct = finish;
        //Serial.println("imalive1");
        for(int i = 0; correct != start; i++)
        {
            path[i] = whereFrom[correct.x][correct.y];
            if(whereFrom[correct.x][correct.y] == fromDirection::LEFT) correct = correct + Vec2{-1, 0};
            else if(whereFrom[correct.x][correct.y] == fromDirection::RIGHT) correct = correct + Vec2{1, 0};
            else if(whereFrom[correct.x][correct.y] == fromDirection::UP) correct = correct + Vec2{0, -1};
            else if(whereFrom[correct.x][correct.y] == fromDirection::DOWN) correct = correct + Vec2{0, 1};
            if(i >= 256) 
            {
                Serial.println("error infinite loop path");
                break;
            }
            pathEndIndex = i;
        }
    }
    fromDirection nextPathCell()
    {
        return fromDirection(((int)path[pathEndIndex] + 2) % 4);
    }
    void printPath()
    {
        Serial.print("startPath: ");
        for(int i = 0; i <= pathEndIndex; i++) // на самом деле цикл кончается раньше, когда закончатся все элементы массива из списка L U R D
        {
            if(path[i] == fromDirection::DOWN) Serial.print("D");
            else if(path[i] == fromDirection::UP) Serial.print("U");
            else if(path[i] == fromDirection::LEFT) Serial.print("L");
            else if(path[i] == fromDirection::RIGHT) Serial.print("R");
            else 
            {
                break;
            }
            Serial.print(" ");
        }
        Serial.println("endPath");
    }
};