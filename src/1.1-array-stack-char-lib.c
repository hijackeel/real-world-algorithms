#include "1.1-array-stack-char-lib.h"
#include <stdlib.h>


stack_char stack_char_create (size_t max)
{
  return (stack_char){.base=malloc(max * sizeof(char)), .size=0, .max=max};
}


void stack_char_destroy (stack_char *s)
{
  free(s->base); s->base = 0; s->size = s->max = 0;
}


size_t stack_char_size (stack_char *s)
// Return number of elements in stack s.
{
  return s->size;
}


int stack_char_empty (stack_char *s)
// Return TRUE if stack s is empty.
// Return FALSE if stack s is not empty.
{
  return stack_char_size(s) == 0;
}


int stack_char_full (stack_char *s)
// Return TRUE if stack s is full.
// Return FALSE if stack s is not full.
{
  return stack_char_size(s) == s->max;
}


int stack_char_push (stack_char *s, char i)
// Push item i onto stack s.
// Return OVERFLOW (non-zero) if stack is full.
{
  return stack_char_full(s) ? OVERFLOW : 0 * (s->base[(s->size)++] = i);
}


char * stack_char_pop (stack_char *s)
// Pop top item off stack s and return pointer to it.
// Return UNDERFLOW (null pointer) if stack is empty.
{
  return stack_char_empty(s) ? UNDERFLOW : s->base + --(s->size);
}


char * stack_char_top (stack_char *s)
// Return pointer to item on top of stack s without removing it.
// Return UNDERFLOW (null pointer) if stack is empty.
{
  return stack_char_empty(s) ? UNDERFLOW : s->base + s->size - 1;
}
