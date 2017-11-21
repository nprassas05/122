/* 
 * String Buffer Library
 *
 * 15-122 Principles of Imperative Computation
 * This version exposes the externals, requires
 * discipline from client! */

#include <string.h>
#include "lib/contracts.h"
#include "lib/xalloc.h"
#include "strbuf.h"

/*** Implementation ***/
bool is_strbuf(struct strbuf* sb)
{
  if (sb == NULL) return false;
  //if (!(string_terminated(sb->buf, sb->len + 1))) return false;
  if (!(strlen(sb->buf) == sb->len)) return false;
  return true;
}

struct strbuf* strbuf_new(size_t init_limit)
//@ensures is_strbuf(\result);
{
  struct strbuf* sb = xmalloc(sizeof(struct strbuf));
  sb->limit = init_limit;
  sb->buf = xcalloc(init_limit, sizeof(char));
  sb->len = 0;
  sb->buf[0] = '\0';
  REQUIRES(is_strbuf(sb));
  return sb;
}

char* strbuf_str(struct strbuf* sb)
//@requires is_strbuf(sb);
//@ensures is_strbuf(sb);
{
  REQUIRES(is_strbuf(sb));
  char* buffer = xcalloc(sb->len + 1, sizeof(char));
  for (int i = 0; i <= sb->len; i++) { // using <= means we'll include '\0'
    buffer[i] = sb->buf[i];
  }
  
  assert(is_strbuf(sb));
  return buffer;
}

void strbuf_add(struct strbuf* sb, char *str, size_t len)
//@requires is_strbuf(sb);
//@requires is_cstring(str, 0, len);
//@ensures is_strbuf(sb);
{
  REQUIRES(is_strbuf(sb));
  if (sb->len + len >= sb->limit)
    {
      resize(sb, (sb->limit + len) * 2);
    }
  
  for (int i = 0; i < len; i++) {
    sb->buf[sb->len + i] = str[i];
  }
  
  sb->buf[sb->len + len] = '\0';
  sb->len = sb->len + len;
  assert(is_strbuf(sb));
}

void strbuf_addstr(struct strbuf* sb, char *str)
//@requires is_strbuf(sb);
//@ensures is_strbuf(sb);
//@requires is_cstring(str, 0, \length(str));
{
  REQUIRES(is_strbuf(sb));
  strbuf_add(sb, str, strlen(str));
}

void resize(struct strbuf* sb, size_t limit)
//@requires is_strbuf(sb);
//@ensures is_strbuf(sb);
{
  REQUIRES(is_strbuf(sb));
  char* buffer = xcalloc(limit, sizeof(char));
  for (int i = 0; i <= sb->limit; i++)
    {
      buffer[i] = sb->buf[i];
    }
  
  free(sb->buf);
  sb->buf = buffer; // garbage collector takes care of the old buf in C0
  sb->limit = limit;
  ENSURES(is_strbuf(sb));
  return;
}

char *strbuf_dealloc(struct strbuf *sb)
{
  char* buffer = sb->buf;
  free(sb);
  return buffer;
}
