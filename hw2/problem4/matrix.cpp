#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include <iostream>
#include <vector>

# define N 1024

std::vector<std::vector<double>> initMatrix() {
  std::vector<std::vector<double> > matrix(N, std::vector<double>(N, 0));
  for (int i = 0; i < N; i++) {
    for (int j = 0; j < N; j++) {
      matrix[i][j] = rand() % N;
    }
  }
  return matrix;
}

int main() {
  std::vector<std::vector<double>> A = initMatrix();
  std::vector<std::vector<double>> B = initMatrix();
  
  return EXIT_SUCCESS;;
}
