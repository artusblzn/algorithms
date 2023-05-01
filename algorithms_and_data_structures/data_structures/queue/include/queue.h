#ifndef QUEUE_H
#define QUEUE_H

#include <stdbool.h>

typedef struct queue {
  int *items;
  int front, rear, capacity;
} Queue;

Queue *__queue__(int queue_capacity);
void enqueue(Queue *queue, int item);
bool queue_is_full(Queue *queue);
int dequeue(Queue *queue);
bool queue_is_empty(Queue *queue);
void enqueue_and_test(Queue *queue, int item, bool *queue_overflow);
int dequeue_and_test(Queue *queue, bool *queue_underflow);

#endif