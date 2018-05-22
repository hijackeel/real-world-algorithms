#include <stddef.h>


#define STACK_CREATE(MAX, TYPE) \
  _Generic((TYPE), \
    int: stack_create_int,\
    size_t: stack_create_size_t,\
    char: stack_create_char\
  )(MAX, sizeof(TYPE))
 
#define STACK_OP_GENERIC(OP) \
  _Generic((S),\
    stack_int: stack_##OP_int,\
    stack_size_t: stack_##OP_size_t,\
    stack_char: stack_##OP_char\
  )(&##S)

#define STACK_DESTROY(S) \
  STACK_OP_GENERIC(destroy)

#define STACK_SIZE(S) \
  STACK_OP_GENERIC(size)

#define STACK_EMPTY(S) \
  STACK_OP_GENERIC(empty)

#define STACK_FULL(S) \
  STACK_OP_GENERIC(full)

#define STACK_PUSH(S, I) \
  _Generic((S),\
    stack_int: stack_push_int,\
    stack_size_t: stack_push_size_t,\
    stack_char: stack_push_char\
  )(&##S, I)

#define STACK_POP(S) \
  STACK_OP_GENERIC(pop)

#define STACK_TOP(S) \
  STACK_OP_GENERIC(top)

typedef enum
{
  OVERFLOW = 1,
  UNDERFLOW = 0
} stack_error;

#define DEF_STRUCT_STACK(TYPE)\
  typedef struct\
  {\
    TYPE *base;\
    size_t size;\
    size_t max;\
  } stack_##TYPE

#define DECL_STACK_CREATE(TYPE)\
  stack_##TYPE stack_create_##TYPE (size_t max, size_t type)

#define DECL_STACK_DESTROY(TYPE)\
  void stack_destroy_##TYPE (stack_##TYPE *s)

#define DECL_STACK_SIZE(TYPE)\
  size_t stack_size_##TYPE (stack_##TYPE *s)
// Return number of elements in stack s.

#define DECL_STACK_EMPTY(TYPE)\
  int stack_empty_##TYPE (stack_##TYPE *s)
// Return TRUE if stack s is empty.
// Return FALSE if stack s is not empty.

#define DECL_STACK_FULL(TYPE)\
  int stack_full_##TYPE (stack_##TYPE *s)
// Return TRUE if stack s is full.
// Return FALSE if stack s is not full.

#define DECL_STACK_PUSH(TYPE)\
  int stack_push_##TYPE (stack_##TYPE *s, TYPE i)
// Push item i onto stack s.
// Return OVERFLOW (non-zero) if stack is full.

#define DECL_STACK_POP(TYPE)\
  TYPE * stack_pop_##TYPE (stack_##TYPE *s)
// Pop top item off stack s and return pointer to it.
// Return UNDERFLOW (null pointer) if stack is empty.

#define DECL_STACK_TOP(TYPE)\
  TYPE * stack_top_##TYPE (stack_##TYPE *s)
// Return pointer to item on top of stack s without removing it.
// Return UNDERFLOW (null pointer) if stack is empty.

#define DEF_DECL_ALL(TYPE)\
  DEF_STRUCT_STACK(TYPE);\
  DECL_STACK_CREATE(TYPE);\
  DECL_STACK_DESTROY(TYPE);\
  DECL_STACK_SIZE(TYPE);\
  DECL_STACK_EMPTY(TYPE);\
  DECL_STACK_FULL(TYPE);\
  DECL_STACK_PUSH(TYPE);\
  DECL_STACK_POP(TYPE);\
  DECL_STACK_TOP(TYPE);\

DEF_DECL_ALL(int)
DEF_DECL_ALL(size_t)
DEF_DECL_ALL(char)
