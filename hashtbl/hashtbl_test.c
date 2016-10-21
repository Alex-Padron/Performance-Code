#include <stdio.h>
#include <stdlib.h>

#include "./fasttime.h"
#include "./hashtbl_lin_prob.c"

#define test(x) if(!(x)) {	  \
fprintf(stderr, "failed test\n"); \
return -1; \
} \

int32_t* generate_random_array(int length, unsigned int* seed) {
  int32_t* a = malloc(sizeof(int32_t) * length);
  for (int i = 0; i < length; i++) {
    int r = rand_r(seed);
    if (r == 0) r = 1;
    a[i] = r;
  }
  return a;
}

void test_performance() {
  int SIZE;
  int IT;
  unsigned int seed = 1;
  fasttime_t start, end;
  double total_time;
  struct Hashtbl* h = hashtbl_create(0);
  printf("testing lots of inserts then queries then deletes\n");
  SIZE = 10000;
  IT = 1000;
  total_time = 0;
  int count = 0;
  for (int i = 0; i < IT; i++) {
    int32_t* a = generate_random_array(SIZE, &seed);
    start = gettime();
    for (int j = 0; j < SIZE; j++) {
      hashtbl_insert(h, a[j], j);
    }
    for (int j = 0; j < SIZE; j++) {
      // store to count so this loop isn't optimized away
      count += hashtbl_find(h, a[j]); 
    }
    for (int j = 0; j < SIZE; j++) {
      hashtbl_remove(h, a[j]);
    }
    end = gettime();
    total_time += tdiff(start, end);
  }
  printf("average time per iteration is %lf seconds\n", total_time / IT);
}

int main(int argc, char** argv) {
  struct Hashtbl* h = hashtbl_create(3);
  printf("running correctness tests\n");
  hashtbl_insert(h, 1, 2);
  test(hashtbl_find(h, 1) == 2);
  hashtbl_remove(h, 1);
  test(hashtbl_find(h, 1) == 0);
  test(h->elements == 0);
  test(h->size == 2);
  for (int i = 1; i < 8; i++) {
    hashtbl_insert(h, i, i);
  }
  for (int i = 1; i < 8; i++) {
    test(hashtbl_find(h, i) == i);
  }
  for (int i = 1; i < 8; i++) {
    hashtbl_remove(h, i);
  }
  test(h->elements == 0);
  test(h->size == 2);
  for (int i = 1; i < 1000; i++) {
    hashtbl_insert(h, i, i);
  }
  test(h->elements == 999);
  test(h->size == 11);
  for (int i = 1; i < 1000; i++) {
    test(hashtbl_find(h, i) == i);
    hashtbl_remove(h, i);
  }
  test(h->elements == 0);
  test(h->size == 2);
  printf("...passed\n");
  hashtbl_free(h);

  test_performance();
  return 0;
}




