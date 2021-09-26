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

double calc_time(struct timeval start, struct timeval end) {
  double start_sec = (double) start.tv_sec * 1000000.0 + (double) start.tv_usec;
  double end_sec = (double) end.tv_sec * 1000000.0 + (double) end.tv_usec;
  if (end_sec < start_sec) {
    return 0;
  } else {
    return end_sec - start_sec;
  }
}

int main() {
  std::vector<std::vector<double>> A = initMatrix();
  std::vector<std::vector<double>> B = initMatrix();

  struct timeval start_time, end_time;
  gettimeofday(&start_time, NULL);
  multiplyI(A, B);
  gettimeofday(&end_time, NULL);

  double elapsed_s = calc_time(start_time, end_time) / 1000000.0;
  std::cout << "Time = " << elapsed_s << " seconds" << "\n";

  return EXIT_SUCCESS;;
}
