#include "Sequence.h"
#include "Grid.h"
#include <string.h>

//other vars


int main(void);
int countComponents(void);
int createValidCombinations(int* grid, int val, int index, int depth);
void test(void);
void parse(void);
int run(void);
void freeMemory(Sequence* sq);

int main(void) {
    
    //test();
    parse();
    //run();

    return 0;
}

int run() {

    int* arr = (int*)malloc(sizeof(int) * (4 + 1));
    int* invalids = (int*)malloc(sizeof(int) * (5));
    
    //*arr = 1; ++arr; *arr = 2; ++arr; *arr = 4; ++arr; *arr = 2; ++arr; *arr = 1; ++arr; *arr = -1; arr -= 5;
    *arr = 2; ++arr; *arr = 6; ++arr; *arr = 3; ++arr; *arr = 2; ++arr; *arr = -1; arr -= 4;
    //*arr = 3; ++arr; *arr = 7; ++arr; *arr = 5; ++arr; *arr = -1; arr -= 3;
    *invalids = 0; ++invalids; *invalids = 1; ++invalids; *invalids = 2; ++invalids; *invalids = 3; ++invalids; *invalids = 4; ++invalids; invalids -= 5;

    Sequence* sq = createSequence(arr, 20);
    int* acc = (int*)malloc(sizeof(int) * (sq->valueCount + 1));
    generateCombinations(sq, sq->freeSum, 0, acc);
    //printCombinations(sq);
    createCombinationValues(sq);
    //generateSolution(sq, invalids, 1);
    printSolution(sq);

    return 0;
}

void parse() {
    
    //accept inputs here

    printf("Enter board size: ");
    char inputSize[100];
    int size;
    fgets(inputSize, 100, stdin);
    sscanf(inputSize, "%d", &size);

    printf("%d\n", size);
    
    printf("Enter top numbers, delimited by '|': ");
    char inputTopNums[500];
    int** topNums = (int**)malloc(sizeof(int*) * size);
    
    for (int i = 0; i < size; ++i) { 

        *(topNums + i) = (int*)malloc(sizeof(int) * (size / 2 + 1 + (size % 2))); 
    }

    fgets(inputTopNums, 500 - 1, stdin);
    
    printf("%s\n", inputTopNums);

    printf("Enter bottom numbers, delimited by '|': ");
    char inputBottomNums[500];
    int** bottomNums = (int**)malloc(sizeof(int*) * size);
    fgets(inputBottomNums, 500 - 1, stdin);

    printf("%s\n", inputBottomNums);

    //parse inputs here

    int section = 0, valIndex = 0, length = 0;
    char* value = (char*)malloc(sizeof(char) * 4); memset(value, '\0', 4);
    int prevWhitespace = False;

    for (int i = 0; inputTopNums[i] != '\0' && i < 500; ++i) {
    
        printf("%c, %d\n", inputTopNums[i], inputTopNums[i]);

        //if whitespace
        if (inputTopNums[i] == 32 && !prevWhitespace) {
        
            value -= length; memset(value, '\0', length);
            *(*(topNums + section) + valIndex) = atoi(value);
            length = 0;
            ++valIndex;
            prevWhitespace = True;
        }

        //if pipe
        else if (inputTopNums[i] == 124) {
        
            *(*(topNums + section) + valIndex) = -1;
            valIndex = 0;
            value -= length; memset(value, '\0', length);
            prevWhitespace = True;
            ++section;
            length = 0;
        }

        //if normal
        else if (inputTopNums[i] >= 48 && inputTopNums[i] <= 57) {
            
            *value = inputTopNums[i];
            ++value;
            ++length;
            prevWhitespace = False;
        }

        //newline, combine section + newval
        else if (inputTopNums[i] == 10) {
        
            value -= length;
            *(*(topNums + section) + valIndex) = atoi(value);
            memset(value, '\0', length);
            length = 0;
            ++valIndex;
            
            *(*(topNums + section) + valIndex) = -1;
            valIndex = 0;
            prevWhitespace = True;
            ++section;
        }
    }

    for (int i = 0; i < section; ++i) {
    
        int j = 0;
        
        while (*(*(topNums + i) + j) != -1) {
        
            printf("%d", *(*(topNums + i) + j));
            ++j;
        }

        printf("\n");
    }


    //free

    free(topNums); free(bottomNums);
    free(value);

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

