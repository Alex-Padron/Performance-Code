#include <stdint.h>

#ifndef _hashtbl_lin_prob_
#define _hashtbl_lin_prob_

struct Hashtbl {
  int32_t elements; // number of elements in the table
  int32_t size; // log size of table
  int32_t* values; // table of values
  int32_t* keys; // table of keys for given indices
};

struct Hashtbl* hashtbl_create(int32_t size);

void hashtbl_insert(struct Hashtbl* hashtbl, int32_t key, int32_t value);

// return 0 if key not in table
int32_t hashtbl_find(struct Hashtbl* hashtbl, int32_t key);

void hashtbl_remove(struct Hashtbl* hashtbl, int32_t key);

#endif
