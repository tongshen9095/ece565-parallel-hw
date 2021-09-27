#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <stdint.h>


void write_only(uint64_t * array, int num_elements, int num_iters) {
  for (int i = 0; i < num_iters; i++) {
    for (int j = 0; j < num_elements; j++) {
      array[j] = j;
    }
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
  if (argc != 4) {
    printf("Usage: bandwidth <num_elements> <num_iters> <choice>\n");
    return EXIT_FAILURE;
  }
  
  int num_elements = atoi(argv[1]);
  int num_iters = atoi(argv[2]);
  int choice = atoi(argv[3]);
  
  uint64_t * array = (uint64_t*)malloc(num_elements * sizeof(uint64_t));
  for (int i = 0; i < num_elements; i++) {
    array[i] = 0;
  }

  struct timespec start_time, end_time;
  double num_bytes;
  switch(choice) {
  case 1:
    clock_gettime(CLOCK_MONOTONIC, &start_time);
    write_only(array, num_elements, num_iters);
    clock_gettime(CLOCK_MONOTONIC, &end_time);
    num_bytes = num_elements * num_iters * 8;
    break;
    
  }
  
  double elapsed_ns = calc_time(start_time, end_time);
  printf("write traffic only: %f GBPS\n", num_bytes / elapsed_ns);
  
  free(array);
}



