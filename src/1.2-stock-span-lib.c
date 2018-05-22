#include "1.2-stock-span-lib.h"
#include "1.1-array-stack-size_t-lib.h"

void stock_span (int *quotes, size_t *spans, size_t length)
{
  spans[0] = 1;
  stack_size_t s = stack_size_t_create(length);
  stack_size_t_push(&s, 0);

  for (size_t i=1; i<length; i++)
  {
    while (!stack_size_t_empty(&s) &&
      quotes[*stack_size_t_top(&s)] <= quotes[i])
    {
      stack_size_t_pop(&s);
    }
    if (stack_size_t_empty(&s))
    {
      spans[i] = i+1;
    }
    else
    {
      spans[i] = i - *stack_size_t_top(&s);
    }
    stack_size_t_push(&s, i);
  }

  stack_size_t_destroy(&s);
}
