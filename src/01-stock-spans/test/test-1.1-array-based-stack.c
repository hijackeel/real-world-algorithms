#include "../1.1-array-based-stack.h"
#include <assert.h>
#include <stddef.h>

void test_stack_empty(stack *s)
// Test state of empty stack.
{
  assert(stack_top(s) == UNDERFLOW);
  assert(stack_size(s) == 0);
  assert(stack_empty(s));
  assert(!stack_full(s));
}

void test_stack_empty_pop(stack *s)
// Test that attempting to pop from empty stack has no side effects.
{
  assert(stack_pop(s) == UNDERFLOW);
  test_stack_empty(s);
}

void test_stack_half(stack *s, int top, int size)
// Test state of half-full stack (not empty or full).
{
  assert(stack_top(s) == top);
  assert(stack_size(s) == size);
  assert(!stack_empty(s));
  assert(!stack_full(s));
}

void test_stack_full(stack *s, int top, int size)
// Test state of full stack.
{
  assert(stack_top(s) == top);
  assert(stack_size(s) == size);
  assert(!stack_empty(s));
  assert(stack_full(s));
}

void test_stack_full_push(stack *s, int top, int size)
// Test that attempting to push onto full stack has no side effects.
{
  assert(stack_push(s, 42) == OVERFLOW);
  test_stack_full(s, top, size);
}

void test_stack_complete(int *a, size_t max)
// Pass in an array of data to copy to stack, and max number of elements.
{
  // Create and test empty stack.
  stack s = stack_create(max);
  test_stack_empty(&s);
  test_stack_empty_pop(&s);

  // Incrementally push data onto stack and test state, except for last value.
  for (size_t i = 0; i <= max-2; i++) {
    assert(!stack_push(&s, a[i]));
    test_stack_half(&s, a[i], i+1);
  }

  // Push last value onto stack, test state, and pop off again.
  assert(!stack_push(&s, a[max-1]));
  test_stack_full(&s, a[max-1], max);
  test_stack_full_push(&s, a[max-1], max);
  assert(stack_pop(&s) == a[max-1]);

  // Incrementally test stack state and pop off data, until empty.
  for (size_t i = max-2; i < max; i--) {
    test_stack_half(&s, a[i], i+1);
    assert(stack_pop(&s) == a[i]);
  }

  // Test and destroy empty stack.
  test_stack_empty(&s);
  test_stack_empty_pop(&s);
  stack_destroy(&s);
}

void test_stack_two()
{
  int a[] = {20, 37};
  size_t max = sizeof a / sizeof *a;
  test_stack_complete(a, max);
}

void test_stack_five()
{
  int a[] = {20, 37, 99, 11, 1066};
  size_t max = sizeof a / sizeof *a;
  test_stack_complete(a, max);
}

void test_stack_negative_twos()
{
  int a[] = {-2, -2, -2, -2, -2};
  size_t max = sizeof a / sizeof *a;
  test_stack_complete(a, max);
}

int main (int argc, char **argv)
{
  test_stack_two();
  test_stack_five();
  test_stack_negative_twos();
}
