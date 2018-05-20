#include <stddef.h>

typedef enum
{
  OVERFLOW = 1,
  UNDERFLOW = 0
} stack_error;

typedef struct
{
  int *base;
  size_t size;
  size_t max;
} stack;

stack stack_create (size_t max);

void stack_destroy (stack *s);

size_t stack_size (stack *s);
// Return number of elements in stack s.

int stack_empty (stack *s);
// Return TRUE if stack s is empty.
// Return FALSE if stack s is not empty.

int stack_full (stack *s);
// Return TRUE if stack s is full.
// Return FALSE if stack s is not full.

int stack_push (stack *s, int i);
// Push item i onto stack s.
// Return OVERFLOW (non-zero) if stack is full.

int * stack_pop (stack *s);
// Pop top item off stack s and return pointer to it.
// Return UNDERFLOW (null pointer) if stack is empty.

int * stack_top (stack *s);
// Return pointer to item on top of stack s without removing it.
// Return UNDERFLOW (null pointer) if stack is empty.
