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
  b = strbuf_str(sb);
  printf("%s\n", b);
}

int main()
{
  test_strbuf();
  return 0;
}
