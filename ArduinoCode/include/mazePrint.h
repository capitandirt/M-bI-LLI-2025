#pragma once
#include "Arduino.h"
#include "Maze.h"
#include "Solver.h"

void printMaze(Maze* maze)
    {
        Serial.println("\nstart print\n");
        Serial.println(String(123));
        Serial.print(" ");
        for(int j = 0; j < MAZE_SIZE; j++)
        {
            Serial.print(String("c:") + String(j) + " ");
        }
        Serial.print("\n+");
        for(int j = 0; j < MAZE_SIZE; j++)
        {
            Serial.print(" = +");
        }
        for(int i = 0; i < MAZE_SIZE; i++)
        {
            Serial.print("\n|");
            for(int j = 0; j < MAZE_SIZE; j++)
            {
                Serial.print(String("   "));
                if(maze->getWalls({j, i}).right == YES) Serial.print("|");
                else if(maze->getWalls({j, i}).right == UNDEFINED) Serial.print(".");
                else Serial.print(" ");
            }
            Serial.print(" l:" + String(i) + "\n+");
            for(int j = 0; j < MAZE_SIZE; j++)
            {
                //Serial.print("im here");
                if(maze->getWalls({j, i}).down == YES) Serial.print("---");
                else if(maze->getWalls({j, i}).down == UNDEFINED) Serial.print(" . ");
                else Serial.print("   ");
                Serial.print("+");
            }
        }
        Serial.print("\nfinish print");
    }