#include "gtest/gtest.h"

extern "C" {
#include "stack.h"
}

/*
  Tests if the push function is correctly pushing elements to the stack.
*/
TEST(stack, push) {
  int stack_capacity = 5;
  Stack *stack = __stack__(stack_capacity);

  push(stack, 1);

  ASSERT_EQ(stack->items[stack->top], 1);
  ASSERT_EQ(stack->top, 0);
}

/*
  Tests if the stack_is_full function can detect if the stack has more elements
  than its capacity.
*/
TEST(stack, stack_is_full) {
  int stack_capacity = 5;
  Stack *stack = __stack__(stack_capacity);

  for (int i = 0; i < stack_capacity; i++) {
    push(stack, i);
  }

  ASSERT_TRUE(stack_is_full(stack));
}

/*
  Tests if the stack_is_full function can detect if the stack has less elements
  than its capacity.
*/
TEST(stack, stack_is_not_full) {
  int stack_capacity = 5;
  Stack *stack = __stack__(stack_capacity);

  push(stack, 1);

  ASSERT_FALSE(stack_is_full(stack));
}

/*
  Tests if the pop function is correctly pushing elements to the stack.
*/
TEST(stack, pop) {
  int stack_capacity = 5;
  Stack *stack = __stack__(stack_capacity);

  push(stack, 1);

  ASSERT_EQ(pop(stack), 1);
  ASSERT_EQ(stack->top, -1);
}

/*
  Tests if the stack_is_empty function can detect if the stack has no elements.
*/
TEST(stack, stack_is_empty) {
  int stack_capacity = 5;
  Stack *stack = __stack__(stack_capacity);

  for (int i = 0; i < stack_capacity; i++) {
    push(stack, i);
  }

  for (int i = 0; i < stack_capacity; i++) {
    pop(stack);
  }

  ASSERT_TRUE(stack_is_empty(stack));
}

/*
  Tests if the stack_is_empty function can detect if the stack has elements.
*/
TEST(stack, stack_is_not_empty) {
  int stack_capacity = 5;
  Stack *stack = __stack__(stack_capacity);

  push(stack, 1);

  ASSERT_FALSE(stack_is_empty(stack));
}

/*
  Tests if the push_and_test function can push an element to a non-full stack.
*/
TEST(stack, push_and_test) {
  int stack_capacity = 5;
  bool stack_overflow = false;
  Stack *stack = __stack__(stack_capacity);

  push_and_test(stack, 1, &stack_overflow);

  ASSERT_FALSE(stack_overflow);
  ASSERT_EQ(stack->items[stack->top], 1);
  ASSERT_EQ(stack->top, 0);
}

/*
  Tests if the push_and_test function can detect if there is a stack overflow,
  i.e. tried to push more elements than the stack's capacity.
*/
TEST(stack, push_and_test_overflow) {
  int stack_capacity = 5;
  bool stack_overflow = false;
  Stack *stack = __stack__(stack_capacity);

  for (int i = 0; i <= stack_capacity; i++) {
    push_and_test(stack, i, &stack_overflow);
  }
  ASSERT_TRUE(stack_overflow);
}

/*
  Tests if the pop_and_test function can pop an element to a non-empty stack.
*/
TEST(stack, pop_and_test) {
  int stack_capacity = 5;
  bool stack_overflow, stack_underflow = false;
  Stack *stack = __stack__(stack_capacity);

  push_and_test(stack, 1, &stack_overflow);

  ASSERT_EQ(pop_and_test(stack, &stack_underflow), 1);
  ASSERT_EQ(stack->top, -1);
  ASSERT_FALSE(stack_underflow);
}

/*
  Tests if the pop_and_test function can detect if there is a stack underflow,
  i.e. tried to pop an element from an empty stack.
*/
TEST(stack, pop_and_test_underflow) {
  int stack_capacity = 5;
  bool stack_underflow = false;
  Stack *stack = __stack__(stack_capacity);

  pop_and_test(stack, &stack_underflow);

  ASSERT_TRUE(stack_underflow);
}