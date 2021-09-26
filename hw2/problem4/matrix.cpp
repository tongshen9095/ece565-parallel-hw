#include <stdio.h>
#include <sys/time.h>
#include <stdlib.h>
#include <stdint.h>
#include <iostream>
#include <vector>

# define N 1024

double ** initMatrix() {
  double ** matrix = new double * [N];
  for (int i = 0; i < N; i++) {
    matrix[i] = new double[N];
  }
  for (int i = 0; i < N; i++) {
    for (int j = 0; j < N; j++) {
      matrix[i][j] = rand() % N;
    }
  }
}

void freeMatrix(double ** matrix) {
  for (int i = 0; i < N; i++) {
    delete[] matrix[i];
  }
  delete[] matrix;
}

int main() {
  double ** A = initMatrix();
  freeMatrix(A);
  return EXIT_SUCCESS;;
}
