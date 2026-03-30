
#include "Sequence.h"


Sequence* createSequence(int* values, int size) {
    
    Sequence* newSequence = malloc(sizeof(Sequence));
    if (!newSequence) { return NULL; }

    newSequence->values = values;

    int count = 0;
    int sum = 0;

    while (*(values + count) != -1) { 
        sum += *(values + count);
        ++count;
    }

    int combinationsCalc = pow(2,5);

    newSequence->valueCount = count;
    newSequence->valueSum = sum;
    newSequence->freeSum = size - (sum + count - 1);
    newSequence->combinationsMax = combinationsCalc;
    newSequence->combinations = (int**)malloc(sizeof(int*) * combinationsCalc);
    newSequence->combinationsCount = 0;
    newSequence->size = size;

    return newSequence;
}

void appendCombination(Sequence* sq, int* combination, int size) {
    
    int* values = (int*)malloc(sizeof(int) * size);
    
    for (int i = 0; i < size; ++i) { *(values + i) = *(combination + i); }
    
    *(sq->combinations + sq->combinationsCount) = values;
    ++sq->combinationsCount;

    if (sq->combinationsMax == sq->combinationsCount + 1) { 

        sq->combinationsMax *= 2;
        int** temp = realloc(sq->combinations, sq->combinationsCount * sizeof(int*));

        if (temp != NULL) { sq->combinations = temp; }
    }
}

void generateCombinations(Sequence* sq, int value, int index, int* acc) {

    if (index == sq->valueCount) { 

        *(acc + index) = value; 
        appendCombination(sq, acc, index + 1);
        return;
    }

    for (int i = 0; i <= value; ++i) {

        *(acc + index) = i;
        generateCombinations(sq, value - i, index + 1, acc);
    }

    return;
}

void printCombinations(Sequence* sq) {

    int index = 0;

    for (int i = 0; i < sq->combinationsCount; ++i) {

        for (int j = 0; j < sq->valueCount + 1; ++j) {
        
            printf("%d ", *(*(sq->combinations + i) + j));
        }
        printf("\n");
    }
}

void printProperties(Sequence* sq) {

    printf("Value count : %d\n", sq->valueCount);
    printf("Value sum   : %d\n", sq->valueSum);
    printf("Free sum    : %d\n", sq->freeSum);
    printf("Size        : %d\n", sq->size);
    printf("Combinations: %d\n", sq->combinationsMax);

    printf("Values: ");

    for (int i = 0; i < sq->valueCount; ++i) {
    
        printf("%d ", *(sq->values + i));
    }
    printf("\n");
}
