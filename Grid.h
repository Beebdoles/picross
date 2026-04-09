#ifndef GRID_H
#define GRID_H

#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include "Sequence.h"

typedef struct Grid {
    int* grid;
    Sequence** sequences;

    int size;
} Grid;

Grid* createGrid(int size, char* vals);
void solveGrid(Grid* grid);

void printGrid(Grid* grid);
void freeGrid(Grid* gd);

#define True 1
#define False 0

#endif
