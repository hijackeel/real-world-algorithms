#include "1.2-stock-span-lib.h"
#include "run_test.h"
#include <assert.h>

typedef void (*stock_span_function)(double*, size_t*, size_t);

static void test_stock_span_function(stock_span_function f)
{
  static double quotes[] = {7.0, 11.0, 8.0, 6.0, 3.0, 8.0, 9.0};
  static size_t length = sizeof quotes / sizeof *quotes;
  size_t spans[7];
  f(quotes, spans, length);
  static size_t output[] = {1, 2, 1, 1, 1, 4, 5};
  for (size_t i=0; i<length; i++)
  {
    assert(spans[i] == output[i]);
  }
}

static void test_stock_span_stack()
{
  test_stock_span_function(&stock_span_stack);
}

static void test_stock_span_simple()
{
  test_stock_span_function(&stock_span_simple);
}

int main()
{
  run_test(test_stock_span_stack);
  run_test(test_stock_span_simple);
  printf("\nOK\n\n");
}
