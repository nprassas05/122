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


static inline void swap(elem *A, size_t i, size_t j) {
  elem temp = A[i];
  A[i] = A[j];
  A[j] = temp;
}

/************** C0 code for selection sort ********************
 *
 *                                to be converted!
 *
 *  int index --> size_t
 *  int element --> elem
 *  arrays --> pointers
 *  arithmetic compare --> client supplied function pointer
 *  contracts
 ***************************************************************/

size_t min_index(elem* A, size_t lower, size_t upper, compare_fun cmp)
//@requires 0 <= lower && lower < upper && upper <= \length(A);
//@ensures lower <= \result && \result < upper;
//@ensures le_seg(A[\result], A, lower, upper);
{
  size_t m = lower;
  elem min = A[lower];
  for (size_t i = lower+1; i < upper; i++)
    //@loop_invariant lower < i && i <= upper;
    //@loop_invariant le_seg(min, A, lower, i);
    //@loop_invariant A[m] == min;
    //    if ( A[i] < min) 
    if ( (*cmp)(A[i], min) < 0  ) {
      m = i;
      min = A[i];
    }
  return m;
}

void sort(elem* A, size_t lower, size_t upper, compare_fun cmp)
//@requires 0 <= lower && lower <= upper && upper <= \length(A);
//@ensures is_sorted(A, lower, upper);
{
  for (size_t i = lower; i < upper; i++)
    //@loop_invariant lower <= i && i <= upper;
    //@loop_invariant is_sorted(A, lower, i);
    //@loop_invariant le_segs(A, lower, i, i, upper);
    {
      size_t m = min_index(A, i, upper, cmp);
      //@assert le_seg(A[m], A, i, upper);
      swap(A, i, m);
    }
  return;
}
