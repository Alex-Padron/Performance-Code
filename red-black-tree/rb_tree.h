#include <stdint.h>

struct rb_node {
  enum {red, black} color;
  int key;
  int value;
  struct rb_node *left, *right, *parent;
};

struct rb_tree {
  int size;
  struct rb_node* head;
};

struct rb_tree* rb_create();

void rb_insert(struct rb_tree* T, int key, int value);

// return 0 if the element is not present
int rb_find(struct rb_tree* T, int key);

// linear time
int height(struct rb_tree* T);

//linear time
int size(struct rb_tree* T);

void rb_print_tree(struct rb_tree* T);
