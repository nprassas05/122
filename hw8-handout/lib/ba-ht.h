
/* 
 * Hash tables interface
 *
 * 15-122 Principles of Imperative Computation */

#include <stdlib.h>
#include <stdbool.h>

#include "bitarray.h"
#include "ht.h"

#ifndef _BITARRAY_HASHTABLE_H_
#define _BITARRAY_HASHTABLE_H_

struct ba_ht_elem_base {
    uint8_t last_move;
    bitarray ba;
};

typedef struct ba_ht_elem_base* ba_ht_elem;
typedef bitarray* ba_ht_key; // Cannot be NULL


/* IMPORTANT: Please respect the hash table interface when
 * writing your implementation of these functions!
 */

/* Creates a new hash table
 */
ht ba_ht_new(size_t capacity);


/* ht_insert(H,e) returns 
 * kicked-out element with key of e, if it exists and 
 * NULL otherwise
 */
ba_ht_elem ba_ht_insert(ht H, ba_ht_elem e);

/* ht_lookup(H,k) returns 
 * NULL if no element with key k exists and
 * the element associated with the key otherwise.
 * NULL keys are invalid in ba_hts
 */
ba_ht_elem ba_ht_lookup(ht H, ba_ht_key k);

/* Frees the hash table and all of its data
 */
void ba_ht_free(ht H);

#endif
