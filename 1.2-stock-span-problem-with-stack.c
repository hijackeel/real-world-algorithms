#include "1.1-array-based-stack.h"
#include <stdio.h>

int quotes[] = {7, 11, 8, 6, 3, 8, 9};
int spans[7];

int main ()
{
  spans[0] = 1;
  stack s = create(7);
  push(&s, 0);
  for (int i=1; i<=7; i++)
  {
    while (!empty(&s) && quotes[top(&s)] <= quotes[i])
    {
      pop(&s);
    }
    if (empty(&s))
    {
      spans[i] = i+1;
    }
    else
    {
      spans[i] = i - top(&s);
    }
    push(&s, i);
  }
  for (int i=0; i<7; i++)
  {
    printf("%i\n", spans[i]);
  }
  destroy(&s);
}
