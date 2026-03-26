#ifndef Sequence_H
#define Sequence_H

#include <math.h>

typedef struct Sequence {
    int* values;
    int** combinations;
    int size;
} Sequence;

Sequence* createSequence(int* values, int size);

void createCombinations(Sequence* sq);
void generateCombination(Sequence* sq, int value, int freeSpaces);

#endif
