/* 
 * Stacks 
 *
 * 15-122 Principles of Imperative Computation */

#include <stdbool.h>

#ifndef _STACKS_H_
#define _STACKS_H_

typedef void *stack_elem;
typedef struct stack_header* stack;
bool stack_empty(stack S);           /* O(1) */
stack stack_new();                   /* O(1) */
void push(stack S, stack_elem e);    /* O(1) */
stack_elem pop(stack S);             /* O(1) */
void stack_free(stack S);    /* O(1), S must be empty! */

#endif
