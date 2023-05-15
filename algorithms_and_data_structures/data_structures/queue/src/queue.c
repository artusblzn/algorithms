#include "queue.h"
#include <stdbool.h>
#include <stdlib.h>

Queue *__queue__(int queue_capacity) {
  Queue *queue;

  if (!(queue = (Queue *)malloc(sizeof(Queue)))) {
    exit(1);
  }

  if (!(queue->items = (int *)malloc(sizeof(int)))) {
    exit(1);
  }

  /* The queue is empty if the rear index is lesser than the front index. */
  queue->front = 0;
  queue->rear = -1;
  queue->capacity = queue_capacity;

  return queue;
}

void enqueue(Queue *queue, int item) { queue->items[++queue->rear] = item; }

bool queue_is_full(Queue *queue) { return queue->rear >= queue->capacity - 1; }

int dequeue(Queue *queue) { return queue->items[queue->front++]; }

bool queue_is_empty(Queue *queue) { return queue->rear < queue->front; }

void enqueue_and_test(Queue *queue, int item, bool *queue_overflow) {
  if (*queue_overflow = queue_is_full(queue)) {
    return;
  }
  enqueue(queue, item);
}

int dequeue_and_test(Queue *queue, bool *queue_underflow) {
  *queue_underflow = queue_is_empty(queue);
  if (*queue_underflow) {
    return -1;
  }
  return dequeue(queue);
}