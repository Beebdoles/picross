#include <stdlib.h>
#include <stdio.h>
#include <math.h>

#include "Sequence.h"

Sequence* createSequence(int* values, int size) {
    
    Sequence* newSequence = malloc(sizeof(Sequence));
    if (!newSequence) { return NULL; }

    newSequence->values = values;
    newSequence->combinations = (int**)malloc(sizeof(int*));
    newSequence->size = size;

    return newSequence;
}

void createCombinations(Sequence* sq) {
    
    int sum = 0;
    int count = 0;
        
    while (*(sq->values + count) != -1) {
        
        printf("%d ", *(sq->values + count));
        ++count;
        sum += *(sq->values + count);
    }
    printf("\n");

    int freeBlocks = sq->size - (sum + count - 1);
    int freeSpaces = count + 1;
}

void generateCombination(Sequence* sq, int value, int freeSpaces) {

    int* masks = (int*)malloc(sizeof(int));
    int index = 0;

    for (int i = 0; i < pow(2, freeSpaces); ++i) {
        
        int bitCount;

        for (int j = 0; j < freeSpaces; ++j) {
            
            if (i % 2 == 1) { ++bitCount; }
        }
        if (bitCount != value) { continue; }

        int* spaceDistributions = (int*)malloc(sizeof(int));
        int bitIndex = 0;

        for (int j = 0; j < freeSpaces; ++j) {
        
            *spaceDistributions = i % 2;
            ++spaceDistributions;
        }
        spaceDistributions -= freeSpaces;

    }

    free(masks);
}
