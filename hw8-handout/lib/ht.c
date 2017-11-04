/* 
 * Hash tables, automatic resizing to keep load factor < 1
 *
 * 15-122 Principles of Imperative Computation */

#include <stdbool.h>
#include <stdlib.h>
#include <limits.h>
#include "xalloc.h"
#include "contracts.h"
#include "ht.h"

struct chain_node {
  ht_elem data;                 /* data != NULL */
  struct chain_node* next;
};
typedef struct chain_node chain;

struct ht_header {
  size_t size;                  /* size >= 0 */
  size_t capacity;              /* capacity > 0 */
  chain **table;                /* \length(table) == capacity */
  ht_key (*elem_key)(ht_elem e);
  bool (*key_equal)(ht_key k1, ht_key k2);
  size_t (*key_hash)(ht_key k);
  void (*elem_free)(ht_elem e);
};

// Basic hashtable properties
// (Not violated as we change the data structure)
bool is_safe_ht(ht H) {
  if (H == NULL) return false;
  if (!(H->capacity > 0)) return false;
  if (H->elem_key == NULL) return false;
  if (H->key_equal == NULL) return false;
  if (H->key_hash == NULL) return false;
  /* H->elem_free can be NULL */
  return true;
}

static inline ht_key elemkey(ht H, ht_elem e) {
  REQUIRES(is_safe_ht(H)); 
  return (*H->elem_key)(e);
}

static inline bool keyequal(ht H, ht_key k1, ht_key k2) {
  REQUIRES(is_safe_ht(H)); 
  return (*H->key_equal)(k1, k2);
}

static inline size_t keyhash(ht H, ht_key k) {
  REQUIRES(is_safe_ht(H)); 
  return (*H->key_hash)(k);
}

// Checks that a chain contains only non-NULL elements and is a valid chain
// at index i of a table with modulus m.
// If counter != NULL, increments *counter with size of chain.
// May fail to terminate in the presence of circularity.
static bool is_chain(ht H, chain *p, size_t i, size_t *counter) {
  REQUIRES(is_safe_ht(H)); 
  REQUIRES(i < H->capacity);

  while (p != NULL) {
    if (!(p->data != NULL)) return false;
    if (!(keyhash(H, elemkey(H, p->data)) % H->capacity == i)) return false;
    if (counter != NULL) (*counter)++;
    p = p->next;
  }
  return true;
}

bool is_ht(ht H) {
  if (!(is_safe_ht(H))) return false;
  /* Cannot check that \length(H->table) == H->capacity */

  size_t count = 0;   /* Count number of elements in table */
  for (size_t i = 0; i < H->capacity; i++) {
    is_chain(H, H->table[i], i, &count);
  }
  if (!(count == H->size)) return false;

  return true;
}

ht ht_new(size_t capacity,
          ht_key (*elem_key)(ht_elem e),
          bool (*key_equal)(ht_key k1, ht_key k2),
          size_t (*key_hash)(ht_key k),
          void (*elem_free)(ht_elem e)) {
  REQUIRES(capacity > 0);
  REQUIRES(elem_key != NULL);
  REQUIRES(key_equal != NULL);
  REQUIRES(key_hash != NULL);

  ht H = xmalloc(sizeof(struct ht_header));
  H->size = 0;
  H->capacity = capacity;
  H->table = xcalloc(capacity, sizeof(chain*));
  /* Table elements all initialized to NULL by xcalloc */
  H->elem_key = elem_key;
  H->key_equal = key_equal;
  H->key_hash = key_hash;
  H->elem_free = elem_free;

  ENSURES(is_ht(H));
  return H;
}

/* ht_lookup(H,k) returns NULL if no element with key k exists */
ht_elem ht_lookup(ht H, ht_key k)
{
  REQUIRES(is_ht(H));

  size_t i = keyhash(H, k) % H->capacity;

  chain* p = H->table[i];
  while (p != NULL) {
    ASSERT(is_chain(H, p, i, NULL));
    if (keyequal(H, elemkey(H, p->data), k)) {
      return p->data;
    } else {
      p = p->next;
    }
  }

  /* not in chain */
  return NULL;
}

static void ht_resize(ht H, size_t new_capacity)
{
  REQUIRES(is_ht(H));
  REQUIRES(new_capacity > 0);

  chain **old_table = H->table;
  chain **new_table = xcalloc(new_capacity, sizeof(chain*));
  /* new_table is initialized to all NULL */
  for (size_t i = 0; i < H->capacity; i++) {
    chain *p = old_table[i];
    while (p != NULL) {
      ASSERT(is_chain(H, p, i, NULL));
      chain *q = p->next;      /* save p->next */
      ht_elem e = p->data;
      size_t h = keyhash(H, elemkey(H, e)) % new_capacity;
      p->next = new_table[h];
      new_table[h] = p;
      p = q;
    }
  }
  free(old_table);

  /* change ht H in place */
  H->capacity = new_capacity;
  H->table = new_table;

  ENSURES(is_ht(H));
  ENSURES(H->capacity == new_capacity);
  return;
}

ht_elem ht_insert(ht H, ht_elem e) {
  REQUIRES(is_ht(H));
  REQUIRES(e != NULL);

  ht_key k = elemkey(H, e);
  size_t i = keyhash(H, k) % H->capacity;

  chain *p = H->table[i];
  while (p != NULL) {
    ASSERT(is_chain(H, p, i, NULL));
    ASSERT(p->data != NULL);
    if (keyequal(H, elemkey(H, p->data), k)) {
      /* overwrite existing element and return it */
      ht_elem tmp = p->data;
      p->data = e;
      
      ENSURES(is_ht(H));
      ENSURES(ht_lookup(H, elemkey(H, e)) != NULL);
      return tmp;
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

  /* resize hash table if load factor would be > 1, up to UINT_MAX */
  if (H->size > H->capacity && H->capacity < UINT_MAX/2) {
    /* load factor > 1 */
    ht_resize(H, 2*H->capacity);
  }

  ENSURES(is_ht(H));
  ENSURES(ht_lookup(H, elemkey(H, e)) != NULL);

  /* no existing element with given key: return NULL */
  return NULL;
}

static void chain_free(chain *p, void (*elem_free)(ht_elem e)) {
  while (p != NULL) {
    ASSERT(p->data != NULL);

    if (elem_free != NULL) {
      (*elem_free)(p->data);
    }
    chain *tmp = p->next;
    free(p);
    p = tmp;
  }
  return;
}

void ht_free(ht H) {
  for (size_t i = 0; i < H->capacity; i++) {
    if (H->table[i] != NULL) {
      chain_free(H->table[i], H->elem_free);
    }
  }
  free(H->table);
  free(H);
}

