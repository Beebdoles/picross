#include <stdlib.h>
#include <string.h>
#include <stdio.h>


#define True 1
#define False 0


//other vars


int main(void);
int countComponents(void);
int createValidCombinations(int* grid, int val, int index, int depth);


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

    return 0;
}

int createValidCombinations(int* grid, int val, int index, int depth) {

    if (val == 0) { return 0; }

    grid[depth * 10 + index] = val;
    

    return 0;
}
