/* Testing stacks
 *
 * 15-122 Principles of Imperative Computation, Spring 2013
 * Frank Pfenning
 */

#include <stdio.h>
#include <string.h>
#include "contracts.h"
#include "stacks.h"

/* printstack(S, k) prints the top k elements
 * of the stack, and '...' if there are more.
 * Rightmost element is top of stack.
 */
void printstack(stack S, int k)
//@requires k >= 0;
{
  stack T = stack_new();
  while (!stack_empty(S) && k > 0)
    //@loop_invariant k >= 0;
    {
    push(T, pop(S));
    k--;
    }
  if (!stack_empty(S))
    printf("... ");
  while (!stack_empty(T)) {
    char *x = pop(T);
    printf("%s ", x);
    push(S, x);
  }
  /* at this point T's header will become unreachable */
  return;
}

int main() {
  stack S = stack_new();
  push(S, "a");
  push(S, "b");
  push(S, "c");
  push(S, "d");
  printstack(S, 3); printf("\n");
  assert(strcmp(pop(S), "d") == 0);
  assert(strcmp(pop(S), "c") == 0);
  assert(strcmp(pop(S), "b") == 0);
  assert(strcmp(pop(S), "a") == 0);
  assert(stack_empty(S));
  printf("All tests passed!\n");
  return 0;
}
