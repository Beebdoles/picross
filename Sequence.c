
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
    newSequence->combinationValues = (int**)malloc(sizeof(int*) * combinationsCalc);
    newSequence->solution = (int*)malloc(sizeof(int) * size);
    newSequence->invalidsCount = 0;
    newSequence->invalids = (int*)malloc(sizeof(int) * 5);

    for (int i = 0; i < size; ++i) { *(newSequence->solution + i) = 0; }

    newSequence->combinationsCount = 0;
    newSequence->validCombinations = 0;
    newSequence->size = size;

    return newSequence;
}

void appendCombination(Sequence* sq, int* combination, int size) {
    
    int* values = (int*)malloc(sizeof(int) * size);
    
    for (int i = 0; i < size; ++i) { *(values + i) = *(combination + i); }
    
    *(sq->combinations + sq->combinationsCount) = values;
    ++sq->combinationsCount;
    ++sq->validCombinations;

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

void createCombinationValues(Sequence* sq) {

    int count = 0;

    for (int i = 0; i < sq->combinationsCount; ++i) {
    
        int* combinationValue = (int*)malloc(sizeof(int) * sq->size);

        for (int j = 0; j < sq->valueCount; ++j) {
            
            for (int k = 0; k < *(*(sq->combinations + i) + j); ++k) {
            
                *combinationValue = 0;
                ++combinationValue;
                //printf("0");
            }

            for (int k = 0; k < *(sq->values + j); ++k) {
            
                *combinationValue = 1;
                ++combinationValue;
                //printf("1");
            }

            if (j + 1 < sq->valueCount) { 
                
                *combinationValue = 0;
                ++combinationValue;
                //printf("0");
            }
        }
        for (int j = 0; j < *(*(sq->combinations + i) + sq->valueCount); ++j) {

            *combinationValue = 0;
            ++combinationValue;
            //printf("0");
        }
        //printf("\n");
        //this is a bit fragile maybe, but it shoudl work?
        combinationValue -= sq->size;
        *(sq->combinationValues + count) = combinationValue;
        ++count;
    }

    for (int i = 0; i < sq->size; ++i) {
    
        for (int j = 0; j < sq->combinationsCount; ++j) {

            *(sq->solution + i) += *(*(sq->combinationValues + j) + i);
        }
    }

    for (int i = 0; i < sq->size; ++i) {

        if (*(sq->solution + i) == sq->combinationsCount) { *(sq->solution + i) = 1; }
        else { *(sq->solution + i) = 0; }
    }
}

int generateSolution(Sequence* sq, int* invalids, int count) {

    for (int i = 0; i < sq->combinationsCount; ++i) {
   
        if (*(sq->combinationValues + i) == NULL) { continue; }

        for (int j = 0; j < count; ++j) {
        
            if (*(*(sq->combinationValues + i) + *(invalids + j)) == 1) { 

                free(*(sq->combinationValues + i));
                *(sq->combinationValues + i) = NULL;
                --sq->validCombinations;
            }
        }
    }

    for (int i = 0; i < sq->size; ++i) {

        *(sq->solution + i) = 0;
    
        for (int j = 0; j < sq->combinationsCount; ++j) {
            
            if (*(sq->combinationValues + j) == NULL) { continue; }

            *(sq->solution + i) += *(*(sq->combinationValues + j) + i);
        }

        if (*(sq->solution + i) == sq->validCombinations) { *(sq->solution + i) = 1; }
        else { *(sq->solution + i) = 0; }
    }

    return 0;
}

void printCombinations(Sequence* sq) {

    for (int i = 0; i < sq->combinationsCount; ++i) {

        for (int j = 0; j < sq->valueCount + 1; ++j) {
        
            printf("%d ", *(*(sq->combinations + i) + j));
        }
        printf("\n");
    }
}

void printCombinationValues(Sequence* sq) {

    for (int i = 0; i < sq->combinationsCount; ++i) {
    
        for (int j = 0; j < sq->size; ++j) {
        
            printf("%d ", *(*(sq->combinationValues + i) + j));
        }
        printf("\n");
    }
}

void printSolution(Sequence* sq) {

    for (int i = 0; i < sq->size; ++i) {
    
        printf("%d ", *(sq->solution + i));
    }
    printf("\n");
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

void freeSequence(Sequence* sq) {

    free(sq->invalids);
    free(sq->solution);

    for (int i = 0; i < sq->combinationsCount; ++i) {
    
        if (*(sq->combinationValues + i) != NULL) { 

            free(*(sq->combinationValues + i)); 
        }

        free(*(sq->combinations + i));
    }

    free(sq->combinationValues);
    free(sq->combinations);
    free(sq);
    sq = NULL;
}
