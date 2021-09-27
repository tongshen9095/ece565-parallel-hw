#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <stdint.h>


void writeOnly(uint64_t * array, int num_elements) {
  for (int i = 0; i < num_elements; i++) {
    array[i] = i;
  }
}

double calc_time(struct timespec start, struct timespec end) { 
  double start_sec = (double)start.tv_sec*1000000000.0 + (double)start.tv_nsec; 
  double end_sec = (double)end.tv_sec*1000000000.0 + (double)end.tv_nsec; 
  if (end_sec < start_sec) {  
    return 0;   
  } else {   
    return end_sec - start_sec;
  } 
}

int main(int argc, char * argv[]) {
  if (argc != 2) {
    printf("Usage: bandwidth <num_elements>\n");
    return EXIT_FAILURE;
  }
  int num_elements = atoi(argv[1]);
  uint64_t * array = (uint64_t*)malloc(num_elements * sizeof(uint64_t));
  for (int i = 0; i < num_elements; i++) {
    array[i] = rand() % num_elements;
  }

  struct timespec start_time, end_time;
  clock_gettime(CLOCK_MONOTONIC, &start_time);
  writeOnly(array, num_elements);
  double num_bytes = num_elements * 8;
  clock_gettime(CLOCK_MONOTONIC, &end_time);

  double elapsed_ns = calc_time(start_time, end_time);
  printf("write: %f GBPS\n", num_bytes / elapsed_ns);
  
  free(array);
}



