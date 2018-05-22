#include "1.1-array-stack-lib.h"
#include <stdlib.h>


#define BODY_STACK_CREATE(TYPE) \
{\
  return (stack_##TYPE){.base=malloc(max * type), .size=0, .max=max};\
}


#define BODY_STACK_DESTROY \
{\
  free(s->base); s->base = 0; s->size = s->max = 0;\
}


// Return number of elements in stack s.
#define BODY_STACK_SIZE \
{\
  return s->size;\
}


// Return TRUE if stack s is empty.
// Return FALSE if stack s is not empty.
#define BODY_STACK_EMPTY(TYPE) \
{\
  return stack_size_##TYPE(s) == 0;\
}


// Return TRUE if stack s is full.
// Return FALSE if stack s is not full.
#define BODY_STACK_FULL(TYPE) \
{\
  return stack_size_##TYPE(s) == s->max;\
}


// Push item i onto stack s.
// Return OVERFLOW (non-zero) if stack is full.
#define BODY_STACK_PUSH(TYPE) \
{\
  return stack_full_##TYPE(s) ? OVERFLOW : 0 * (int)(s->base[(s->size)++] = i);\
}


// Pop top item off stack s and return pointer to it.
// Return UNDERFLOW (null pointer) if stack is empty.
#define BODY_STACK_POP(TYPE) \
{\
  return stack_empty_##TYPE(s) ? UNDERFLOW : s->base + --(s->size);\
}


// Return pointer to item on top of stack s without removing it.
// Return UNDERFLOW (null pointer) if stack is empty.
#define BODY_STACK_TOP(TYPE) \
{\
  return stack_empty_##TYPE(s) ? UNDERFLOW : s->base + s->size - 1;\
}


#define DECL_BODY_ALL(TYPE) \
  DECL_STACK_CREATE(TYPE)\
  BODY_STACK_CREATE(TYPE)\
  DECL_STACK_DESTROY(TYPE)\
  BODY_STACK_DESTROY\
  DECL_STACK_SIZE(TYPE)\
  BODY_STACK_SIZE\
  DECL_STACK_EMPTY(TYPE)\
  BODY_STACK_EMPTY(TYPE)\
  DECL_STACK_FULL(TYPE)\
  BODY_STACK_FULL(TYPE)\
  DECL_STACK_PUSH(TYPE)\
  BODY_STACK_PUSH(TYPE)\
  DECL_STACK_POP(TYPE)\
  BODY_STACK_POP(TYPE)\
  DECL_STACK_TOP(TYPE)\
  BODY_STACK_TOP(TYPE)

DECL_BODY_ALL(int)
DECL_BODY_ALL(size_t)
DECL_BODY_ALL(char)
