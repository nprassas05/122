/*
 * Testing hash tables (unit tests and randomized tests)
 * 
 * 15-122 Principles of Imperative Computation */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <assert.h>
#include "lib/xalloc.h"
#include "lib/contracts.h"
#include "ht.h"

/******************************/
/* Client-side implementation */
/******************************/

struct count {
  int id;                   /* key */
  int count;                /* data = count */
};

bool key_equal(ht_key k1, ht_key k2) {
  int a = *(int*)k1;
  int b = *(int*)k2;
  return a == b;
}

/* WARNING: this uses a PRNG that expects a 2^32 modulus, 
 * but size_t is likely bigger than 2^32 */
size_t key_hash(ht_key k) {
  int a = *(int*)k;
  size_t b = (size_t)(unsigned int)a; // Cast without sign extension
  size_t h = b*1664525 + 1013904223;
  return h;
}

ht_key elem_key(ht_elem x) {
  struct count *c = x; // Casts from void* 
  REQUIRES(c != NULL);
  return &c->id; // Casts to void*
}

void elem_free(ht_elem c) {
  free(c);
  return;
}

/****************/
/* Testing code */
/****************/

ht_elem elem_fromint(int k) {
  struct count *c = xmalloc(sizeof(struct count));
  c->id = k;
  c->count = k*k;
  return c;
}

ht_elem lookup(ht H, int x) {
  return ht_lookup(H, &x);
}

int main() {
  printf("Testing with Fall 2012 Lecture 1's black-box testing code\n");
  ht_elem E1 = elem_fromint(42);
  ht_elem E2 = elem_fromint(115);
  ht_elem E3 = elem_fromint(42);
  ht_elem E4 = elem_fromint(-215);
  
  ht H = ht_new(3, &elem_key, &key_equal, &key_hash, &elem_free);
  assert(H != NULL);
  assert(lookup(H, 0) == NULL);
  assert(lookup(H, 115) == NULL);
  
  free(ht_insert(H, elem_fromint(98)));
  free(ht_insert(H, elem_fromint(88)));
  free(ht_insert(H, elem_fromint(14)));
  free(ht_insert(H, elem_fromint(67)));
  free(ht_insert(H, elem_fromint(23)));
  free(ht_insert(H, elem_fromint(-12)));
  free(ht_insert(H, elem_fromint(39)));
  
  free(ht_insert(H, E1));
  assert(lookup(H, 42) == E1);
  assert(lookup(H, 115) == NULL);
  assert(lookup(H, 0) == NULL);
  
  free(ht_insert(H, E2));
  assert(lookup(H, 42) == E1);
  assert(lookup(H, 115) == E2);
  assert(lookup(H, 0) == NULL);
  
  free(ht_insert(H, E3));
  assert(lookup(H, 42) == E3);
  assert(lookup(H, 115) == E2);
  
  free(ht_insert(H, E4));
  assert(lookup(H, -215) == E4);
  assert(lookup(H, 42) == E3);

  printf("Running some sequential entries\n");
  for(int i = 0; i < 20; i = i+2) 
    free( ht_insert(H, elem_fromint(i)));

  for(int i = 0; i > -20; i = i-2)
    free(ht_insert(H, elem_fromint(i)));

  for (int i = -19; i < 20; i++) {
    if (i % 2 == 0) assert(lookup(H, i) != NULL);
    else assert(lookup(H, i) == NULL);
  }

  printf("Running some random entries\n");
  for (int i = 0; i < 5000; i++) {
    free(ht_insert(H, elem_fromint(rand())));
  }
  
  ht_free(H);

  printf("Tests passed!\n");
  return 0;
}