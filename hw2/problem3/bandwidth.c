#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <stdint.h>

void write_only(uint64_t * array, int num_elements, int num_iters) {
  for (int i = 0; i < num_iters; i++) {
    for (int index = 0; index < num_elements; index++) {
      array[index] = 1;
    }
  }
}

void read_write_1_1(uint64_t * array, int num_elements, int num_iters) {
  for (int i = 0; i < num_iters; i++) {
    for (int index = 0; index < num_elements; index++) {
      array[index] = array[index] + 1;
    } 
  }
}

void read_write_2_1(uint64_t * array, int num_elements, int num_iters) {
  for (int i = 0; i < num_iters; i++) {
    for (int index = 0; index < num_elements - 1; index++) {
      array[index] = array[index] + array[index + 1];
    }
    array[num_elements - 1] = array[num_elements - 1] + array[0];
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
  
  if (num_elements != 4096 && num_elements != 4000000) {
    printf("The number of elements can only be 4096 or 4000000\n");
    return EXIT_FAILURE;
  }

  if (choice != 1 && choice != 2 && choice != 3) {
    printf("The choice can only be 1, 2 or 3\n");
    return EXIT_FAILURE;
  }
  
  uint64_t * array = (uint64_t*)malloc(num_elements * sizeof(uint64_t));
  for (int index = 0; index < num_elements; index++) {
    array[index] = index;
  }

  struct timespec start_time, end_time;
  double num_bytes;
  switch(choice) {
  case 1:
    clock_gettime(CLOCK_MONOTONIC, &start_time);
    write_only(array, num_elements, num_iters);
    clock_gettime(CLOCK_MONOTONIC, &end_time);
    num_bytes = num_elements * num_iters * 8;
    printf("write traffic only: ");
    break;
  case 2:
    clock_gettime(CLOCK_MONOTONIC, &start_time);
    read_write_1_1(array, num_elements, num_iters);
    clock_gettime(CLOCK_MONOTONIC, &end_time);
    num_bytes = num_elements * num_iters * 8 * 2;
    printf("1:1 read-to-write: ");
    break;
  case 3:
    clock_gettime(CLOCK_MONOTONIC, &start_time);
    read_write_2_1(array, num_elements, num_iters);
    clock_gettime(CLOCK_MONOTONIC, &end_time);
    num_bytes = num_elements * num_iters * 8 * 3;
    printf("2:1 read-to-write: ");
    break;
  }
  
  double elapsed_ns = calc_time(start_time, end_time);
  printf("%f GBPS\n", num_bytes / elapsed_ns);
  
  free(array);
}



