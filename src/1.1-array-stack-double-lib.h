#include <stddef.h>

typedef enum
{
  OVERFLOW = 1,
  UNDERFLOW = 0
} stack_error;

typedef struct
{
  double *base;
  size_t size;
  size_t max;
} stack_double;

stack_double stack_double_create (size_t max);

void stack_double_destroy (stack_double *s);

size_t stack_double_size (stack_double *s);
// Return number of elements in stack s.

int stack_double_empty (stack_double *s);
// Return TRUE if stack s is empty.
// Return FALSE if stack s is not empty.

int stack_double_full (stack_double *s);
// Return TRUE if stack s is full.
// Return FALSE if stack s is not full.

int stack_double_push (stack_double *s, double i);
// Push item i onto stack s.
// Return OVERFLOW (non-zero) if stack is full.

double * stack_double_pop (stack_double *s);
// Pop top item off stack s and return pointer to it.
// Return UNDERFLOW (null pointer) if stack is empty.

double * stack_double_top (stack_double *s);
// Return pointer to item on top of stack s without removing it.
// Return UNDERFLOW (null pointer) if stack is empty.
