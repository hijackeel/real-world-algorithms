#include <stddef.h>

typedef enum
{
  STACK_OVERFLOW = 1,
  STACK_UNDERFLOW = 2
} stack_error;

typedef struct
{
  char *mem;
  size_t max;
  size_t type;
  size_t elements;
} stack;

stack stack_create(size_t max, size_t type);
// Create and return empty stack that can hold max elements, each of size type.

void stack_destroy(stack *s);
// Free stack s's memory, and zero all elements of struct.

size_t stack_size(stack *s);
// Return number of elements in stack s.

int stack_empty(stack *s);
// Return TRUE if stack s is empty.
// Return FALSE if stack s is not empty.

int stack_full(stack *s);
// Return TRUE if stack s is full.
// Return FALSE if stack s is not full.

int stack_push(stack *s, void *i);
// Push item i onto stack s.
// Return STACK_OVERFLOW (non-zero) if stack is full.

int stack_top(stack *s, void *i);
// Copy item on top of stack s to i without removing it from stack.
// Return STACK_UNDERFLOW (non-zero) if stack is empty.

int stack_pop(stack *s, void *i);
// Pop top item off stack s and store it at i.
// Return STACK_UNDERFLOW (non-zero) if stack is empty.
