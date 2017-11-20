/*
 * Polymorphic selection sort in C
 *
 * Principles of Imperative Computation
 * Frank Pfenning, Penny Anderson
 */

#include <stdlib.h>
#include <limits.h>

#include "lib/contracts.h"
#include "sort.h"

size_t min_index(elem *A, size_t lower, size_t upper, compare_fun compare) {
  REQUIRES( lower < upper );    // and upper <= length of array A

  size_t m = lower;
  elem min = A[lower];
  for (size_t i = lower+1; i < upper; i++) {
    ASSERT( lower < i && i <= upper );
    ASSERT( A[m] == min );
    if ( (*compare)(A[i], min) < 0 ) {
      /* The compiler would let us write:
	 if ( compare(A[i], min) < 0 ) {
      */
      m = i;
      min = A[i];
    }
  }
  ENSURES( lower <= m && m < upper);
  return m;
}

static inline void swap(elem *A, size_t i, size_t j) {
  elem temp = A[i];
  A[i] = A[j];
  A[j] = temp;
}

void sort(elem *A, size_t lower, size_t upper, compare_fun compare) {
  REQUIRES( lower <= upper ); // and  upper <= length of array A;
    for (size_t i = lower; i < upper; i++) {
      ASSERT( lower <= i && i <= upper );
      size_t m = min_index(A, i, upper, compare);
      swap(A, i, m);
    }
  return;
}
