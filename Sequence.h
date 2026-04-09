#ifndef Sequence_H
#define Sequence_H

#include <math.h>
#include <stdio.h>
#include <stdlib.h>

#define True 1
#define False 0

typedef struct Sequence {
    int* values;
    int valueCount;
    int valueSum;
    int freeSum;

    int** combinations;
    int** combinationValues;
    int* solution;

    int combinationsCount;
    int validCombinations;
    int combinationsMax;
    int size;

    int invalidsCount;
    int* invalids;
} Sequence;

Sequence* createSequence(int* values, int size);

void generateCombinations(Sequence* sq, int value, int index, int* acc);
void createCombinationValues(Sequence* sq);
int generateSolution(Sequence* sq, int* invalids, int count);

void printCombinations(Sequence* sq);
void printProperties(Sequence* sq);
void printCombinationValues(Sequence* sq);
void printSolution(Sequence* sq);
void freeSequence(Sequence* sq);

#endif
