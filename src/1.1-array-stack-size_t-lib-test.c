#include "1.1-array-stack-size_t-lib.h"
#include "run_test.h"
#include <assert.h>

static void test_stack_size_t_empty(stack_size_t *s)
// Test state of empty stack.
{
  assert(stack_size_t_top(s) == UNDERFLOW);
  assert(stack_size_t_size(s) == 0);
  assert(stack_size_t_empty(s));
  assert(!stack_size_t_full(s));
}

static void test_stack_size_t_underflow(stack_size_t *s)
// Test that attempting to pop from empty stack has no side effects.
{
  assert(stack_size_t_pop(s) == UNDERFLOW);
  test_stack_size_t_empty(s);
}

static void test_stack_size_t_half(stack_size_t *s, size_t top, size_t size)
// Test state of half-full stack (not empty or full).
{
  assert(stack_size_t_top(s) != UNDERFLOW);
  assert(*stack_size_t_top(s) == top);
  assert(stack_size_t_size(s) == size);
  assert(!stack_size_t_empty(s));
  assert(!stack_size_t_full(s));
}

static void test_stack_size_t_full(stack_size_t *s, size_t top, size_t size)
// Test state of full stack.
{
  assert(stack_size_t_top(s) != UNDERFLOW);
  assert(*stack_size_t_top(s) == top);
  assert(stack_size_t_size(s) == size);
  assert(!stack_size_t_empty(s));
  assert(stack_size_t_full(s));
}

static void test_stack_size_t_overflow(stack_size_t *s, size_t top, size_t size)
// Test that attempting to push onto full stack has no side effects.
{
  assert(stack_size_t_push(s, 42) == OVERFLOW);
  test_stack_size_t_full(s, top, size);
}

static void test_stack_size_t_destroyed(stack_size_t *s)
// Test state of destroyed stack.
{
  assert(stack_size_t_top(s) == UNDERFLOW);
  assert(!stack_size_t_size(s));
  assert(stack_size_t_empty(s));
  assert(stack_size_t_full(s));
}

static void test_stack_size_t_destroyed_overflow_underflow(stack_size_t *s)
// Test that attempting to push/pop to/from destroyed stack has no side effects.
{
  assert(stack_size_t_push(s, 42) == OVERFLOW);
  test_stack_size_t_destroyed(s);
  assert(stack_size_t_pop(s) == UNDERFLOW);
  test_stack_size_t_destroyed(s);
}

static void test_stack_size_t_complete(size_t *a, size_t max)
// Pass in an array of data to copy to stack, and max number of elements.
{
  // Create and test empty stack.
  stack_size_t s = stack_size_t_create(max);
  test_stack_size_t_empty(&s);
  test_stack_size_t_underflow(&s);

  if (max > 1)
  {
    // Incrementally push data onto stack and test state, except for last value.
    for (size_t i = 0; i <= max-2; i++)
    {
      assert(!stack_size_t_push(&s, a[i]));
      test_stack_size_t_half(&s, a[i], i+1);
    }
  }

  // Push last value onto stack, test state, and pop off again.
  assert(!stack_size_t_push(&s, a[max-1]));
  test_stack_size_t_full(&s, a[max-1], max);
  test_stack_size_t_overflow(&s, a[max-1], max);
  assert(*stack_size_t_pop(&s) == a[max-1]);

  if (max > 1)
  {
    // Incrementally test stack state and pop off data, until empty.
    for (size_t i = max-2; i < max; i--)
    {
      test_stack_size_t_half(&s, a[i], i+1);
      assert(*stack_size_t_pop(&s) == a[i]);
    }
  }

  // Test and destroy empty stack.
  test_stack_size_t_empty(&s);
  test_stack_size_t_underflow(&s);
  stack_size_t_destroy(&s);

  // Test destroyed stack.
  test_stack_size_t_destroyed_overflow_underflow(&s);
}

static void test_stack_size_t_one()
{
  size_t a[] = {20};
  size_t max = sizeof a / sizeof *a;
  test_stack_size_t_complete(a, max);
}

static void test_stack_size_t_two()
{
  size_t a[] = {20, 37};
  size_t max = sizeof a / sizeof *a;
  test_stack_size_t_complete(a, max);
}

static void test_stack_size_t_five()
{
  size_t a[] = {20, 37, 99, 11, 1066};
  size_t max = sizeof a / sizeof *a;
  test_stack_size_t_complete(a, max);
}

static void test_stack_size_t_array_of_overflows()
{
  size_t a[] = {OVERFLOW, OVERFLOW, OVERFLOW, OVERFLOW, OVERFLOW};
  size_t max = sizeof a / sizeof *a;
  test_stack_size_t_complete(a, max);
}

static void test_stack_size_t_array_of_underflows()
{
  size_t a[] = {UNDERFLOW, UNDERFLOW, UNDERFLOW, UNDERFLOW, UNDERFLOW};
  size_t max = sizeof a / sizeof *a;
  test_stack_size_t_complete(a, max);
}

static void test_stack_size_t_half_destroyed()
// Test destruction of non-empty stack.
{
  stack_size_t s = stack_size_t_create(2);
  stack_size_t_push(&s, 42);
  stack_size_t_destroy(&s);
  test_stack_size_t_destroyed_overflow_underflow(&s);
}

int main()
{
  run_test(test_stack_size_t_one);
  run_test(test_stack_size_t_two);
  run_test(test_stack_size_t_five);
  run_test(test_stack_size_t_array_of_overflows);
  run_test(test_stack_size_t_array_of_underflows);
  run_test(test_stack_size_t_half_destroyed);
  printf("\nOK\n\n");
}
