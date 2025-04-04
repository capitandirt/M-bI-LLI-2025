#pragma once
#include "Arduino.h"
#include "Maze.h"
#include "Solver.h"

void printMaze(Maze *maze, Solver *solver)
{
    #if ACTIVE_OUTPUT
    PRINTLN("\nstart print\n");
    PRINT(" ");
    for (int j = 0; j < MAZE_SIZE; j++)
    {
        PRINT(String("c:") + String(j) + " ");
    }
    PRINT("\n+");
    for (int j = 0; j < MAZE_SIZE; j++)
    {
        PRINT("---+");
    }
    for (int8_t i = 0; i < MAZE_SIZE; i++)
    {
        PRINT("\n|");
        for (int8_t j = 0; j < MAZE_SIZE; j++)
        {
            char symbols[] = {' ', 'L', 'U', 'R', 'D'};
            PRINT(" " + 
                         String( symbols[int(solver->whereFrom[j][i])] )
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
                
            PRINT(out);
        }
        PRINT(" l:" + String(i) + "\n+");
        for (int j = 0; j < MAZE_SIZE; j++)
        {
            CellWalls walls = maze->getWalls({j, i});
            // CellWalls walls = CellWalls(YES, YES, YES, YES);
            // PRINT("im here");
            if (walls.down == WALL)
                PRINT("---");
            else if (walls.down == UNDEFINED)
                PRINT(" . ");
            else
                PRINT("   ");
            PRINT("+");
        }
    }
    PRINT("\nfinish print\n");
    #endif
}