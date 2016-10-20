#include <cilk/cilk.h>

inline void swap(int* A, int i, int j) {
  int tmp = A[i];
  A[i] = A[j];
  A[j] = tmp;
}

inline int partition(int* A, int i, int j) {
  int pivot = A[j];
  int h = i;
  while (i < j) {
    if (A[i] < pivot) {
      if (i > h) {
	swap(A, i, h);
      }
      ++h;
    }
    ++i;
  }
  swap(A, h, j);
  return h;
}

inline void insertion_sort(int* A, int i, int j) {
  for (int s = i; s <= j; s++) {
    int t = s;
    while (t > i && A[t] < A[t - 1]) {
      swap(A, t, t - 1);
      t -= 1;
    }
  }
}

void quicksort(int* A, int i, int j) {
  if (i >= j - 10) {
    insertion_sort(A, i, j);
    return;
  }
  int h = partition(A, i, j);
  cilk_spawn quicksort(A, i, h - 1);
  quicksort(A, h + 1, j);
  cilk_sync;
}

