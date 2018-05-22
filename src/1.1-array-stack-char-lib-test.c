#include "1.1-array-stack-char-lib.h"
#include "run_test.h"
#include <assert.h>

static void test_stack_char_empty(stack_char *s)
// Test state of empty stack.
{
  assert(stack_char_top(s) == UNDERFLOW);
  assert(stack_char_size(s) == 0);
  assert(stack_char_empty(s));
  assert(!stack_char_full(s));
}

static void test_stack_char_underflow(stack_char *s)
// Test that attempting to pop from empty stack has no side effects.
{
  assert(stack_char_pop(s) == UNDERFLOW);
  test_stack_char_empty(s);
}

static void test_stack_char_half(stack_char *s, char top, size_t size)
// Test state of half-full stack (not empty or full).
{
  assert(stack_char_top(s) != UNDERFLOW);
  assert(*stack_char_top(s) == top);
  assert(stack_char_size(s) == size);
  assert(!stack_char_empty(s));
  assert(!stack_char_full(s));
}

static void test_stack_char_full(stack_char *s, char top, size_t size)
// Test state of full stack.
{
  assert(stack_char_top(s) != UNDERFLOW);
  assert(*stack_char_top(s) == top);
  assert(stack_char_size(s) == size);
  assert(!stack_char_empty(s));
  assert(stack_char_full(s));
}

static void test_stack_char_overflow(stack_char *s, char top, size_t size)
// Test that attempting to push onto full stack has no side effects.
{
  assert(stack_char_push(s, 'Q') == OVERFLOW);
  test_stack_char_full(s, top, size);
}

static void test_stack_char_destroyed(stack_char *s)
// Test state of destroyed stack.
{
  assert(stack_char_top(s) == UNDERFLOW);
  assert(!stack_char_size(s));
  assert(stack_char_empty(s));
  assert(stack_char_full(s));
}

static void test_stack_char_destroyed_overflow_underflow(stack_char *s)
// Test that attempting to push/pop to/from destroyed stack has no side effects.
{
  assert(stack_char_push(s, 'Q') == OVERFLOW);
  test_stack_char_destroyed(s);
  assert(stack_char_pop(s) == UNDERFLOW);
  test_stack_char_destroyed(s);
}

static void test_stack_char_complete(char *a, size_t max)
// Pass in an array of data to copy to stack, and max number of elements.
{
  // Create and test empty stack.
  stack_char s = stack_char_create(max);
  test_stack_char_empty(&s);
  test_stack_char_underflow(&s);

  if (max > 1)
  {
    // Incrementally push data onto stack and test state, except for last value.
    for (size_t i = 0; i <= max-2; i++)
    {
      assert(!stack_char_push(&s, a[i]));
      test_stack_char_half(&s, a[i], i+1);
    }
  }

  // Push last value onto stack, test state, and pop off again.
  assert(!stack_char_push(&s, a[max-1]));
  test_stack_char_full(&s, a[max-1], max);
  test_stack_char_overflow(&s, a[max-1], max);
  assert(*stack_char_pop(&s) == a[max-1]);

  if (max > 1)
  {
    // Incrementally test stack state and pop off data, until empty.
    for (size_t i = max-2; i < max; i--)
    {
      test_stack_char_half(&s, a[i], i+1);
      assert(*stack_char_pop(&s) == a[i]);
    }
  }

  // Test and destroy empty stack.
  test_stack_char_empty(&s);
  test_stack_char_underflow(&s);
  stack_char_destroy(&s);

  // Test destroyed stack.
  test_stack_char_destroyed_overflow_underflow(&s);
}

static void test_stack_char_one()
{
  char a[] = {'H'};
  size_t max = sizeof a / sizeof *a;
  test_stack_char_complete(a, max);
}

static void test_stack_char_two()
{
  char a[] = {'H', 'J'};
  size_t max = sizeof a / sizeof *a;
  test_stack_char_complete(a, max);
}

static void test_stack_char_five()
{
  char a[] = {'H', 'J', 'K', 'L', ';'};
  size_t max = sizeof a / sizeof *a;
  test_stack_char_complete(a, max);
}

static void test_stack_char_array_of_overflows()
{
  char a[] = {OVERFLOW, OVERFLOW, OVERFLOW, OVERFLOW, OVERFLOW};
  size_t max = sizeof a / sizeof *a;
  test_stack_char_complete(a, max);
}

static void test_stack_char_array_of_underflows()
{
  char a[] = {UNDERFLOW, UNDERFLOW, UNDERFLOW, UNDERFLOW, UNDERFLOW};
  size_t max = sizeof a / sizeof *a;
  test_stack_char_complete(a, max);
}

static void test_stack_char_half_destroyed()
// Test destruction of non-empty stack.
{
  stack_char s = stack_char_create(2);
  stack_char_push(&s, 'Q');
  stack_char_destroy(&s);
  test_stack_char_destroyed_overflow_underflow(&s);
}

int main()
{
  run_test(test_stack_char_one);
  run_test(test_stack_char_two);
  run_test(test_stack_char_five);
  run_test(test_stack_char_array_of_overflows);
  run_test(test_stack_char_array_of_underflows);
  run_test(test_stack_char_half_destroyed);
  printf("\nOK\n\n");
}
