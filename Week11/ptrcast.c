/*
 * Pointer casting
 * 
 * 15-122 Principles of Imperative Computation */

#include <assert.h>
#include <stdio.h>
#include "lib/xalloc.h"
#include <stdint.h>
#include <string.h>

int incr(int x) { return x+1; }

int main(int argc, char **argv) {

  if (argc != 2) {
    printf("Not enough arguments!\n");
    return 1;
  }

  int len = strlen(argv[1]);
  void *vp = xcalloc(len+1, sizeof(char));
  char *cp = (char*)vp;
  int *ip = (int*)vp;
  (void) ip;

  strcpy(cp, argv[1]); 
  printf("About %p...\n", vp);
  printf("...same as %p...\n", (void*) cp);
  printf("...same as %p...\n", (void*) ip);
  printf("...I'm looking at \"%s\"\n", cp);
  printf("...but I'm seeing %#10x\n", *ip);
  return 0;
}  

