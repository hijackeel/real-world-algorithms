#include "1.2-stock-span-lib.h"
#include "run_test.h"
#include <assert.h>

static void test_stock_span()
{
  static int quotes[] = {7, 11, 8, 6, 3, 8, 9};
  static size_t length = sizeof quotes / sizeof *quotes;
  size_t spans[length];
  stock_span(quotes, spans, length);
  static size_t output[] = {1, 2, 1, 1, 1, 4, 5};
  for (size_t i=0; i<length; i++)
  {
    assert(spans[i] == output[i]);
  }
}

int main()
{
  run_test(test_stock_span);
  printf("\nOK\n\n");
}
