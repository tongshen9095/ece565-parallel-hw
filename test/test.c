#include <stdio.h>
#include <omp.h>

#define NUM_COLS 5
#define NUM_ROWS (2*(NUM_COLS-1))

int whichThread[NUM_ROWS][NUM_COLS];

void fillColumn1(int j) {
    #pragma omp for schedule(static, 2)
    for (int i=0; i < NUM_ROWS; i++)
        whichThread[i][j] = omp_get_thread_num();
}

void fillColumn2(int j) {
    for (int i=0; i < NUM_ROWS; i++)
        whichThread[i][j] = omp_get_thread_num();
}

int main() {
    int i, j;
    for (i = 0; i < NUM_ROWS; i++) // initialize the array                                                                                                         
        for (j= 0; j < NUM_COLS; j++)
            whichThread[i][j] = -1;

    #pragma omp parallel num_threads(NUM_COLS - 1)
    fillColumn1(0);

    #pragma omp parallel for num_threads(NUM_COLS - 1)
    for (j = 1; j < NUM_COLS; j++)
        fillColumn2(j);

    for (i = 0; i < NUM_ROWS; i++) { // print out the results                                                                                                  
        for (j= 0; j < NUM_COLS; j++)
            printf(" %2d ", whichThread[i][j]); 
        printf("\n");
    }

    return 0;
}