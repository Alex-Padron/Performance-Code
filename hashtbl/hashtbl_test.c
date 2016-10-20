#include <stdio.h>
#include <stdlib.h>

#include "./fasttime.h"
#include "./hashtbl_lin_prob.c"

#define test(x) if(!(x)) {	  \
fprintf(stderr, "failed test\n"); \
return -1; \
} \


int main(int argc, char** argv) {
  struct Hashtbl* h = hashtbl_create(3);
  printf("running hashtbl tests...\n");
  printf("basic tests...\n");
  hashtbl_insert(h, 1, 2);
  test(hashtbl_find(h, 1) == 2);
  hashtbl_remove(h, 1);
  test(hashtbl_find(h, 1) == 0);
  for (int i = 1; i < 8; i++) {
    hashtbl_insert(h, i, i);
  }
  for (int i = 1; i < 8; i++) {
    fprintf(stdout, "found value %d at index %d\n", hashtbl_find(h, i), i);
    test(hashtbl_find(h, i) == i);
  }
  for (int i = 1; i < 8; i++) {
    hashtbl_remove(h, i);
  }
  printf("test resizing...\n");
  for (int i = 1; i < 1000; i++) {
    if ((i % 100) == 0) printf("inserting %d\n", i);
    hashtbl_insert(h, i, i);
  }
  for (int i = 1; i < 1000; i++) {
    test(hashtbl_find(h, i) == i);
  }
  printf("...passed\n");
  return 0;
}




