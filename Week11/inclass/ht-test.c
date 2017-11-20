/* Testing hash tables
 * 15-122 Principles of Imperative Computation
 * Frank Pfenning
 */

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <assert.h>

#include "lib/xalloc.h"
#include "lib/contracts.h"

#include "ht.h"

/* elements */
struct wc {
  char *word;			/* key */
  int count;			/* information */
};

/* key comparison */
bool word_equal(ht_key w1, ht_key w2) {
  return strcmp((char*)w1,(char*)w2) == 0;		/* different from C0! */
}

/* extracting keys from elements */
ht_key wc_key(ht_elem e) {
  REQUIRES(e != NULL);
  struct wc *wcount = (struct wc*)e;
  return wcount->word;
}

/* hash function */
/* uses pseudo-random number generation */
/* converted to use unsigned int in C */
int word_hash(ht_key s, int m) {
  REQUIRES(m > 1);
  unsigned int a = 1664525;
  unsigned int b = 1013904223;	       /* inlined random number generator */
  unsigned int r = 0xdeadbeef;	       /* initial seed */
  int len = strlen(s);		       /* different from C0! */
  unsigned int h = 0;		       /* empty string maps to 0 */
  for (int i = 0; i < len; i++)
    {
      h = r*h + ((char*)s)[i];	 /* mod 2^32 */
      r = r*a + b;	 /* mod 2^32, linear congruential random no */
    }
  h = h % m;			/* reduce to range */
  //@assert -m < (int)h && (int)h < m;
  int hx = (int)h;
  if (hx < 0) h += m;	/* make positive, if necessary */
  ENSURES(0 <= hx && hx < m);
  return hx;
}

void wc_free(ht_elem e) {
  struct wc *wcount = (struct wc*)e;
  free(wcount->word);
  free(e);
}

/* max number of character in int: 10 + sign + '\0' = 12 */
#define MAXINT_CHARS 12

char* itoa(int n) {
  char* buf = xmalloc(MAXINT_CHARS * sizeof(char));
  snprintf(buf, MAXINT_CHARS, "%d", n);
  return buf;
}

int main () {
  int n = (1<<10)+1; // start with 1<<10 for timing; 1<<9 for -d
  int num_tests = 2; // start with 1000 for timing; 10 for -d

  /* different from C0! */
  printf("Testing array of size %d with %d values, %d times\n",
	 n/5, n, num_tests);
  for (int j = 0; j < num_tests; j++) {
    ht H = ht_new(n/5, &wc_key, &word_equal, &word_hash, &wc_free);
    for (int i = 0; i < n; i++) {
      struct wc *e = xmalloc(sizeof(struct wc));
      e->word = itoa(j*n+i);	/* diff from C0 */
      e->count = j*n+i;
      ht_insert(H, e);
    }
    for (int i = 0; i < n; i++) {
      char* s = itoa(j*n+i);
      struct wc *wcount = (struct wc*)(ht_lookup(H, s));
      assert(wcount->count == j*n+i); /* "missed existing element" */
      free(s);
    }
    for (int i = 0; i < n; i++) {
      char* s = itoa((j+1)*n+i);
      assert(ht_lookup(H, s) == NULL); /* "found nonexistent element" */
      free(s);
    }
    ht_free(H);
  }
  printf("All tests passed!\n");
  return 0;
}
