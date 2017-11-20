/* Sorting
 * 15-122 Principles of Imperative Computation, Summer One 2013
 * Penny Anderson
 */

#include <stdlib.h>
#include <stdint.h>
#include <stdio.h>
#include <string.h>

#include "lib/xalloc.h"
#include "sort.h"

/************ Client code for generic sort *******************
 *
 *  Define comparison functions for integers and strings
 *  for indexes use size_t
 *  for integer elements use intptr_t (same size as a pointer)
 *
 ***************************************************************/


int compare_ints(void *i1, void *i2) {
  intptr_t ii1 = (intptr_t) i1;
  intptr_t ii2 = (intptr_t) i2;
  return ii1 < ii2 ? -1 : ( ii1 == ii2 ? 0 : 1 );
}

int compare_strings(void *s1, void *s2) {
  return strcmp((char *) s1, (char *) s2);
}

/*
 * Sort 10 integers then 10 strings
 */

int main() {
  intptr_t A1[10] = { 5, 3, 6, 2, 7, 1, 8, 4, 10, 9 };
  sort( (elem *) A1, 0, 10, &compare_ints);
  for (size_t i = 0 ; i < 10 ; i++ ) 
    printf("%ld ", A1[i]);                                 
  printf("\n");

  char *A2[10] = { "alpha", "zeta", "beta", "xi", "lambda", "mu", "nu", "psi", "pi", "phi" };
  sort( (elem *) A2, 0, 10, &compare_strings);
  for (size_t i = 0 ; i < 10 ; i++ )
    printf("%s ", A2[i]);
  printf("\n");

  return 0;
}
