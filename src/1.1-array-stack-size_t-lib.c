#include "1.1-array-stack-size_t-lib.h"
#include <stdlib.h>


stack_size_t stack_size_t_create (size_t max)
{
  return (stack_size_t){.base=malloc(max * sizeof(size_t)), .size=0, .max=max};
}


void stack_size_t_destroy (stack_size_t *s)
{
  free(s->base); s->base = 0; s->size = s->max = 0;
}


size_t stack_size_t_size (stack_size_t *s)
// Return number of elements in stack s.
{
  return s->size;
}


int stack_size_t_empty (stack_size_t *s)
// Return TRUE if stack s is empty.
// Return FALSE if stack s is not empty.
{
  return stack_size_t_size(s) == 0;
}


int stack_size_t_full (stack_size_t *s)
// Return TRUE if stack s is full.
// Return FALSE if stack s is not full.
{
  return stack_size_t_size(s) == s->max;
}


int stack_size_t_push (stack_size_t *s, size_t i)
// Push item i onto stack s.
// Return OVERFLOW (non-zero) if stack is full.
{
  return stack_size_t_full(s) ? OVERFLOW : 0 * (int)(s->base[(s->size)++] = i);
}


size_t * stack_size_t_pop (stack_size_t *s)
// Pop top item off stack s and return pointer to it.
// Return UNDERFLOW (null pointer) if stack is empty.
{
  return stack_size_t_empty(s) ? UNDERFLOW : s->base + --(s->size);
}


size_t * stack_size_t_top (stack_size_t *s)
// Return pointer to item on top of stack s without removing it.
// Return UNDERFLOW (null pointer) if stack is empty.
{
  return stack_size_t_empty(s) ? UNDERFLOW : s->base + s->size - 1;
}
