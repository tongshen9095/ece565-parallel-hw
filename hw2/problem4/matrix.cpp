#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include <iostream>
#include <vector>

# define N 1024

std::vector<std::vector<double> > initMatrix() {
  std::vector<std::vector<double> > matrix(N, std::vector<double>(N, 0));
  for (int i = 0; i < N; i++) {
    for (int j = 0; j < N; j++) {
      matrix[i][j] = rand() % N;
    }
  }
  return matrix;
}

void multiplyI(std::vector<std::vector<double>> A,
	       std::vector<std::vector<double>> B) {
  std::vector<std::vector<double> > C(N, std::vector<double>(N, 0));
  for (int i = 0; i < N; i++) {
    for (int j = 0; j < N; j++) {
      for (int k = 0; k < N; k++) {
	C[i][j] += A[i][k] * B[k][j];
      }
    }
  }
  std::cout << "C[N - 1][N - 1] = " << C[N - 1][N - 1] << "\n";
}

int main() {
  std::vector<std::vector<double>> A = initMatrix();
  std::vector<std::vector<double>> B = initMatrix();
  multiplyI(A, B);
  return EXIT_SUCCESS;;
}
