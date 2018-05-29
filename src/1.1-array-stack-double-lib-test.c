#include "1.1-array-stack-double-lib.h"
#include "run_test.h"
#include <assert.h>

static void test_stack_double_empty(stack_double *s)
// Test state of empty stack.
{
  assert(stack_double_top(s) == UNDERFLOW);
  assert(stack_double_size(s) == 0);
  assert(stack_double_empty(s));
  assert(!stack_double_full(s));
}

static void test_stack_double_underflow(stack_double *s)
// Test that attempting to pop from empty stack has no side effects.
{
  assert(stack_double_pop(s) == UNDERFLOW);
  test_stack_double_empty(s);
}

static void test_stack_double_half(stack_double *s, double top, size_t size)
// Test state of half-full stack (not empty or full).
{
  assert(stack_double_top(s) != UNDERFLOW);
  assert(*stack_double_top(s) == top);
  assert(stack_double_size(s) == size);
  assert(!stack_double_empty(s));
  assert(!stack_double_full(s));
}

static void test_stack_double_full(stack_double *s, double top, size_t size)
// Test state of full stack.
{
  assert(stack_double_top(s) != UNDERFLOW);
  assert(*stack_double_top(s) == top);
  assert(stack_double_size(s) == size);
  assert(!stack_double_empty(s));
  assert(stack_double_full(s));
}

static void test_stack_double_overflow(stack_double *s, double top, size_t size)
// Test that attempting to push onto full stack has no side effects.
{
  assert(stack_double_push(s, 42.0) == OVERFLOW);
  test_stack_double_full(s, top, size);
}

static void test_stack_double_destroyed(stack_double *s)
// Test state of destroyed stack.
{
  assert(stack_double_top(s) == UNDERFLOW);
  assert(!stack_double_size(s));
  assert(stack_double_empty(s));
  assert(stack_double_full(s));
}

static void test_stack_double_destroyed_overflow_underflow(stack_double *s)
// Test that attempting to push/pop to/from destroyed stack has no side effects.
{
  assert(stack_double_push(s, 42.0) == OVERFLOW);
  test_stack_double_destroyed(s);
  assert(stack_double_pop(s) == UNDERFLOW);
  test_stack_double_destroyed(s);
}

static void test_stack_double_complete(double *a, size_t max)
// Pass in an array of data to copy to stack, and max number of elements.
{
  // Create and test empty stack.
  stack_double s = stack_double_create(max);
  test_stack_double_empty(&s);
  test_stack_double_underflow(&s);

  if (max > 1)
  {
    // Incrementally push data onto stack and test state, except for last value.
    for (size_t i = 0; i <= max-2; i++)
    {
      assert(!stack_double_push(&s, a[i]));
      test_stack_double_half(&s, a[i], i+1);
    }
  }

  // Push last value onto stack, test state, and pop off again.
  assert(!stack_double_push(&s, a[max-1]));
  test_stack_double_full(&s, a[max-1], max);
  test_stack_double_overflow(&s, a[max-1], max);
  assert(*stack_double_pop(&s) == a[max-1]);

  if (max > 1)
  {
    // Incrementally test stack state and pop off data, until empty.
    for (size_t i = max-2; i < max; i--)
    {
      test_stack_double_half(&s, a[i], i+1);
      assert(*stack_double_pop(&s) == a[i]);
    }
  }

  // Test and destroy empty stack.
  test_stack_double_empty(&s);
  test_stack_double_underflow(&s);
  stack_double_destroy(&s);

  // Test destroyed stack.
  test_stack_double_destroyed_overflow_underflow(&s);
}

static void test_stack_double_one()
{
  double a[] = {20.0};
  size_t max = sizeof a / sizeof *a;
  test_stack_double_complete(a, max);
}

static void test_stack_double_two()
{
  double a[] = {20.0, 37.0};
  size_t max = sizeof a / sizeof *a;
  test_stack_double_complete(a, max);
}

static void test_stack_double_five()
{
  double a[] = {20.0, 37.0, 99.0, 11.0, 1066.0};
  size_t max = sizeof a / sizeof *a;
  test_stack_double_complete(a, max);
}

static void test_stack_double_array_of_overflows()
{
  double a[] = {OVERFLOW, OVERFLOW, OVERFLOW, OVERFLOW, OVERFLOW};
  size_t max = sizeof a / sizeof *a;
  test_stack_double_complete(a, max);
}

static void test_stack_double_array_of_underflows()
{
  double a[]= {UNDERFLOW, UNDERFLOW, UNDERFLOW, UNDERFLOW, UNDERFLOW};
  size_t max = sizeof a / sizeof *a;
  test_stack_double_complete(a, max);
}

static void test_stack_double_half_destroyed()
// Test destruction of non-empty stack.
{
  stack_double s = stack_double_create(2);
  stack_double_push(&s, 42.0);
  stack_double_destroy(&s);
  test_stack_double_destroyed_overflow_underflow(&s);
}

int main()
{
  run_test(test_stack_double_one);
  run_test(test_stack_double_two);
  run_test(test_stack_double_five);
  run_test(test_stack_double_array_of_overflows);
  run_test(test_stack_double_array_of_underflows);
  run_test(test_stack_double_half_destroyed);
  printf("\nOK\n\n");
}
