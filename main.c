#include "Sequence.h"
#include "Grid.h"

//other vars


int main(void);
int countComponents(void);
int createValidCombinations(int* grid, int val, int index, int depth);
void test(void);
void parse(void);
void freeMemory(Sequence* sq);

int main(void) {
    
    //test();
    parse();

    return 0;
}

void parse() {

    char input[500];
    fgets(input, 500 - 1, stdin);
    input[499] = '\0';
    printf("%s\n", input);



    int** vals = (int**)malloc(sizeof(int*) * 10);
    int j, k, jMax, kMax = 0;
    int prevWhitespace = 1; 
    char val[3]; val[0] = '\0'; val[1] = '\0'; val[2] = '\0';
    int index = 0;

    for (int i = 0; i < 500 - 1; ++i) {
   
        if (input[i] == '\0') { break; }

        printf("element: %c\n", input[i]);

        if (input[i] == ' ' && prevWhitespace == 0) {  

            printf("here1\n");
            prevWhitespace = 1;
            printf("%d\n", atoi(val));
            *(*(vals + j) + k) = atoi(val);
            index = 0;
            printf("here1.5\n");
            val[0] = 0; val[1] = 0;
            prevWhitespace = 1;
            ++k;
            printf("here2\n");
        }
        else if (input[i] == '|') {
        
            prevWhitespace = 1;
            *(*(vals + j) + k + 1) = -1;
            ++j;
            ++jMax;
            if (kMax < k) { kMax = k; }
            k = 0;
        }
        else {
            val[index] = input[i];
            prevWhitespace = 0;
            ++index;
        }
    }

    for (int i = 0; i < jMax; ++i) {

        int currVal = 0;

        while (*(*(vals + i) + currVal) != -1) {
        
            printf("%d ", *(*(vals + i) + currVal));
            ++currVal;
        }
        printf("\n");
    }
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

