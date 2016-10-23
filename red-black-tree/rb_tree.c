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

// [dir == 0] left child, [dir == 1] right child
inline struct rb_node* get_child(struct rb_node* x, int dir) {
  if (dir) return x->right;
  return x->left;
}

// [dir == 0] assign left child, [dir == 1] assign right child
inline void assign_child(struct rb_node* x, struct rb_node* child, int dir) {
  if (dir) {
    x->right = child;
  } else {
    x->left = child;
  }
}

// [dir == 0] rotate left, [dir == 1] rotate right
void rotate(struct rb_tree* T, struct rb_node* x, int dir) {
  int opp_dir = 1;
  if (dir) opp_dir = 0;
  struct rb_node* new_parent = get_child(x, opp_dir);
  assign_child(x, get_child(new_parent, dir), opp_dir);
  if (get_child(x, opp_dir)) get_child(x, opp_dir)->parent = x;
  new_parent->parent = x->parent;
  if (!x->parent) {
    T->head = new_parent;
  } else {
    if (x == get_child(x->parent, dir)) {
      assign_child(x->parent, new_parent, dir);
    } else {
      assign_child(x->parent, new_parent, opp_dir);
    }
  }
  assign_child(new_parent, x, dir);
  x->parent = new_parent;
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
	  rotate(T, parent, 0);
	  x = parent;
	  parent = x->parent;
	}
	rotate(T, grandparent, 1);
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
	  rotate(T, parent, 1);
	  x = parent;
	  parent = x->parent;
	}
	rotate(T, grandparent, 0);
	swap_colors(parent, grandparent);
	x = parent;
      }
    }
  }
  T->head->color = black;
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
  return 0;
}

void rb_insert(struct rb_tree* T, int key, int value) {
  if (T->head == 0) {
    T->head = malloc(sizeof(struct rb_node));
    T->head->key = key;
    T->head->value = value;
    T->head->color = black;
    ++T->size;
    return;
  }
  struct rb_node* inserted = rb_tree_insert(T, key, value);
  if (inserted) {
    rb_rebalance(T, inserted);
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
 
void rb_print_tree(struct rb_tree* T) {
  printf("TREE WITH HEIGHT %d AND SIZE %d\n", height(T), T->size);
}
