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
  queue->num_items = 0;

  return queue;
}

void enqueue(Queue *queue, int item) {
  queue->num_items++;
  queue->rear = (queue->rear + 1) % queue->capacity;
  queue->items[queue->rear] = item;
}

bool queue_is_full(Queue *queue) { return queue->num_items >= queue->capacity; }

int dequeue(Queue *queue) {
  int old_front = queue->front;

  queue->front = (queue->front + 1) % queue->capacity;
  queue->num_items--;
  return queue->items[old_front];
}

bool queue_is_empty(Queue *queue) { return queue->num_items == 0; }

void enqueue_and_test(Queue *queue, int item, bool *queue_overflow) {
  *queue_overflow = queue_is_full(queue);
  if (*queue_overflow) {
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