#include "Sequence.h"
#include "Grid.h"
#include <string.h>

//other vars


int main(void);
int countComponents(void);
int createValidCombinations(int* grid, int val, int index, int depth);
void test(void);
int run(void);
int readInput(int* size, char* inputTopNums, char* inputBottomNums);
int parse(int* size, int** topNums, int** bottomNums, char* inputTopNums, char* inputBottomNums);
void freeMemory(Sequence* sq);

int main(void) {
    
    int size;
    char* inputTopNums = (char*)malloc(sizeof(char) * 500);
    char* inputBottomNums = (char*)malloc(sizeof(char) * 500);

    if (readInput(&size, inputTopNums, inputBottomNums) == 1) { return 1; };                                //i love memory leak

    int** topNums = (int**)malloc(sizeof(int*) * size);
    int** bottomNums = (int**)malloc(sizeof(int*) * size);

    if (parse(&size, topNums, bottomNums, inputTopNums, inputBottomNums) == 1) { return 1; }                 //i love memory leak

    //frees
    for (int i = 0; i < size; ++i) { free(*(topNums + i)); free(*(bottomNums + i)); }

    free(inputTopNums); free(inputBottomNums);
    free(topNums); free(bottomNums);

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

int readInput(int* size, char* inputTopNums, char* inputBottomNums) {

    printf("Enter board size: ");
    char inputSize[100];
    fgets(inputSize, 100, stdin);
    sscanf(inputSize, "%d", size);

    printf("Enter top numbers, delimited by ';': ");
    fgets(inputTopNums, 500 - 1, stdin);
    
    printf("Enter bottom numbers, delimited by ';': ");
    fgets(inputBottomNums, 500 - 1, stdin);

    return 0;
}

int parse(int* size, int** topNums, int** bottomNums, char* inputTopNums, char* inputBottomNums) {

    for (int i = 0; i < *size; ++i) { 

        *(topNums + i) = (int*)malloc(sizeof(int) * (*size / 2 + 1 + (*size % 2)));
        *(bottomNums + i) = (int*)malloc(sizeof(int) * (*size / 2 + 1 + (*size % 2)));
    }

    int section = 0, valIndex = 0, length = 0;
    char* value = (char*)malloc(sizeof(char) * 4); memset(value, '\0', 4);              //read 3 digit val at most
    int prevWhitespace = False;

    for (int i = 0; *(inputTopNums + i) != '\0' && i < 500; ++i) {
   
        if (valIndex > (*size / 2 + 1 + (*size % 2))) { printf("Too many blocks in section\n"); return 1; }
        if (length > 3) { printf("Error: Digit too large ( > 3)\n"); return 1; }
        if (section >= *size) { printf("Error: Too many sections\n"); return 1; }

        //write a value if whitespace or semicolon
        if ((*(inputTopNums + i) == 32 && prevWhitespace == False) || *(inputTopNums + i) == 59 || *(inputTopNums + i) == 10) {
        
            value -= length;

            //dont write multiple 0's
            if (atoi(value) != 0 || (atoi(value) == 0 && valIndex == 0)) {

                *(*(topNums + section) + valIndex) = atoi(value);                       //safety write val + sentinel
                *(*(topNums + section) + valIndex + 1) = -1;                    
            }

            memset(value, '\0', 4); length = 0;
            ++valIndex;
            prevWhitespace = True;

            if (*(inputTopNums + i) == 59) {
            
                ++section;
                valIndex = 0;
            }

            if (*(inputTopNums + i) == 10) {
            
                ++section;
                
                if (section != *size) { printf("Error: Not enough sections inputted\n"); return 1; }

                break;
            }
        }

        //read a value
        else if (*(inputTopNums + i) >= 48 && *(inputTopNums + i) <= 57) {
            
            *value = *(inputTopNums + i);
            ++value;
            ++length;
            prevWhitespace = False;
        }
    }

    if (section > *size) { printf("Error: Too many sections\n"); return 1; };

    memset(value, '\0', 4);
    section = 0; valIndex = 0; length = 0;
    prevWhitespace = False;

    for (int i = 0; *(inputBottomNums + i) != '\0' && i < 500; ++i) {
    
        if (valIndex > (*size / 2 + 1 + (*size % 2))) { printf("Error: Too many blocks in section\n"); return 1; }
        if (length > 3) { printf("Error: Digit too large ( > 3)\n"); return 1; }
        if (section >= *size) { printf("Error: Too many sections\n"); return 1; }

        //write a value if whitespace or semicolon
        if ((*(inputBottomNums + i) == 32 && prevWhitespace == False) || *(inputBottomNums + i) == 59 || *(inputBottomNums + i) == 10) {
        
            value -= length;

            //dont write multiple 0'
            if (atoi(value) != 0 || (atoi(value) == 0 && valIndex == 0)) {
                
                *(*(bottomNums + section) + valIndex) = atoi(value);                           //safety write val + sentinel
                *(*(bottomNums + section) + valIndex + 1) = -1;                    
            }
            
            memset(value, '\0', 4); length = 0;
            ++valIndex;
            prevWhitespace = True;

            if (*(inputBottomNums + i) == 59) {
            
                ++section;
                valIndex = 0;
            }

            if (*(inputBottomNums + i) == 10) {
            
                ++section;

                if (section != *size) { printf("Error: not enough sections inputted\n"); return 1; }

                break;
            }
        }

        //read a value
        else if (*(inputBottomNums + i) >= 48 && *(inputBottomNums + i) <= 57) {
            
            *value = *(inputBottomNums + i);
            ++value;
            ++length;
            prevWhitespace = False;
        }
    }

    if (section > *size) { printf("Error: Too many sections\n"); return 1; };

    printf("\n");
    printf("Tops:\n");

    for (int i = 0; i < *size; ++i) {
    
        int j = 0;
        
        while (*(*(topNums + i) + j) != -1 && j < *size) {
        
            printf("%d ", *(*(topNums + i) + j));
            ++j;
        }

        printf("\n");
    }

    printf("\nBottoms:\n");

    for (int i = 0; i < *size; ++i) {
    
        int j = 0;

        while (*(*(bottomNums + i) + j) != -1 && j < *size) {
        
            printf("%d ", *(*(bottomNums + i) + j));
            ++j;
        }

        printf("\n");
    }

    free(value);

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

