#include <stdlib.h>
#include <stdio.h>
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

void generateCombination(Sequence* sq, int value, int index, int depth, int freeSpaces) {i

    if (depth == 0) {
        
        while (*(sq->combinations + depth) != NULL) { ++depth; }

        *(sq->combinations + depth) = (int*)malloc(sizeof(int));
    }
    if (depth > freeSpaces) { (*(sq->combinations) + index) == -1; }
    
    for (int i = 0; i <= value; ++i) {

        createCombinations(sq, value - i, ++index, depth);
    }
}
