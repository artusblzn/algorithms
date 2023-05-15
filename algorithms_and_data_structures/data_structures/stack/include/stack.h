#ifndef STACK_H
#define STACK_H

#include <stdbool.h>

typedef struct stack {
  int *items;
  int top;
  int capacity;
} Stack;

Stack *__stack__(int stack_capacity);
void push(Stack *stack, int item);
bool stack_is_full(Stack *stack);
int pop(Stack *stack);
bool stack_is_empty(Stack *stack);
void push_and_test(Stack *stack, int item, bool *stack_overflow);
int pop_and_test(Stack *stack, bool *stack_underflow);

#endif