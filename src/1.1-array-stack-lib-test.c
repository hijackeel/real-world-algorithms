#include "1.1-array-stack-lib.h"
#include "run_test.h"
#include <assert.h>

static void test_stack_empty(stack *s, void *i)
// Test state of empty stack.
{
  assert(stack_top(s, i) == STACK_UNDERFLOW);
  assert(stack_size(s) == 0);
  assert(stack_empty(s));
  assert(!stack_full(s));
}

static void test_stack_underflow(stack *s, void *i)
// Test that attempting to pop from empty stack has no side effects.
{
  assert(stack_pop(s, i) == STACK_UNDERFLOW);
  test_stack_empty(s, i);
}

static void test_stack_half(stack *s, void *i, char top, size_t size)
// Test state of half-full stack (not empty or full).
{
  assert(!stack_top(s, i));
  assert(*(char *)i == top);
  assert(stack_size(s) == size);
  assert(!stack_empty(s));
  assert(!stack_full(s));
}

static void test_stack_full(stack *s, void *i, char top, size_t size)
// Test state of full stack.
{
  assert(!stack_top(s, i));
  assert(*(char *)i == top);
  assert(stack_size(s) == size);
  assert(!stack_empty(s));
  assert(stack_full(s));
}

static void test_stack_overflow(stack *s, void *i, char top, size_t size)
// Test that attempting to push onto full stack has no side effects.
{
  assert(stack_push(s, i) == STACK_OVERFLOW);
  test_stack_full(s, i, top, size);
}

static void test_stack_destroyed(stack *s, void *i)
// Test state of destroyed stack.
{
  assert(stack_top(s, i) == STACK_UNDERFLOW);
  assert(!stack_size(s));
  assert(stack_empty(s));
  assert(stack_full(s));
}

static void test_stack_destroyed_overflow_underflow(stack *s, void *i)
// Test that attempting to push/pop to/from destroyed stack has no side effects.
{
  assert(stack_push(s, i) == STACK_OVERFLOW);
  test_stack_destroyed(s, i);
  assert(stack_pop(s, i) == STACK_UNDERFLOW);
  test_stack_destroyed(s, i);
}

static void test_stack_complete(char *a, size_t max, size_t type)
// Pass in an array of data to copy to stack, and max number of elements.
{
  char c = 'Q';
  void *i = &c;

  // Create and test empty stack.
  stack s = stack_create(max, type);
  test_stack_empty(&s, i);
  test_stack_underflow(&s, i);

  if (max > 1)
  {
    // Incrementally push data onto stack and test state, except for last value.
    for (size_t j = 0; j <= max-2; j++)
    {
      assert(!stack_push(&s, a+j));
      test_stack_half(&s, i, a[j], j+1);
    }
  }

  // Push last value onto stack, test state, and pop off again.
  assert(!stack_push(&s, a+max-1));
  test_stack_full(&s, i, a[max-1], max);
  test_stack_overflow(&s, i, a[max-1], max);
  assert(!stack_pop(&s, i));
  assert(*(char *)i == a[max-1]);

  if (max > 1)
  {
    // Incrementally test stack state and pop off data, until empty.
    for (size_t j = max-2; j < max; j--)
    {
      test_stack_half(&s, i, a[j], j+1);
      assert(!stack_pop(&s, i));
      assert(*(char *)i == a[j]);
    }
  }

  // Test and destroy empty stack.
  test_stack_empty(&s, i);
  test_stack_underflow(&s, i);
  stack_destroy(&s);

  // Test destroyed stack.
  test_stack_destroyed_overflow_underflow(&s, i);
}

static void test_stack_one()
{
  char a[] = {'H'};
  test_stack_complete(a, sizeof a, sizeof *a);
}

static void test_stack_two()
{
  char a[] = {'H', 'J'};
  test_stack_complete(a, sizeof a, sizeof *a);
}

static void test_stack_five()
{
  char a[] = {'H', 'J', 'K', 'L', ';'};
  test_stack_complete(a, sizeof a, sizeof *a);
}

static void test_stack_array_of_overflows()
{
  char a[] = {STACK_OVERFLOW, STACK_OVERFLOW, STACK_OVERFLOW};
  test_stack_complete(a, sizeof a, sizeof *a);
}

static void test_stack_array_of_underflows()
{
  char a[] = {STACK_UNDERFLOW, STACK_UNDERFLOW, STACK_UNDERFLOW};
  test_stack_complete(a, sizeof a, sizeof *a);
}

static void test_stack_half_destroyed()
// Test destruction of non-empty stack.
{
  char c = 'Q';
  void *i = &c;
  stack s = stack_create(2, sizeof(char));
  stack_push(&s, i);
  stack_destroy(&s);
  test_stack_destroyed_overflow_underflow(&s, i);
}

int main()
{
  run_test(test_stack_one);
  run_test(test_stack_two);
  run_test(test_stack_five);
  run_test(test_stack_array_of_overflows);
  run_test(test_stack_array_of_underflows);
  run_test(test_stack_half_destroyed);
  printf("\nOK\n\n");
}
