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
        
    while (*sq->values != -1) {
        
        printf("%d ", *sq->values);

        ++sq->values;
        ++count;
    }
    printf("\n");
    sq->values -= count;
}
