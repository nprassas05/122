/* Hash tables (auto-resizing)
 *
 * 15-122 Principles of Imperative Computation, Fall 2012
 */

#include <stdbool.h>
#include <stdlib.h>
#include <limits.h>

#include "lib/xalloc.h"
#include "lib/contracts.h"

#include "ht.h"

/* Interface type definitions */
/* see ht.h */

struct chain_node {
  ht_elem data;			/* data != NULL */
  struct chain_node* next;
};
typedef struct chain_node chain;

struct ht_header {
  int size;			/* size >= 0 */
  int capacity;			/* capacity > 0 */
  chain **table;		/* \length(table) == capacity */
  ht_key (*elem_key)(ht_elem e);
  bool (*key_equal)(ht_key k1, ht_key k2);
  int (*key_hash)(ht_key k, int m);
  void (*elem_free)(ht_elem e);
};

inline ht_key elemkey(ht H, elem e) {
  return (*H->elem_key)(e);
}

inline int keyhash(ht H, ht_key k, int m) {
  return (*H->key_hash)(k, m);
}

bool is_ht(ht H) {
  if (H == NULL) return false;
  if (!(H->size >= 0)) return false;
  if (!(H->capacity > 0)) return false;
  if (H->elem_key == NULL) return false;
  if (H->key_equal == NULL) return false;
  if (H->key_hash == NULL) return false;
  /* H->elem_free can be NULL */
  // assert \length(H->table) == H->capacity;
  int count = 0;		/* elements found in hash table */
  for (int i = 0; i < H->capacity; i++) {
      chain *p = H->table[i];
      while (p != NULL) {
	if (!(p->data != NULL)) return false;
	if (!(keyhash(H, elemkey(H, p->data), H->capacity) == i)) return false;
	count++;
	if (!(count <= H->size)) return false;
	p = p->next;
      }
    }
  if (!(count == H->size)) return false;
  return true;
}

ht ht_new(int capacity,
          ht_key (*elem_key)(ht_elem e),
          bool (*key_equal)(ht_key k1, ht_key k2),
          int (*key_hash)(ht_key k, int m),
          void (*elem_free)(ht_elem e))
{
  REQUIRES(capacity > 0);
  ht H = xmalloc(sizeof(struct ht_header));
  H->size = 0;
  H->capacity = capacity;
  H->table = xcalloc(capacity, sizeof(chain*));
  H->elem_key = elem_key;
  H->key_equal = key_equal;
  H->key_hash = key_hash;
  H->elem_free = elem_free;
  /* initialized to NULL */
  ENSURES(is_ht(H));
  return H;
}

/* ht_lookup(H, k) returns NULL if key k not present in H */
ht_elem ht_lookup(ht H, ht_key k)
{
  REQUIRES(is_ht(H));
  int i = keyhash(H, k, H->capacity);
  chain* p = H->table[i];
  while (p != NULL) {
    ASSERT(p->data != NULL);
    if (keyequal(H, elemkey(H,p->data), k))
      return p->data;
    else
      p = p->next;
  }
  /* not in chain */
  return NULL;
}

void ht_resize(ht H, int new_capacity)
{
  REQUIRES(is_ht(H));
  REQUIRES(new_capacity > 0);
  // printf("(resizing hash table to capacity %d)\n", new_capacity);
  chain **old_table = H->table;
  chain **new_table = xcalloc(new_capacity, sizeof(chain*));
  /* new_table is initialized to all NULL */
  for (int i = 0; i < H->capacity; i++) {
    chain *p = old_table[i];
    while (p != NULL) {
      chain *q = p->next;	/* save p->next */
      ht_elem e = p->data;
      //@assert e != NULL;
      int h = keyhash(H, elemkey(H, e), new_capacity);
      p->next = new_table[h];
      new_table[h] = p;
      p = q;
    }
  }
  /* change ht H in place */
  /* H->size remains unchanged */
  H->capacity = new_capacity;
  H->table = new_table;
  ENSURES(is_ht(H));
  ENSURES(H->capacity == new_capacity);
  return;
}

void ht_insert(ht H, ht_elem e) {
  REQUIRES(is_ht(H));
  REQUIRES(e != NULL);
  ht_key k = elemkey(H, e);
  int i = keyhash(H, k, H->capacity);

  chain *p = H->table[i];
  while (p != NULL)
    // loop invariant: p points to chain
    {
      ASSERT(p->data != NULL);
      if (keyequal(H, elemkey(H, p->data), k))
	{
	  /* overwrite existing element */
	  p->data = e;
	  return;
	} else {
	p = p->next;
      }
    }
  ASSERT(p == NULL);

  /* prepend new element */
  chain* q = xmalloc(sizeof(struct chain_node));
  q->data = e;
  q->next = H->table[i];
  H->table[i] = q;
  (H->size)++;

  /* resize hash table if load factor would be > 1 */
  if (H->size > H->capacity && H->capacity < INT_MAX/2)
    /* load factor > 1 */
    ht_resize(H, 2*H->capacity);

  ENSURES(is_ht(H));
  ENSURES(ht_lookup(H, elemkey(H, e) != NULL));

  return;
}

void chain_free(chain *p, void (*elem_free)(ht_elem e));

void ht_free(ht H);
