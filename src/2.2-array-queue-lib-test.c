#include "2.2-array-queue-lib.h"
#include "run_test.h"
#include <assert.h>

static void test_queue()
{
  uint32_t dq = 42;

  // [ | | ]
  //  ht
  queue q = queue_create(3);
  assert(queue_empty(&q));
  assert(!queue_full(&q));
  assert(dequeue(&q,&dq) == QUEUE_EMPTY);
  assert(dq == 42);

  // [a| | ]
  //  ht
  assert(!enqueue(&q,'a'));
  assert(!queue_empty(&q));
  assert(!queue_full(&q));

  // [a|b| ]
  //  h t
  assert(!enqueue(&q,'b'));
  assert(!queue_empty(&q));
  assert(!queue_full(&q));

  // [a|b|c]
  //  h   t
  assert(!enqueue(&q,'c'));
  assert(!queue_empty(&q));
  assert(queue_full(&q));
  assert(enqueue(&q,'d') == QUEUE_FULL);

  // [ |b|c]
  //    h t
  assert(!dequeue(&q,&dq));
  assert(dq == 'a');
  assert(!queue_empty(&q));
  assert(!queue_full(&q));

  // [d|b|c]
  //  t h
  assert(!enqueue(&q,'d'));
  assert(!queue_empty(&q));
  assert(queue_full(&q));
  assert(enqueue(&q,'e') == QUEUE_FULL);

  // [d| |c]
  //  t   h
  assert(!dequeue(&q,&dq));
  assert(dq == 'b');
  assert(!queue_empty(&q));
  assert(!queue_full(&q));

  // [d| | ]
  //  ht
  assert(!dequeue(&q,&dq));
  assert(dq == 'c');
  assert(!queue_empty(&q));
  assert(!queue_full(&q));

  // [d|e| ]
  //  h t
  assert(!enqueue(&q,'e'));
  assert(!queue_empty(&q));
  assert(!queue_full(&q));

  // [ |e| ]
  //    ht
  assert(!dequeue(&q,&dq));
  assert(dq == 'd');
  assert(!queue_empty(&q));
  assert(!queue_full(&q));

  // [ | | ]
  //    ht
  assert(!dequeue(&q,&dq));
  assert(dq == 'e');
  assert(queue_empty(&q));
  assert(!queue_full(&q));
  assert(dequeue(&q,&dq) == QUEUE_EMPTY);
  assert(dq == 'e');

  // [ |f| ]
  //    ht
  assert(!enqueue(&q,'f'));
  assert(!queue_empty(&q));
  assert(!queue_full(&q));

  queue_destroy(&q);
}

int main()
{
  run_test(test_queue);
  printf("\nOK\n\n");
}
