/*
 * Interface for stacks
 *
 * 15-122 Principles of Imperative Computation */

#include <stdbool.h>

#ifndef _STACKS_H
#define _STACKS_H

typedef void *stack_elem;
typedef struct stack_header *stack;
bool stack_empty(stack S);           /* O(1) */
stack stack_new();                   /* O(1) */
void push(stack S, stack_elem e);    /* O(1) */
stack_elem pop(stack S);             /* O(1) */
size_t stack_size(stack S);          /* O(1) */

/* If the second argument is non-NULL, then  *
 * the elem_free function will be run on     *
 * every element still in the queue. If the  * 
 * second argument is NULL, the elem_free    *
 * function won't be run.                    */
void stack_free(stack S, void (*elem_free)(void* e));   /* O(n) */

#endif
