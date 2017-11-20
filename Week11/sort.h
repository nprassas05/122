/* Sorting
 * 15-122 Principles of Imperative Computation, Summer One 2013
 * Penny Anderson
 */

#include <stdlib.h>
#include <stdint.h>

#ifndef _SORT_EXAMPLE_H_
#define _SORT_EXAMPLE_H_

typedef void* elem;
typedef int (*compare_fun) (void  *e1, void *e2);

void sort(elem* A, size_t lower, size_t upper, compare_fun compare);

#endif
