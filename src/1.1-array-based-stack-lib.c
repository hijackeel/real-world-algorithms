#include "1.1-array-based-stack-lib.h"
#include <stdlib.h>


stack stack_create (int max)
{
  return (stack){.max=max, .array=malloc(max * sizeof(int)), .top=-1};
}


void stack_destroy (stack *s)
{
  free(s->array);
}


int stack_size (stack *s)
// Return number of elements in stack s.
{
  return s->top + 1;
}


int stack_empty (stack *s)
// Return TRUE if stack s is empty.
// Return FALSE if stack s is not empty.
{
  return stack_size(s) == 0;
}


int stack_full (stack *s)
// Return TRUE if stack s is full.
// Return FALSE if stack s is not full.
{
  return stack_size(s) == s->max;
}


int stack_push (stack *s, int i)
// Push item i onto stack s.
// Return error if stack is full.
{
  return stack_full(s) ? OVERFLOW : 0 * (s->array[++(s->top)] = i);
}


int stack_pop (stack *s)
// Pop top item off stack s and return it.
// Return error if stack is empty.
{
  return stack_empty(s) ? UNDERFLOW : s->array[(s->top)--];
}


int stack_top (stack *s)
// Return value of item on top of stack s without removing it.
// Return error if stack is empty.
{
  return stack_empty(s) ? UNDERFLOW : s->array[s->top];
}
