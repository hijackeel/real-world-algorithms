#include "1.2-stock-span-problem-with-stack-lib.h"
#include "1.1-array-based-stack-lib.h"

void stock_span (int *quotes, size_t *spans, size_t length)
{
  spans[0] = 1;
  stack s = stack_create(length);
  stack_push(&s, 0);

  for (size_t i=1; i<length; i++)
  {
    while (!stack_empty(&s) && quotes[stack_top(&s)] <= quotes[i])
    {
      stack_pop(&s);
    }
    if (stack_empty(&s))
    {
      spans[i] = i+1;
    }
    else
    {
      spans[i] = i - stack_top(&s);
    }
    stack_push(&s, i);
  }

  stack_destroy(&s);
}
