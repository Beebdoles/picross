#include "Sequence.h"
#include "Grid.h"

//other vars


int main(void);
int countComponents(void);
int createValidCombinations(int* grid, int val, int index, int depth);
void test(void);
void freeMemory(Sequence* sq);

int main(void) {
    
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
    free(arr2);
    free(invalid);
    freeSequence(sq);

    Grid* gd = createGrid(10, "");
    printGrid(gd);
    freeGrid(gd);
}

