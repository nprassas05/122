#include <stdio.h>
#include "strbuf.h"
#include <assert.h>

void test_strbuf()
{
  struct strbuf* sb = strbuf_new(16);
  strbuf_add(sb, "hello", 5);
  char *b = strbuf_str(sb);
  printf("%s\n", b);
  strbuf_addstr(sb, " world, my name is sally with the socks");
  free(b);
  b = strbuf_str(sb);
  printf("%s\n", b);
  strbuf_addstr(sb, "\nyet another line has been added to the buffer");
  free(b);
  b = strbuf_dealloc(sb);
  printf("%s\n", b);
  free(b);
}

int main()
{
  test_strbuf();
  return 0;
}
