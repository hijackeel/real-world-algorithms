#include "2.2-array-queue-lib.h"
#include <stdlib.h>

queue queue_create(size_t max)
// Create an empty queue that can hold max number of items.
{
  return (queue){.mem=malloc(max * sizeof(uint32_t)), .max=max,
    .count=0, .head=0, .tail=max-1};
}

void queue_destroy(queue *q)
// Free queue q's memory and set all struct elements to zero.
{
  free(q->mem); q->mem = NULL; q->max = q->count = q->head = q->tail = 0;
}

int queue_empty(queue *q)
// Return TRUE if queue q is empty.
// Return FALSE if queue q is not empty.
{
  return q->count == 0;
}

int queue_full(queue *q)
// Return TRUE if queue q is full.
// Return FALSE if queue q is not full.
{
  return q->count == q->max;
}

int enqueue(queue *q, uint32_t i)
// Add item i to the tail of queue q.
// Return QUEUE_FULL (non-zero) if queue is full.
{
  if (queue_full(q))
  {
    return QUEUE_FULL;
  }
  else
  {
    q->tail++;
    q->tail %= q->max;
    q->mem[q->tail] = i;
    q->count++;
    return 0;
  }
}

int dequeue(queue *q, uint32_t *i)
// Remove the item at the head of the queue and store it at i.
// Return QUEUE_EMPTY (non-zero) if queue is empty.
{
  if (queue_empty(q))
  {
    return QUEUE_EMPTY;
  }
  else
  {
    *i = q->mem[q->head];
    q->head++;
    q->head %= q->max;
    q->count--;
    return 0;
  }
}
