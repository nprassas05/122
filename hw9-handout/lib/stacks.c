/* Stacks
 * 15-122 Principles of Imperative Computation, Spring 2011
 * Frank Pfenning
 */

#include <stdlib.h>
#include <stdbool.h>
#include <assert.h>
#include "xalloc.h"
#include "contracts.h"
#include "stacks.h"

/* Linked lists */

typedef struct list_node list;
struct list_node {
  stack_elem data;
  list *next;
};

/* is_segment(start, end) will diverge if list is circular! */
bool is_segment(list *start, list *end, size_t size) {
  list *p = start;
  while (p != end) {
    if (p == NULL) return false;
    if (size-- == 0) return false;
    p = p->next;
  }
  return size == 0;
}

/* segement_free(start, end, data_free) will free the list
 * segment from start to end, excluding end.  It also applies
 * the data_free function to every stored element
 */
void segment_free(list *start, list *end, void (*data_free)(void* e), size_t n)
{
  REQUIRES(is_segment(start, end, n));
  (void) n;
  list *p = start;
  while (p != end) {
    ASSERT(p != NULL);
    list *tmp = p;
    p = p->next;
    if (data_free != NULL && tmp->data != NULL)
      (*data_free)(tmp->data);
    free(tmp);
  }
  return;
}


/* Stacks */ 

struct stack_header {
  list *top;
  list *bottom;
  size_t size;
};

bool is_stack (stack S) {
  if (S == NULL) return false;
  if (S->top == NULL || S->bottom == NULL) return false;
  if (!is_segment(S->top, S->bottom, S->size)) return false;
  return true;
}

bool stack_empty(stack S) {
  REQUIRES(is_stack(S));
  return S->size == 0;
}

stack stack_new() {
  stack S = xmalloc(sizeof(struct stack_header));
  list *l = xmalloc(sizeof(struct list_node));
  S->top = l;
  S->bottom = l;
  S->size = 0;
  ENSURES(is_stack(S) && stack_empty(S));
  return S;
}

void stack_free(stack S, void (*elem_free)(void* e)) {
  REQUIRES(is_stack(S));
  segment_free(S->top, S->bottom, elem_free, S->size);
  free(S->bottom);
  free(S);
  return;
}

void push(stack S, stack_elem e) {
  REQUIRES(is_stack(S));
  list *first = xmalloc(sizeof(struct list_node));
  first->data = e;
  first->next = S->top;
  S->top = first;
  S->size += 1;
  ENSURES(is_stack(S) && !stack_empty(S));
}

stack_elem pop(stack S) {
  REQUIRES(is_stack(S) && !stack_empty(S));
  assert(S != NULL && !stack_empty(S));
  stack_elem e = S->top->data;
  list *q = S->top;
  S->top = S->top->next;
  S->size -= 1;
  free(q);
  ENSURES(is_stack(S));
  return e;
}

size_t stack_size(stack S) {
  REQUIRES(is_stack(S));
  return S->size;
}
