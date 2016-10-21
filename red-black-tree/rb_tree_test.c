#include <stdio.h>
#include <stdlib.h>

#include "./fasttime.h"
#include "./rb_tree.h"

#define test(x) if(!(x)) {	  \
fprintf(stderr, "failed test\n"); \
return -1; \
} \

int main(int argc, char** argv) {
  printf("testing insert...\n");
  struct rb_tree* r = rb_create();
  printf("testing basic insert and find...\n");
  for (int i = 1; i < 100; i++) {
    rb_insert(r, i, i*i);
  }
  for (int i = 1; i < 100; i++) {
    test(rb_find(r, i) == (i*i));
  }
  rb_print_tree(r);
  printf("...passed\n");
  
  /*
  rb_insert(r, 1, 10);
  test(r->head->key == 1);
  test(r->head->value == 10);
  rb_insert(r, 1, 100);
  test(r->head->key == 1);
  test(r->head->value == 100);
  test(r->head->left == 0);
  test(r->head->right == 0);
  rb_insert(r, 2, 20);
  test(r->head->right->key == 2);
  test(r->head->right->value == 20);
  test(r->head->left == 0);
  test(r->head->key == 1);
  test(r->head->value == 100);
  rb_insert(r, 0, 0);
  test(r->head->left->key == 0);
  test(r->head->left->value == 0);
  rb_insert(r, 4, 40);
  test(r->head->right->right->key == 4);
  test(r->head->right->right->value == 40);
  rb_insert(r, 3, 30);
  test(r->head->right->right->left->key == 3);
  test(r->head->right->right->left->value == 30);
  printf("...passed\n");

  printf("testing find...\n");
  test(rb_find(r, 1) == 100);
  test(rb_find(r, 3) == 30);
  test(rb_find(r, 2) == 20);
  test(rb_find(r, 4) == 40);
  test(rb_find(r, 0) == 0);

  for (int i = 100; i < 1; i++) {
    rb_insert(r, i, i*i);
  }
  for (int i = 100; i < 1; i++) {
    test(rb_find(r, i) == (i*i));
  }
  printf("...passed\n");
  */
  return 0;
}




