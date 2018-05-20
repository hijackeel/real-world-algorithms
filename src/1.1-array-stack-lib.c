#include "1.1-array-stack-lib.h"
#include <stdlib.h>


stack stack_create (size_t max)
{
  int * array = malloc(max * sizeof(int));
  return (stack){.bottom=array, .top=array, .max=max};
}


void stack_destroy (stack *s)
{
  free(s->bottom); s->bottom=s->top=0; s->max=0;
}


size_t stack_size (stack *s)
// Return number of elements in stack s.
{
  return (size_t)(s->top - s->bottom);
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
// Return OVERFLOW (non-zero) if stack is full.
{
  return stack_full(s) ? OVERFLOW : 0 * (*(++(s->top)) = i);
}


int * stack_pop (stack *s)
// Pop top item off stack s and return pointer to it.
// Return UNDERFLOW (null pointer) if stack is empty.
{
  return stack_empty(s) ? UNDERFLOW : (s->top)--;
}


int * stack_top (stack *s)
// Return pointer to item on top of stack s without removing it.
// Return UNDERFLOW (null pointer) if stack is empty.
{
  return stack_empty(s) ? UNDERFLOW : s->top;
}
