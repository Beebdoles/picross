#ifndef Sequence_H
#define Sequence_H

#include <math.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct Sequence {
    int* values;
    int valueCount;
    int valueSum;
    int freeSum;
    int** combinations;
    int** combinationValues;
    int combinationsCount;
    int combinationsMax;
    int size;
} Sequence;

Sequence* createSequence(int* values, int size);

void generateCombinations(Sequence* sq, int value, int index, int* acc);
void createCombinationValues(Sequence* sq);

void printCombinations(Sequence* sq);
void printProperties(Sequence* sq);
void printCombinationValues(Sequence* sq);

#endif
