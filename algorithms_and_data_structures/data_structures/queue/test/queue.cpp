#include "gtest/gtest.h"

extern "C" {
#include "queue.h"
}

/*
  Tests if the insert function can insert an item correctly in the queue.
*/
TEST(queue, enqueue) {
  int queue_capacity = 5;
  Queue *queue = __queue__(queue_capacity);

  enqueue(queue, 1);

  ASSERT_EQ(queue->items[queue->rear], 1);
  ASSERT_EQ(queue->front, 0);
  ASSERT_EQ(queue->rear, 0);
}

/*
  Tests if the queue_is_full function can detect a queue is full, i.e. there
  were inserted a number of elements equal its capacity.
*/
TEST(queue, queue_is_full) {
  int queue_capacity = 5;
  Queue *queue = __queue__(queue_capacity);

  for (int i = 0; i < queue_capacity; i++) {
    enqueue(queue, 1);
  }

  ASSERT_TRUE(queue_is_full(queue));
}

/*
  Tests if the queue_is_full function can detect a queue is not full, i.e. there
  were inserted less elements than its capacity.
*/
TEST(queue, queue_is_not_full) {
  int queue_capacity = 5;
  Queue *queue = __queue__(queue_capacity);

  enqueue(queue, 1);

  ASSERT_FALSE(queue_is_full(queue));
}

/*
  Tests if the insert function can remove an item correctly from the queue.
*/
TEST(queue, dequeue) {
  int queue_capacity = 5;
  Queue *queue = __queue__(queue_capacity);

  enqueue(queue, 1);

  ASSERT_EQ(dequeue(queue), 1);
  ASSERT_EQ(queue->front, 1);
  ASSERT_EQ(queue->rear, 0);
}

/*
  Tests if the queue_is_empty function can detect a queue is empty, i.e. there
  is no elements in a queue.
*/
TEST(queue, queue_is_empty) {
  int queue_capacity = 5;
  Queue *queue = __queue__(queue_capacity);

  ASSERT_TRUE(queue_is_empty(queue));
}

/*
  Tests if the queue_is_empty function can detect a queue is not empty, i.e.
  there is elements in a queue.
*/
TEST(queue, queue_is_not_empty) {
  int queue_capacity = 5;
  Queue *queue = __queue__(queue_capacity);

  enqueue(queue, 1);

  ASSERT_FALSE(queue_is_empty(queue));
}

/* Test if the enqueue_and_test function can insert an element in a queue.*/
TEST(queue, enqueue_and_test) {
  int queue_capacity = 5;
  bool queue_overflow = false;
  Queue *queue = __queue__(queue_capacity);

  for (int i = 0; i < queue_capacity; i++) {
    enqueue_and_test(queue, i, &queue_overflow);
  }

  ASSERT_FALSE(queue_overflow);
  ASSERT_EQ(queue->items[queue->rear], queue_capacity - 1);
  ASSERT_EQ(queue->front, 0);
  ASSERT_EQ(queue->rear, queue_capacity - 1);
}

/* Test if the enqueue_and_test function can detect a possible overflow when
 * trying to insert an element in a queue.*/
TEST(queue, enqueue_and_test_overflow) {
  int queue_capacity = 5;
  bool queue_overflow = false;
  Queue *queue = __queue__(queue_capacity);

  for (int i = 0; i <= queue_capacity; i++) {
    enqueue_and_test(queue, i, &queue_overflow);
  }

  ASSERT_TRUE(queue_overflow);
}

/* Test if the enqueue_and_test function can remove an element in a queue.*/
TEST(queue, dequeue_and_test) {
  int queue_capacity = 5;
  bool queue_overflow = false, queue_underflow = false;
  Queue *queue = __queue__(queue_capacity);

  enqueue_and_test(queue, 1, &queue_overflow);

  ASSERT_EQ(dequeue_and_test(queue, &queue_underflow), 1);
  ASSERT_FALSE(queue_underflow);
  ASSERT_EQ(queue->front, 1);
  ASSERT_EQ(queue->rear, 0);
}

/* Test if the enqueue_and_test function can detect and underflow while trying
 * to remove an element from an empty queue.*/
TEST(queue, dequeue_and_test_underflow) {
  int queue_capacity = 5;
  bool queue_underflow = false;
  Queue *queue = __queue__(queue_capacity);

  dequeue_and_test(queue, &queue_underflow);

  ASSERT_TRUE(queue_underflow);
}