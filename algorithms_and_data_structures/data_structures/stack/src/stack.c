#include "stack.h"
#include <stdlib.h>

Stack *__stack__(int stack_capacity) {
  Stack *stack;

  if (!(stack = (Stack *)malloc(sizeof(Stack)))) {
    exit(1);
  }

  if (!(stack->items = (int *)malloc(sizeof(int)))) {
    exit(1);
  }
  stack->top = -1;

  stack->capacity = stack_capacity;

  return stack;
}

void push(Stack *stack, int item) { stack->items[++stack->top] = item; }

int stack_is_full(Stack *stack) { return (stack->top >= stack->capacity - 1); }

int pop(Stack *stack) { return stack->items[stack->top--]; }

int stack_is_empty(Stack *stack) { return stack->top < 0; }

void push_and_test(Stack *stack, int item, int *stack_overflow) {
  *stack_overflow = stack_is_full(stack);
  if (*stack_overflow)
    return;
  push(stack, item);
}

int pop_and_test(Stack *stack, int *stack_underflow) {
  *stack_underflow = stack_is_empty(stack);
  if (!*stack_underflow)
    return stack->items[stack->top--];
  return -1;
}