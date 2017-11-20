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

int compare_ints(void *i1, void *i2) {
  intptr_t n1 =  (intptr_t) i1;
  intptr_t n2 =  (intptr_t) i2;
  return n1 < n2 ? -1 : ( n1 == n2 ? 0 : 1 );
}

int compare_strings(void *s1, void *s2) {
  return strcmp((char*)s1, (char*)s2);
}

int main() {
  intptr_t A1[10] = { 5, 3, 6, 2, 7, 1, 8, 4, 10, 9 };
  sort((elem*)A1, 0, 10, &compare_ints);
  for (size_t i = 0 ; i < 10 ; i++ )
    printf("%ld ", A1[i]);
  printf("\n");

  char *A2[10] = { "alpha", "zeta", "beta", "xi", "lambda", "mu", "nu", "psi", "pi", "phi" };
  sort((elem*)A2, 0, 10, &compare_strings);
  for (size_t i = 0 ; i < 10 ; i++ )
    printf("%s ", A2[i]);
  printf("\n");

  return 0;
}
