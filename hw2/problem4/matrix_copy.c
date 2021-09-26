#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <stdint.h>

# define N 1024

double calc_time(struct timespec start, struct timespec end) {
    double start_sec = (double) start.tv_sec * 1000000000.0 + (double) start.tv_nsec;
    double end_sec = (double) end.tv_sec * 1000000000.0 + (double) end.tv_nsec;
    if (end_sec < start_sec) {
        return 0;
    } else {
        return end_sec - start_sec;
    }
}

void initMatrix(double matrix[N][N]) {
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            matrix[i][j] = rand() % N;
        }
    }
}

// i -> j -> k
void multiply_i(double A[N][N], double B[N][N], double C[N][N]) {
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            double sum = 0;
            for (int k = 0; k < N; k++) {
                sum += A[i][k] * B[k][j];
            }
            C[i][j] = sum;
        }
    }
}


int main(int argc, char *argv[]) {
    double A[N][N];
    double B[N][N];
    double C[N][N];
    initMatrix(A);
    initMatrix(B);

    struct timespec start_time, end_time;
    clock_gettime(CLOCK_MONOTONIC, &start_time);
    multiply_i(A, B, C);
    clock_gettime(CLOCK_MONOTONIC, &end_time);
    double elapsed_ns = calc_time(start_time, end_time);
    printf("Time = %f\n", elapsed_ns);
    return EXIT_SUCCESS;
}
