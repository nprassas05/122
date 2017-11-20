#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>
#include <limits.h>
#include <string.h>

#include "lib/xalloc.h"
#include "lib/contracts.h"

#include "stacks.h"

int incr(int x) { return x+1; }

int main(int argc, char **argv) {
  stack S = stack_new();
  int x = 0x4800;

  push(S, (void*) "hello");
  push(S, (void*) "there");
  push(S, (void*) &x);      // Sad and dangerous
  push(S, (void*)  "world");

  printf("pop - %s\n", (char*) pop(S));
  int *p = (int*) pop(S);
  printf("pop - %d\n", *p);
  printf("pop - %s\n", (char*) pop(S));
  printf("pop - %c\n", *(char*) pop(S));

  (void) argc;
  printf("Where is argv? %p\n", (void*) &argv);
  printf("Where is incr? %p\n", (void*) &incr);

  int (*f)(int) = &incr;
  printf("Use the function, get %d\n", (*f)(4));

  ASSERT(stack_empty(S));
  stack_free(S);
  printf("Done!\n");
  return 0;
}
