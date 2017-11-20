/* 
 * Hash tables interface
 *
 * 15-122 Principles of Imperative Computation */

#include <stdlib.h>
#include <stdbool.h>

#ifndef _HASHTABLE_H_
#define _HASHTABLE_H_

typedef void *ht_elem; // NULL vs. non-NULL is significant
typedef void *ht_key;  // NULL vs. non-NULL is not significant

typedef struct ht_header* ht;

ht ht_new(size_t capacity,                         // Must be > 0
          ht_key (*elem_key)(ht_elem e),           // Must not be NULL
          bool (*key_equal)(ht_key k1, ht_key k2), // Must not be NULL
          size_t (*key_hash)(ht_key k),            // Must not be NULL
          void (*elem_free)(ht_elem e));           // May be NULL

/* ht_insert(H,e) returns kicked-out element with key of e, if it exists */
ht_elem ht_insert(ht H, ht_elem e);

/* ht_lookup(H,k) returns NULL if no element with key k exists */
ht_elem ht_lookup(ht H, ht_key k);

void ht_free(ht H);

#endif