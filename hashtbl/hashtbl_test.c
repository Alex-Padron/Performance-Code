#include <stdio.h>
#include <stdlib.h>

#include "./fasttime.h"

extern void quicksort(int* A, int i, int j);

int check_sorted(int* A, int size) {
  int i;
  for (i = 0; i < size - 1; i++) {
    if (!(A[i+1] >= A[i])) {
      fprintf(stdout, "index %d is not less that %d", i, i + 1);
      return 0;
    }
  }
  return 1;
}

int main(int argc, char** argv) {
  int SIZE = 1000000;
  int IT = 100;
  int RANGE = 1000000;
  unsigned int SEED = 1;
  int* A = malloc(sizeof(int) * SIZE);
  fasttime_t start, end;
  double total_time = 0;
  int i;
  for (i = 0; i < IT; i++) {
    int j; 
    for (j = 0; j < SIZE; j++) {
      A[j] = rand_r(&SEED) % RANGE;
    }
    start = gettime();
    quicksort(A, 0, SIZE - 1);
    end = gettime();
    total_time += tdiff(start, end);
    if (!check_sorted(A, SIZE)) return -1;
  }
  fprintf(stdout, "Average time: %f seconds\n", total_time / IT);
  free(A);
  return 0;
}




