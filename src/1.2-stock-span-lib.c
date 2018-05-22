#include "1.2-stock-span-lib.h"
#include "1.1-array-stack-size_t-lib.h"
#include <stdbool.h>

/* Given an array of chronologically-sorted daily closing price quotes for a
stock, find the "span" of the stock's price for each day: the number of
consecutive days going backward on which the price was less than or equal to the
day the span is being calculated for.

12 --2          
11   #---------5
10   #-------4 |
 9   #-1     | #
 8 1 # #     # #
 7 # # #-1   # #
 6 # # # #   # #
 5 # # # #   # #
 4 # # # #-1 # #
 3 # # # # # # #
 2 # # # # # # #
 1 # # # # # # #
   0 1 2 3 4 5 6
*/

void stock_span_stack (int *quotes, size_t *spans, size_t length)
// O(n)
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
// O(n^2)
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
