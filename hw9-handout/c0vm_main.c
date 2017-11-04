/* C0VM, main file
 * 15-122, Fall 2010
 * William Lovas, Tom Cortina, Frank Pfenning
 *
 * Performs some OS compatibility checks before
 * running the VM.
 */
#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include "lib/c0vm.h"

/* for the args library */
int c0_argc;
char **c0_argv;

/* fail-fast file function wrappers */
FILE *xfopen(const char *filename, const char *mode, char *error) {
  FILE *f = fopen(filename, mode);
  if (f == NULL) {
    perror(error);
    exit(EXIT_FAILURE);
  }
  return f;
}

void xfwrite(const void *ptr, size_t size, size_t nitems, FILE *stream,
         char *error) {
  if (fwrite(ptr, size, nitems, stream) < nitems) {
    perror(error);
    exit(EXIT_FAILURE);
  }
}

void xfclose(FILE *stream, char *error) {
  if (fclose(stream) != 0) {
    perror(error);
    exit(EXIT_FAILURE);
  }
}

int main(int argc, char **argv) {
  if (argc < 2) {
    fprintf(stderr, "usage: %s <bc0_file> [args...]\n", argv[0]);
    exit(1);
  }

  /* test for two's complement */
  if (~(-1) != 0) {
    fprintf(stderr, "Error: not a two's complement machine\n");
    exit(1);
  }

  /* test representation sizes */
  if (sizeof(int) != 4) {
    fprintf(stderr, "Error: sizeof(int) == %zd != 4\n", sizeof(int));
    exit(1);
  }

  if (CHAR_BIT != 8) {
    fprintf(stderr, "Error: CHAR_BITS == %d != 8\n", CHAR_BIT);
    exit(1);
  }

  /* test of sign-extending shift */
  if ((int)(-1) >> 31 != -1) {
    fprintf(stderr, "Error: right shift does not sign-extend\n");
    exit(1);
  }

  /* test that casting preserves identity for a few crucial values */
  if ( INT(VAL(INT_MIN)) != INT_MIN
    || INT(VAL(INT_MAX)) != INT_MAX
    || INT(VAL(-1)) != -1
    || INT(VAL(0)) != 0
    || INT(VAL(1)) != 1 ) {
    fprintf(stderr, "Error: casting between int and void * loses information\n");
    exit(1);
  }

  /* for the args library -- skip the binary name */
  c0_argc = argc - 1;
  c0_argv = argv + 1;

  char *filename = getenv("C0_RESULT_FILE");

  /* initialize the runtime -- possibly initializing the GC */
  /* commented out Fall 2013, since we link against bare runtime only
   * and the bare runtime doesn't do anything at runtime init - rjs */
  // c0_runtime_init();

  struct bc0_file *bc0 = read_program(argv[1]);

  if (filename == NULL) {
    int result = execute(bc0);
    printf("%d\n", result);
  } else {
    FILE *f = xfopen(filename, "w", "Couldn't open $C0_RESULT_FILE");
    xfwrite("\0", 1, 1, f, "Couldn't write to $C0_RESULT_FILE");
    int result = execute(bc0);
    printf("Result = %d\n", result);
    xfwrite(&result, sizeof(int), 1, f, "Couldn't write to $C0_RESULT_FILE");
    xfclose(f, "Couldn't close $C0_RESULT_FILE");
  }

  free_program(bc0);
  return 0;
}
