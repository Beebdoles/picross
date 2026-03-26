#ifndef Sequence_H
#define Sequence_H

#include <math.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct Sequence {
    int* values;
    int freeSpaces;
    int** combinations;
    int combinationsCount;
    int size;
} Sequence;

Sequence* createSequence(int* values, int size);

void generateCombinations(Sequence* sq, int value, int freeSpaces);
void printCombinations(Sequence* sq);

#endif
