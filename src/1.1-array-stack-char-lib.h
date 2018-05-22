#include <stddef.h>

typedef enum
{
  OVERFLOW = 1,
  UNDERFLOW = 0
} stack_error;

typedef struct
{
  char *base;
  size_t size;
  size_t max;
} stack_char;

stack_char stack_char_create (size_t max);

void stack_char_destroy (stack_char *s);

size_t stack_char_size (stack_char *s);
// Return number of elements in stack s.

int stack_char_empty (stack_char *s);
// Return TRUE if stack s is empty.
// Return FALSE if stack s is not empty.

int stack_char_full (stack_char *s);
// Return TRUE if stack s is full.
// Return FALSE if stack s is not full.

int stack_char_push (stack_char *s, char i);
// Push item i onto stack s.
// Return OVERFLOW (non-zero) if stack is full.

char * stack_char_pop (stack_char *s);
// Pop top item off stack s and return pointer to it.
// Return UNDERFLOW (null pointer) if stack is empty.

char * stack_char_top (stack_char *s);
// Return pointer to item on top of stack s without removing it.
// Return UNDERFLOW (null pointer) if stack is empty.
