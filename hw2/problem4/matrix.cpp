#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include <iostream>
#include <vector>

# define N 1024
# define step 128

std::vector<std::vector<double>> initMatrix() {
  std::vector<std::vector<double>> matrix(N, std::vector<double>(N, 0));
  for (int i = 0; i < N; i++) {
    for (int j = 0; j < N; j++) {
      matrix[i][j] = rand() % N;
    }
  }
  return matrix;
}

// I-J-K
void multiplyI(std::vector<std::vector<double>> A,
	       std::vector<std::vector<double>> B) {
  std::vector<std::vector<double> > C(N, std::vector<double>(N, 0));
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

// J-K-I
void multiplyII(std::vector<std::vector<double>> A,
		std::vector<std::vector<double>> B) {
  std::vector<std::vector<double> > C(N, std::vector<double>(N, 0));
  for (int j = 0; j < N; j++) {
    for (int k = 0; k < N; k++) {
      double temp = B[k][j];
      for (int i = 0; i < N; i++) {
	C[i][j] += A[i][k] * temp;
      }
    }
  }
}

// I-K-J
void multiplyIII(std::vector<std::vector<double>> A,
		 std::vector<std::vector<double>> B) {
  std::vector<std::vector<double> > C(N, std::vector<double>(N, 0));
  for (int i = 0; i < N; i++) {
    for (int k = 0; k < N; k++) {
      double temp = A[i][k];
      for (int j = 0; j < N; j++) {
	C[i][j] += temp * B[k][j];
      }
    }
  }
}

// loop tiling for I-J-K
void multiplyLoopTiling(std::vector<std::vector<double>> A,
			std::vector<std::vector<double>> B) {
  std::vector<std::vector<double> > C(N, std::vector<double>(N, 0));
  for (int i = 0; i < N; i += step) {
    for (int j = 0; j < N; j += step) {
      for (int ii = i; ii < i + step; ii++) {
	for (int jj = j; jj < j + step; jj++) {
	  for (int k = 0; k < N; k++) {
	    C[i][j] += A[ii][k] * B[k][jj];
	  }
	}
      }
    }
  }
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

int main(int argc, char * argv[]) {
  if (argc != 2) {
    std::cout << "Usage: ./matrix <choice>" << "\n";
    return EXIT_FAILURE;
  }
  int choice = atoi(argv[1]);
  
  std::vector<std::vector<double>> A = initMatrix();
  std::vector<std::vector<double>> B = initMatrix();

  struct timeval start_time, end_time;
  switch(choice) {
  case 1:
    gettimeofday(&start_time, NULL);
    multiplyI(A, B);
    gettimeofday(&end_time, NULL);
    std::cout << "I-J-K ";
    break;
  case 2:
    gettimeofday(&start_time, NULL);
    multiplyII(A, B);
    gettimeofday(&end_time, NULL);
    std::cout << "J-K-I ";
    break;
  case 3:
    gettimeofday(&start_time, NULL);
    multiplyIII(A, B);
    gettimeofday(&end_time, NULL);
    std::cout << "I-K-J ";
    break;
  case 4:
    gettimeofday(&start_time, NULL);
    multiplyLoopTiling(A, B);
    gettimeofday(&end_time, NULL);
    std::cout << "Loop tiling for I-J-K ";
    break;
  }

  double elapsed_s = calc_time(start_time, end_time) / 1000000.0;
  std::cout << "time: " << elapsed_s << " seconds" << "\n";

  return EXIT_SUCCESS;;
}
