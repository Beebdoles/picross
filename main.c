#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <math.h>

#include "Sequence.h"

#define True 1
#define False 0


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

    int* arr = (int*)malloc(sizeof(int) * 5);
    *arr = 1; ++arr; *arr = 2; ++arr; *arr = 3; ++arr; *arr = -1; arr -= 3;
    
    Sequence* sq = createSequence(arr, 5);
    //createCombinations(sq);
    generateCombinations(sq, 1, 5);
    printCombinations(sq);

    freeMemory(sq);
}

void freeMemory(Sequence* sq) {
    
    for (int i = 0; i < pow(2, 5); ++i) {
        
        free(*(sq->combinations + i));
    }
    free(sq->combinations);
    free(sq->values);
    free(sq);
}
