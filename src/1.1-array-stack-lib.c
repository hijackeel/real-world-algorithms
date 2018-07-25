#include "1.1-array-stack-lib.h"
#include <stdlib.h>
#include <string.h>

stack stack_create(size_t max, size_t type)
// Create and return empty stack that can hold max elements, each of size type.
{
  return (stack){.mem=malloc(max * type), .max=max, .type=type, .elements=0};
}

void stack_destroy(stack *s)
// Free stack s's memory, and zero all elements of struct.
{
  free(s->mem); s->mem = NULL; s->max = s->type = s->elements = 0;
}

size_t stack_size(stack *s)
// Return number of elements in stack s.
{
  return s->elements;
}

int stack_empty(stack *s)
// Return TRUE if stack s is empty.
// Return FALSE if stack s is not empty.
{
  return stack_size(s) == 0;
}

int stack_full(stack *s)
// Return TRUE if stack s is full.
// Return FALSE if stack s is not full.
{
  return stack_size(s) == s->max;
}

int stack_push(stack *s, void *i)
// Push item i onto stack s.
// Return STACK_OVERFLOW (non-zero) if stack is full.
{
  if (stack_full(s))
  {
    return STACK_OVERFLOW;
  }
  else
  {
    memcpy(s->mem + (s->elements * s->type), i, s->type);
    s->elements++;
    return 0;
  }
}

int stack_top(stack *s, void *i)
// Copy item on top of stack s to i without removing it from stack.
// Return STACK_UNDERFLOW (non-zero) if stack is empty.
{
  if (stack_empty(s))
  {
    return STACK_UNDERFLOW;
  }
  else
  {
    memcpy(i, s->mem + ((s->elements-1) * s->type), s->type);
    return 0;
  }
}

int stack_pop(stack *s, void *i)
// Pop top item off stack s and store it at i.
// Return STACK_UNDERFLOW (non-zero) if stack is empty.
{
  int r = stack_top(s, i);
  if (!r)
  {
    s->elements--;
  }
  return r;
}
