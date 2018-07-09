#include <stdint.h>
#include <stddef.h>

typedef enum
{
  QUEUE_FULL = 1,
  QUEUE_EMPTY = 2
} queue_error;

typedef struct
{
  uint32_t *mem;
  size_t max;
  size_t count;
  size_t head;
  size_t tail;
} queue;

queue queue_create(size_t max);
// Create an empty queue that can hold max number of items.

void queue_destroy(queue *q);
// Free queue q's memory and set all struct elements to zero.

int queue_empty(queue *q);
// Return TRUE if queue q is empty.
// Return FALSE if queue q is not empty.

int queue_full(queue *q);
// Return TRUE if queue q is full.
// Return FALSE if queue q is not full.

int enqueue(queue *q, uint32_t i);
// Add item i to the tail of queue q.
// Return QUEUE_FULL (non-zero) if queue is full.

int dequeue(queue *q, uint32_t *i);
// Remove the item at the head of the queue and store it at i.
// Return QUEUE_EMPTY (non-zero) if queue is empty.
