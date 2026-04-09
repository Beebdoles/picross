#include "Grid.h"

Grid* createGrid(int size, char* vals) {

   Grid* newGrid = (Grid*)malloc(sizeof(Grid));
   if (!newGrid) { return NULL; }

    newGrid->size = size;
    newGrid->grid = (int*)malloc(sizeof(int) * size * size);
    newGrid->sequences = (Sequence**)malloc(sizeof(Sequence*) * size * 2);

    for (int i = 0; i < size * size; ++i) { *(newGrid->grid + i) = i; }

   return newGrid;
}

void printGrid(Grid* grid) {

    for (int i = 0; i < grid->size; ++i) {
    
        for (int j = 0; j < grid->size; ++j) {
        
            printf("%d ", *(grid->grid + (i * 10 + j)));
            
            if (i == 0) { printf(" "); }
        }

        printf("\n");
    }
}

void freeGrid(Grid* gd) {

    free(gd->grid);
    
    for (int i = 0; i < gd->size * 2; ++i) {
    
        free(*(gd->sequences + i));
    }

    free(gd->sequences);
    free(gd);
    gd = NULL;
}
