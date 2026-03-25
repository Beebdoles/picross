#ifndef Sequence_H
#define Sequence_H

typedef struct Sequence {
    int* values;
    int** combinations;
    int size;
} Sequence;

Sequence* createSequence(int* values, int size);

void createCombinations(Sequence* sq);

#endif
