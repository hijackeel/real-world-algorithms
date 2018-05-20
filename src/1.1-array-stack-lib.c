#include "1.1-array-stack-lib.h"
#include <stdlib.h>


stack stack_create (size_t max)
{
  return (stack){.max=max, .array=malloc(max * sizeof(int)), .size=0};
}


void stack_destroy (stack *s)
{
  free(s->array); s->array = 0; s->max = s->size = 0;
}


size_t stack_size (stack *s)
// Return number of elements in stack s.
{
  return s->size;
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
  return stack_full(s) ? OVERFLOW : 0 * (s->array[(s->size)++] = i);
}


int stack_pop (stack *s)
// Pop top item off stack s and return it.
// Return error if stack is empty.
{
  return stack_empty(s) ? UNDERFLOW : s->array[--(s->size)];
}


int stack_top (stack *s)
// Return value of item on top of stack s without removing it.
// Return error if stack is empty.
{
  return stack_empty(s) ? UNDERFLOW : s->array[(s->size)-1];
}
