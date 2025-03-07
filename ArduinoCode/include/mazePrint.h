#pragma once
#include "Arduino.h"
#include "Maze.h"
#include "Solver.h"

void printMaze(Maze *maze, Solver *solver)
{
    Serial.println("\nstart print\n");
    Serial.println(String(123));
    Serial.print(" ");
    for (int j = 0; j < MAZE_SIZE; j++)
    {
        Serial.print(String("c:") + String(j) + " ");
    }
    Serial.print("\n+");
    for (int j = 0; j < MAZE_SIZE; j++)
    {
        Serial.print("---+");
    }
    for (int i = 0; i < MAZE_SIZE; i++)
    {
        Serial.print("\n|");
        for (int j = 0; j < MAZE_SIZE; j++)
        {
            char symbols[] = {'U', 'D', 'L', 'R', 'X'};
            Serial.print(" " + 
                         String( symbols[int(solver->parent[j][i])] )
                         + " "); 
            CellWalls walls = maze->getWalls({j, i});
            // CellWalls walls = CellWalls(YES, YES, YES, YES);
            String out = "";
            if (walls.right == WALL)
                out = "|";
            else if (walls.right == UNDEFINED)
                out = ".";
            else
                out = " ";
                
            Serial.print(out);
        }
        Serial.print(" l:" + String(i) + "\n+");
        for (int j = 0; j < MAZE_SIZE; j++)
        {
            CellWalls walls = maze->getWalls({j, i});
            // CellWalls walls = CellWalls(YES, YES, YES, YES);
            // Serial.print("im here");
            if (walls.down == WALL)
                Serial.print("---");
            else if (walls.down == UNDEFINED)
                Serial.print(" . ");
            else
                Serial.print("   ");
            Serial.print("+");
        }
    }
    Serial.print("\nfinish print\n");
}