#include <stdlib.h>

#include "./hashtbl_lin_prob.h"

/*
  Hash table mapping int32_t keys to int32_t values.
  Cannot insert/find the key 0, since it acts basically as
  null in for signalling a key is not present
 */

// hash and given a result mod 2**size
inline int32_t hash(int32_t x, int32_t size) {
  x = ((x >> 16) ^ x) * 0x45d9f3b;
  x = ((x >> 16) ^ x) *0x45d9f3b;
  x = (x >> 16) ^ x;
  return x >> (32 - size);
}

inline int32_t* new_array(int32_t size) {
  int32_t* a = malloc(sizeof(int32_t) * (1 << size));
  for (int i = 0; i < (1 << size); i++) {
    a[i] = 0;
  }
  return a;
}

// @param size: log size of table, must be less than 32
// @param empty_key: signals a not present key, cannot be inserted
struct Hashtbl* hashtbl_create(int32_t size) {
  struct Hashtbl* hashtbl = malloc(sizeof(struct Hashtbl));
  hashtbl->elements = 0;
  hashtbl->size = size;
  hashtbl->values = new_array(size);
  hashtbl->keys = new_array(size);
  return hashtbl;
}

void hashtbl_free(struct Hashtbl* hashtbl) {
  free(hashtbl->values);
  free(hashtbl->keys);
  free(hashtbl);
}

inline int32_t find_empty_index(int32_t* buckets, int32_t key, int32_t size) {
  int32_t index = hash(key, size);
  while (buckets[index] != 0 && buckets[index] != key) {
    ++index;
    if (index == (1 << size)) index = 0;
  }
  return index;
}

inline int32_t find_key_index(int32_t* buckets, int32_t key, int32_t size) {
  int32_t index = hash(key, size);
  int32_t start = index;
  while (buckets[index] != key) {
    ++index;
    if (index == (1 << size)) index = 0;
    if (index == start) return -1;
  }
  return index;
}

void print_array(int32_t* a, int32_t size) {
  for (int i = 0; i < (1 << size); i++) {
    printf("%d ", a[i]);
  }
  printf("\n");
}

void resize(struct Hashtbl* hashtbl, int32_t new_size) {
  int32_t* new_keys = new_array(new_size);
  int32_t* new_values = new_array(new_size);
  int i;
  for (i = 0; i < (1 << hashtbl->size); i++) {
    int key = hashtbl->keys[i];
    if (key != 0) {
      int value = hashtbl->values[i];
      int index = find_empty_index(new_keys, key, new_size);
      new_keys[index] = key;
      new_values[index] = value;
    }
  }
  free(hashtbl->keys);
  free(hashtbl->values);
  hashtbl->keys = new_keys;
  hashtbl->values = new_values;
  hashtbl->size = new_size;
}

void check_resize(struct Hashtbl* hashtbl) {
  if (hashtbl->elements > (1 << (hashtbl->size - 1))) {
    resize(hashtbl, hashtbl->size + 1);
  } else if (hashtbl->elements < (1 << (hashtbl->size - 2)) && hashtbl->size > 2) {
    resize(hashtbl, hashtbl->size - 1);
  }
}

void hashtbl_insert(struct Hashtbl* hashtbl, int32_t key, int32_t value) {
  check_resize(hashtbl);
  int index = find_empty_index(hashtbl->keys, key, hashtbl->size);
  if (hashtbl->keys[index] != key) {
    hashtbl->keys[index] = key;
    hashtbl->elements++;
  }
  hashtbl->values[index] = value;
} 

int32_t hashtbl_find(struct Hashtbl* hashtbl, int32_t key) {
  int index = find_key_index(hashtbl->keys, key, hashtbl->size);
  if (index == -1) return 0;
  return hashtbl->values[index];
}

void hashtbl_remove(struct Hashtbl* hashtbl, int32_t key) {
  check_resize(hashtbl);
  int index = find_key_index(hashtbl->keys, key, hashtbl->size);
  if (index != -1) {
    hashtbl->keys[index] = 0;
    hashtbl->elements--;
  }
}





