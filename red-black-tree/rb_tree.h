/*
  Implementation of a Red-Black tree.
 */

struct rb_node {
  enum {RED, BLACK} color;
  int key;
  int value;
  struct rb_node *left, *right, *parent;
};

struct rb_tree {
  int size;
  struct rb_node* head;
};

/*
  Create a new rb tree 
 */
struct rb_tree* rb_create();

/*
  Insert a key-value pair into the tree
 */
void rb_insert(struct rb_tree* T, int key, int value);

/*
  Find the value corresponding to a given key in the tree.
  Returns 0 if the key is not in the tree
 */
int rb_find(struct rb_tree* T, int key);

/*
  Get the height of the tree in linear time
 */
int height(struct rb_tree* T);
