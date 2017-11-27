#include "lib/ba-ht.h"
#include "lib/ht.h"
#include <stdbool.h>
#include <assert.h>
#include <stdlib.h>

ht_key elem_key(ht_elem e) {
    assert(e != NULL);
    ba_ht_elem B = (ba_ht_elem) e;
    return &B->ba;
    //return &((ba_ht_elem)e)->ba; // &e->ba ????
}

bool key_equal(ht_key k1, ht_key k2) {
    ba_ht_key bk1 = (ba_ht_key) k1;
    ba_ht_key bk2 = (ba_ht_key) k2;

    return (*bk1) == (*bk2);
}

size_t key_hash(ht_key B) {
    return (size_t) *((ba_ht_key) B);
}

void elem_free(ht_elem e) {
    free(e);
}

ht ba_ht_new(size_t capacity) {
    ht ba_ht = ht_new(capacity,
                      &elem_key,
                      &key_equal,
                      &key_hash,
                      &elem_free);
    return ba_ht;
}

/* ht_insert(H,e) returns 
 * kicked-out element with key of e, if it exists and 
 * NULL otherwise
 */
ba_ht_elem ba_ht_insert(ht H, ba_ht_elem e) {
	return ht_insert(H, e);
}

/* ht_lookup(H,k) returns 
 * NULL if no element with key k exists and
 * the element associated with the key otherwise.
 * NULL keys are invalid in ba_hts
 */
ba_ht_elem ba_ht_lookup(ht H, ba_ht_key k) {
	return ht_lookup(H, k);
}

/* Frees the hash table and all of its data */
void ba_ht_free(ht H) {
	ht_free(H);
}
