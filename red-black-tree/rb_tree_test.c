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
  rb_insert(r, 1, 10);
  assert(r->head->key == 1);
  assert(r->head->value == 10);
  rb_insert(r, 2, 20);
  assert(r->head->right->key == 2);
  assert(r->head->right->value == 20);
  rb_insert(r, 3, 30);
  test(r->head->key == 2);
  test(r->head->value == 20);
  test(r->head->left->key == 1);
  test(r->head->left->value == 10);
  test(r->head->right->key == 3);
  test(r->head->right->value == 30); 
  test(r->head->color == BLACK);
  test(r->head->left->color == RED);
  test(r->head->right->color == RED);
  rb_insert(r, -1, -10);
  test(r->head->color == BLACK);
  test(r->head->key == 2);
  test(r->head->left->color == BLACK);
  test(r->head->left->key == 1);
  test(r->head->right->color == BLACK);
  test(r->head->right->key == 3);
  test(r->head->left->left->color == RED);
  test(r->head->left->left->key == -1);
  rb_insert(r, -2, -20);
  test(r->head->left->key == -1);
  test(r->head->left->color == BLACK);
  test(r->head->left->right->key == 1);
  test(r->head->left->right->color == RED);
  test(r->head->left->left->key == -2);
  test(r->head->left->left->color == RED);
  printf("testing find...\n");
  test(rb_find(r, -2) == -20);
  test(rb_find(r, -1) == -10);
  test(rb_find(r, 1) == 10);
  test(rb_find(r, 2) == 20);
  test(rb_find(r, 3) == 30);
  printf("testing many inserts...\n");
  for (int i = 1; i < 100; i++) {
    rb_insert(r, i, i*i);
  }
  for (int i = 1; i < 100; i++) {
    test(rb_find(r, i) == (i*i));
  }
  printf("...passed\n");
  return 0;
}




