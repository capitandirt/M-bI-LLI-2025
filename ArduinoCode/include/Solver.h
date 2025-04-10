#pragma once
#include "MazeCoord.h"
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
        //PRINTLN("begin: " + String(begin) + " end: " + String(end) + " ");
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
        if(i > MAX_QUEUE_SIZE) PRINTLN("i'll do it, but it's out of range >");
        else if(i < 0) PRINTLN("i'll do it, but it's out of range <");
        return arr[(begin + i) % MAX_QUEUE_SIZE];
    }
};

#define MAX_PATH_SIZE (MAZE_SIZE * MAZE_SIZE - 1)

class Solver
{
private:
    Queue<MazeCoord> queue; 
    enum class fromDirection : uint8_t
    {
        UNDEFINED,
        LEFT,
        UP,
        RIGHT,
        DOWN
    };
public:
    fromDirection whereFrom[MAZE_SIZE][MAZE_SIZE] = {fromDirection::UNDEFINED};
    
    fromDirection path[MAX_PATH_SIZE];
    
    uint8_t pathEndIndex = 255;
    void solve(MazeCoord start, MazeCoord finish, const Maze* maze)
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
            MazeCoord correct = queue.pop_front();
            PRINT(" correct: " + correct.string());
            CellWalls cell = maze->getWalls(correct);
            PRINT("counter: " + String(counter) + " ");
            PRINT("size: ");
            PRINT(queue.size());
            PRINT(" {");
            for(int i = 0; i < queue.size(); i++)
            {
                PRINT("{");
                PRINT(queue[i].x);
                PRINT(", ");
                PRINT(queue[i].y);
                PRINT("} ");
            }
            PRINTLN("}");

            char symbols[] = {'U', 'P', 'W'};
            PRINT(String(symbols[(int)cell.down]) + " ");
            PRINT(String(symbols[(int)cell.left]) + " "); 
            PRINT(String(symbols[(int)cell.up]) + " "); 
            PRINTLN(String(symbols[(int)cell.right]) + " ");  
            if(cell.left != WALL)
            {
                MazeCoord left = {correct.x - 1, correct.y};
                //PRINTLN("left: " + left.string() + " finish: " + finish.string()); 
                if(left != finish)
                {
                    if(whereFrom[left.x][left.y] == fromDirection::UNDEFINED)
                    {
                        queue.push_back(left);
                        whereFrom[left.x][left.y] = fromDirection::RIGHT;
                        PRINTLN("push left");
                    }
                }
                else
                {
                    whereFrom[left.x][left.y] = fromDirection::RIGHT;
                    PRINTLN(" left is finish"); 
                    return;
                }
            }
            if(cell.up != WALL)
            {
                MazeCoord up = {correct.x, correct.y - 1};
                if(up != finish)
                {
                    if(whereFrom[up.x][up.y] == fromDirection::UNDEFINED)
                    {
                        queue.push_back(up);
                        whereFrom[up.x][up.y] = fromDirection::DOWN;
                        PRINTLN("push up");
                    }
                }
                else
                {
                    whereFrom[up.x][up.y] = fromDirection::DOWN;
                    PRINTLN(" up is finish");
                    return;
                }
            }
            if(cell.right != WALL)
            {
                MazeCoord right = {correct.x + 1, correct.y};
                if(right != finish)
                {
                    if(whereFrom[right.x][right.y] == fromDirection::UNDEFINED)
                    {
                        queue.push_back(right);
                        whereFrom[right.x][right.y] = fromDirection::LEFT;
                        PRINTLN("push right");
                    }
                }
                else
                {
                    whereFrom[right.x][right.y] = fromDirection::LEFT;
                    PRINTLN(" right is finish");
                    return;
                }
            }
            if(cell.down != WALL)
            {
                MazeCoord down = {correct.x, correct.y + 1};
                if(down != finish)
                {
                    if(whereFrom[down.x][down.y] == fromDirection::UNDEFINED)
                    {
                        queue.push_back(down);
                        whereFrom[down.x][down.y] = fromDirection::UP;
                        PRINTLN("push down");
                    }
                }
                else
                {
                    whereFrom[down.x][down.y] = fromDirection::UP;
                    PRINTLN(" down is finish");
                    return;
                }
            }
            counter++;
        }
    }
    void writePath(MazeCoord start, MazeCoord finish)
    {
        PRINTLN("path:");
        MazeCoord correct = finish;
        //PRINTLN("imalive1");
        for(int i = 0; correct != start; i++)
        {
            path[i] = whereFrom[correct.x][correct.y];
            if(whereFrom[correct.x][correct.y] == fromDirection::LEFT) correct = correct + MazeCoord{-1, 0};
            else if(whereFrom[correct.x][correct.y] == fromDirection::RIGHT) correct = correct + MazeCoord{1, 0};
            else if(whereFrom[correct.x][correct.y] == fromDirection::UP) correct = correct + MazeCoord{0, -1};
            else if(whereFrom[correct.x][correct.y] == fromDirection::DOWN) correct = correct + MazeCoord{0, 1};
            if(i >= 256) 
            {
                PRINTLN("error infinite loop path");
                break;
            }
            pathEndIndex = i;
        }
    }
    Direction::Dir nextPathCell()
    {
        return Direction::Dir(((int)path[pathEndIndex] + 2) % 4);
    }

    void printPath()
    {
        PRINT("startPath: ");
        for(int i = 0; i <= pathEndIndex; i++) // на самом деле цикл кончается раньше, когда закончатся все элементы массива из списка L U R D
        {
            if(path[i] == fromDirection::DOWN) PRINT("D");
            else if(path[i] == fromDirection::UP) PRINT("U");
            else if(path[i] == fromDirection::LEFT) PRINT("L");
            else if(path[i] == fromDirection::RIGHT) PRINT("R");
            else 
            {
                break;
            }
            PRINT(" ");
        }
        PRINTLN("endPath");
    }
};