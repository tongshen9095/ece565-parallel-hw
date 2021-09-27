#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <stdint.h>

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
  if (argc != 3) {
    printf("Usage: bandwidth <num_elements> <num_iters>\n");
    return EXIT_FAILURE;
  }
  
  int num_elements = atoi(argv[1]);
  int num_iters = atoi(argv[2]);
  
  uint64_t * array = (uint64_t*)malloc(num_elements * sizeof(uint64_t));
  for (int i = 0; i < num_elements; i++) {
    array[i] = 0;
  }

  struct timespec start_time, end_time;
  clock_gettime(CLOCK_MONOTONIC, &start_time);
  for (int i = 0; i < num_iters; i++) {
    for (int j = 0; j < num_elements; j++) {
      array[j] = j;
    }
  }
  clock_gettime(CLOCK_MONOTONIC, &end_time);
  
  double num_bytes = num_elements * num_iters * 8;
  double elapsed_ns = calc_time(start_time, end_time);
  printf("write only %f: GBPS\n", num_bytes / elapsed_ns);
  
  free(array);
}



