#include "1.1-array-stack-double-lib.h"
#include <stdlib.h>


stack_double stack_double_create (size_t max)
{
  return (stack_double){.base=malloc(max * sizeof(double)), .size=0, .max=max};
}


void stack_double_destroy (stack_double *s)
{
  free(s->base); s->base = 0; s->size = s->max = 0;
}


size_t stack_double_size (stack_double *s)
// Return number of elements in stack s.
{
  return s->size;
}


int stack_double_empty (stack_double *s)
// Return TRUE if stack s is empty.
// Return FALSE if stack s is not empty.
{
  return stack_double_size(s) == 0;
}


int stack_double_full (stack_double *s)
// Return TRUE if stack s is full.
// Return FALSE if stack s is not full.
{
  return stack_double_size(s) == s->max;
}


int stack_double_push (stack_double *s, double i)
// Push item i onto stack s.
// Return OVERFLOW (non-zero) if stack is full.
{
  return stack_double_full(s) ? OVERFLOW : 0 * (int)(s->base[(s->size)++] = i);
}


double * stack_double_pop (stack_double *s)
// Pop top item off stack s and return pointer to it.
// Return UNDERFLOW (null pointer) if stack is empty.
{
  return stack_double_empty(s) ? UNDERFLOW : s->base + --(s->size);
}


double * stack_double_top (stack_double *s)
// Return pointer to item on top of stack s without removing it.
// Return UNDERFLOW (null pointer) if stack is empty.
{
  return stack_double_empty(s) ? UNDERFLOW : s->base + s->size - 1;
}
