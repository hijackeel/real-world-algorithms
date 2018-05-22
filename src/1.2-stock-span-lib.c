#include "1.2-stock-span-lib.h"
#include "1.1-array-stack-lib.h"

void stock_span (int *quotes, size_t *spans, size_t length)
{
  spans[0] = 1;
  stack_size_t s = STACK_CREATE(length, size_t);
  STACK_PUSH(s, 0);

  for (size_t i=1; i<length; i++)
  {
    while (!STACK_EMPTY(s) && quotes[*STACK_TOP(s)] <= quotes[i])
    {
      STACK_POP(s);
    }
    if (STACK_EMPTY(s))
    {
      spans[i] = i+1;
    }
    else
    {
      spans[i] = i - *STACK_TOP(s);
    }
    STACK_PUSH(s, i);
  }

  STACK_DESTROY(s);
}
