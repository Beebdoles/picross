
#include "Sequence.h"

Sequence* createSequence(int* values, int size) {
    
    Sequence* newSequence = malloc(sizeof(Sequence));
    if (!newSequence) { return NULL; }

    newSequence->values = values;
    newSequence->freeSpaces = 0;
    newSequence->combinations = (int**)malloc(sizeof(int*) * pow(2, 5));
    newSequence->combinationsCount = 0;
    newSequence->size = size;

    return newSequence;
}

void generateCombinations(Sequence* sq, int value, int freeSpaces) {

    for (int i = 0; i < pow(2, freeSpaces); ++i) {
        
        int bitCount = 0;
        int bitValue = i;

        for (int j = 0; j < freeSpaces; ++j) {
            
            if (bitValue % 2 == 1) { ++bitCount; }
            bitValue = bitValue >> 1;
        }
        if (bitCount != value) { continue; }

        int* spaceDistributions = (int*)malloc(sizeof(int) * freeSpaces);
        int bitIndex = 0;
        bitValue = i;

        for (int j = 0; j < freeSpaces; ++j) {
        
            *(spaceDistributions + bitIndex) = bitValue % 2;
            bitValue = bitValue >> 1;
            ++bitIndex;
        }
        *(sq->combinations + sq->combinationsCount) = spaceDistributions;
        ++sq->combinationsCount;
        sq->freeSpaces = freeSpaces;
    }
}

void printCombinations(Sequence* sq) {

    int index = 0;

    for (int i = 0; i < sq->combinationsCount; ++i) {

        for (int j = 0; j < sq->freeSpaces; ++j) {
        
            printf("%d ", *(*(sq->combinations + i) + j));
        }
        printf("\n");
    }
}
