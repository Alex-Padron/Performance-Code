#include "./hash.c"

/*
  Simple hash table mapping int32 keys to int32 values
 */

struct Hashtbl {
  int32 elements; // number of elements in the table
  int32 size; // size of the table
  int23* table; // pointer to table
};

struct Hashtbl* hashtbl_create(int32 size) {
  struct Hashtbl* hashtbl;
  hashtbl->elements = 0;
  hashtbl->size = size;
  hashtbl->table = malloc(sizeof(int32) * size);
  return hashtbl;
}

void hashtbl_free(struct Hashtbl* hashtbl) {
  free(hashtbl->table);
}

void hashtbl_insert(int32* hashtbl, int32 key, int32 value) {
} 
