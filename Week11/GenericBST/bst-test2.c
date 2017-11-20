/* Testing binary search trees
 * 15-122 Principles of Imperative Computation, Fall 2010
 * Frank Pfenning
 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdint.h>
#include <assert.h>
#include "lib/xalloc.h"
#include "lib/contracts.h"
#include "bst.h"
#include "bst-client.h"

/******************************/
/* Client-side implementation */
/******************************/
struct count {
  int id;                   /* key */
  int count;                /* data = count */
};

int key_compare(int x, int y) {
  if (x > y) return 1;
  if (x < y) return -1;
  return 0;
}

int int_compare(key k1, key k2) {
  intptr_t x = (intptr_t) k1;
  intptr_t y = (intptr_t) k2;
  if (x > y) return 1;
  if (x < y) return -1;
  return 0;
}

void int_free(elem e) {
  free(e);
}

key int_key(elem e) {
    return e;
}

int elem_key(struct count *c) {
  REQUIRES(c != NULL);
  return c->id;
}

void elem_free(struct count *c) {
  free(c);
  return;
}

elem elem_fromint(int n) {
  return (void*) (intptr_t) n;
}

int main() {
  bst B = bst_new(&int_compare, &int_key, &int_free);
  
  intptr_t A1[10] = { 5, 3, 6, 2, 7, 1, 8, 4, 10, 9 };
  bst_insert(B, (elem) A1[0]);
  intptr_t x = (intptr_t) bst_lookup(B, (void*)(intptr_t) 5);
  printf("%ld\n", x);
  
  bst_free(B);
  printf("Tests passed!\n");
  return 0;
}
