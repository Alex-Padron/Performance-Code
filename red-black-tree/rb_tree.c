#include <stdio.h>
#include <stdlib.h>

#include "./rb_tree.h"

struct rb_tree* rb_create() {
  struct rb_tree* T = malloc(sizeof(struct rb_tree));
  return T;
}

struct rb_node* rb_tree_insert(struct rb_tree* T, int key, int value) {
  struct rb_node* current = T->head;
  while (1) {
    if (current->key < key) {
      if (current->right == 0) {
	current->right = malloc(sizeof(struct rb_node));
	current->right->color = red;
	current->right->key = key;
	current->right->value = value;
	current->right->parent = current;
	++T->size;
	return current->right;
      } else {
	current = current->right;
      }
    } else if (current->key > key) {
      if (current->left == 0) {
	current->left = malloc(sizeof(struct rb_node));
	current->left->color = red;
	current->left->key = key;
	current->left->value = value;
	current->left->parent = current;
	++T->size;
	return current->left;
      } else {
	current = current->left;
      }
    } else { // we see the data has already been inserted
      current->value = value;
      return 0;
    }
  }
}

void swap_colors(struct rb_node* x, struct rb_node* y) {
  int tmp = x->color;
  x->color = y->color;
  y->color = tmp;
}

void rotate_right(struct rb_tree* T, struct rb_node* x) {
  struct rb_node* left = x->left;
  x->left = x->left->right;
  if (x->left) x->left->parent = x;
  left->parent = x->parent;
  if (!x->parent) {
    T->head = left;
  } else if (x == x->parent->left) {
    x->parent->left = left;
  } else {
    x->parent->right = left;
  }
}

void rotate_left(struct rb_tree* T, struct rb_node* x) {
  struct rb_node* right = x->right;
  x->right = right->left;
  if (x->right) x->right->parent = x;
  right->parent = x->parent;
  if (!x->parent) {
    T->head = right;
  } else if (x == x->parent->left) {
    x->parent->left = right;
  } else {
    x->parent->right = right;
  }
}

void rb_rebalance(struct rb_tree* T, struct rb_node* x) {
  while ((x != T->head) && (x->parent->color == red) && (x->color != black)) {
    struct rb_node* parent = x->parent;
    struct rb_node* grandparent = x->parent->parent;
    if (parent == grandparent->left) { // parent is left child
      struct rb_node* uncle = grandparent->right;
      if (uncle && uncle->color == red) {
	grandparent->color = red;
	parent->color = black;
	uncle->color = black;
	x = grandparent;
      } else {
	if (x == parent->right) {
	  rotate_left(T, parent);
	  x = parent;
	  parent = x->parent;
	}
	rotate_right(T, grandparent);
	swap_colors(parent, grandparent);
      }
    } else { // parent is right child
      struct rb_node* uncle = grandparent->left;
      if (uncle && uncle->color == red) {
	grandparent->color = red;
	parent->color = black;
	uncle->color = black;
	x = grandparent;
      } else {
	if (x == parent->left) {
	  rotate_right(T, parent);
	  x = parent;
	  parent = x->parent;
	}
	rotate_left(T, grandparent);
	swap_colors(parent, grandparent);
	x = parent;
      }
    }
  }
  T->head->color = black;
}


void rb_insert(struct rb_tree* T, int key, int value) {
  printf("inserting key %d and value %d into tree\n", key, value);
  if (T->head == 0) {
    T->head = malloc(sizeof(struct rb_node));
    T->head->key = key;
    T->head->value = value;
    T->head->color = black;
    return;
  }
  struct rb_node* inserted = rb_tree_insert(T, key, value);
  if (inserted) {
    printf("started rebalancing\n");
    rb_rebalance(T, inserted);
    printf("finished rebalancing\n");
  } 
}

int rb_find(struct rb_tree* T, int key) {
  if (T->head == 0) {
    return 0;
  }
  struct rb_node* current = T->head;
  while (1) {
    if (current->key < key) {
      if (current->right == 0) return 0;
      current = current->right;
    } else if (current->key > key) {
      if (current->left == 0) return 0;
      current = current->left;
    } else {
      return current->value;
    }
  }
}


int max(int a, int b) {
  if (a > b) return a;
  return b;
}

int rec_height(struct rb_node* x) {
  int height = 0;
  if (x->left) height = rec_height(x->left);
  if (x->right) height = max(rec_height(x->right), height);
  return 1 + height;
}

int height(struct rb_tree* T) {
  if (T->head) return rec_height(T->head);
  printf("unable to find head of tree for height\n");
  return 0;
}

int rec_size(struct rb_node* x) {
  int size = 1;
  if (x->left) size += rec_size(x->left);
  if (x->right) size += rec_size(x->right);
  return size;
}

int size(struct rb_tree* T) {
  if (T->head) return rec_size(T->head);
  printf("unable to find head of tree for size\n");
  return 0;
}

void rb_print_tree(struct rb_tree* T) {
  printf("TREE WITH HEIGHT %d AND SIZE %d\n", height(T), size(T));
}
