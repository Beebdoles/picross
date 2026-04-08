#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <math.h>

#include "Sequence.h"


//other vars


int main(void);
int countComponents(void);
int createValidCombinations(int* grid, int val, int index, int depth);
void test(void);
void freeMemory(Sequence* sq);

int main(void) {
    
    printf("HI");

    int* grid = malloc(10 * 10 * sizeof(int));

    for (int i = 0; i < 10 * 10; ++i) {
        if (i % 10 == 0) { printf("\n"); }
        grid[i] = i;
        printf("%d ", grid[i]);
        if (i < 10) { printf(" "); }
    }
    printf("\n");

    free(grid);

    test();

    return 0;
}

void test() {

    int* arr = (int*)malloc(sizeof(int) * 6);
    *arr = 1; ++arr; *arr = 1; ++arr; *arr = 1; ++arr; *arr = 1; ++arr; *arr = 1; ++arr; *arr = -1; arr -= 5;

    int* arr2 = (int*)malloc(sizeof(int) * (2 + 1));
    *arr2 = 4; ++arr2; *arr2 = 4; ++arr2; *arr2 = -1; arr2 -= 2;
    
    Sequence* sq = createSequence(arr2, 10);
    int* acc = (int*)malloc(sizeof(int) * (sq->valueCount + 1));
    printProperties(sq);

    generateCombinations(sq, sq->freeSum, 0, acc);
    printCombinations(sq);
    createCombinationValues(sq);
    printCombinationValues(sq);
    printSolution(sq);
    int* invalid = (int*)malloc(sizeof(int) * 1);
    *invalid = 4;
    generateSolution(sq, invalid, 1);
    printSolution(sq);
    printf("%d\n", sq->validCombinations);

    printf("free\n");
    free(acc);
    free(arr);
    freeMemory(sq);
}

void freeMemory(Sequence* sq) {
    
    for (int i = 0; i < sq->combinationsCount; ++i) {
        
        free(*(sq->combinations + i));
        free(*(sq->combinationValues + i));
    }
    free(sq->combinations);
    free(sq->combinationValues);
    free(sq->values);
    free(sq->solution);
    free(sq);
}
