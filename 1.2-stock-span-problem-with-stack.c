#include "1.1-array-based-stack.h"
#include <stdio.h>

int quotes[] = {7, 11, 8, 6, 3, 8, 9};
int spans[7];

int main ()
{
  spans[0] = 1;
  stack s = stack_create(7);
  stack_push(&s, 0);
  for (int i=1; i<=7; i++)
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
  for (int i=0; i<7; i++)
  {
    printf("%i\n", spans[i]);
  }
  stack_destroy(&s);
}
