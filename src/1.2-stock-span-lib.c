#include "1.2-stock-span-lib.h"
#include "1.1-array-stack-size_t-lib.h"
#include <stdbool.h>

void stock_span_stack (int *quotes, size_t *spans, size_t length)
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

void stock_span_simple (int *quotes, size_t *spans, size_t length)
{
  for (size_t i=0; i<length; i++)
  {
    size_t k = 1;
    bool span_end = false;
    while (i-k < length && !span_end)
    {
      quotes[i-k] <= quotes[i] ? k++ : (span_end = true);
    }
    spans[i] = k;
  }
}
