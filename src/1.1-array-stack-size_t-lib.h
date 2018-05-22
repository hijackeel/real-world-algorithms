#include <stddef.h>

typedef enum
{
  OVERFLOW = 1,
  UNDERFLOW = 0
} stack_error;

typedef struct
{
  size_t *base;
  size_t size;
  size_t max;
} stack_size_t;

stack_size_t stack_size_t_create (size_t max);

void stack_size_t_destroy (stack_size_t *s);

size_t stack_size_t_size (stack_size_t *s);
// Return number of elements in stack s.

int stack_size_t_empty (stack_size_t *s);
// Return TRUE if stack s is empty.
// Return FALSE if stack s is not empty.

int stack_size_t_full (stack_size_t *s);
// Return TRUE if stack s is full.
// Return FALSE if stack s is not full.

int stack_size_t_push (stack_size_t *s, size_t i);
// Push item i onto stack s.
// Return OVERFLOW (non-zero) if stack is full.

size_t * stack_size_t_pop (stack_size_t *s);
// Pop top item off stack s and return pointer to it.
// Return UNDERFLOW (null pointer) if stack is empty.

size_t * stack_size_t_top (stack_size_t *s);
// Return pointer to item on top of stack s without removing it.
// Return UNDERFLOW (null pointer) if stack is empty.
