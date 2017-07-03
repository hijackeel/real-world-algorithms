#include <stdlib.h>


typedef enum
{
  OVERFLOW = -1,
  UNDERFLOW = -2
} stack_error;


typedef struct
{
  int max;
  int *array;
  int top;
} stack;


stack create (int max)
{
  return (stack){.max=max, .array=calloc(max, sizeof(int)), .top=-1};
}


void destroy (stack *s)
{
  free(s->array);
}


int size (stack *s)
// Return number of elements in stack s.
{
  return s->top + 1;
}


int empty (stack *s)
// Return TRUE if stack s is empty.
// Return FALSE if stack s is not empty.
{
  return size(s) == 0;
}


int full (stack *s)
// Return TRUE if stack s is full.
// Return FALSE if stack s is not full.
{
  return size(s) == s->max;
}


int push (stack *s, int i)
// Push item i onto stack s.
// Return error if stack is full.
{
  return full(s) ? OVERFLOW : 0 * (s->array[++(s->top)] = i);
}


int pop (stack *s)
// Pop top item off stack s and return it.
// Return error if stack is empty.
{
  return empty(s) ? UNDERFLOW : s->array[(s->top)--];
}


int top (stack *s)
// Return value of item on top of stack s without removing it.
// Return error if stack is empty.
{
  return empty(s) ? UNDERFLOW : s->array[s->top];
}
