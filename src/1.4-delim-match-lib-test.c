#include "1.4-delim-match-lib.h"
#include "run_test.h"
#include <string.h>
#include <assert.h>

static void test_delim_match(char *input, int output)
{
  assert(delim_match(input, strlen(input)) == output);
}

static void test_delim_match_correct()
{
  char input[] = "(){[](){}}";
  int output = MATCHED_CORRECT;
  test_delim_match(input, output);
}

static void test_delim_match_incorrect()
{
  char input[] = "(}";
  int output = MATCHED_INCORRECT;
  test_delim_match(input, output);
}

static void test_delim_match_unmatched()
{
  char input[] = "(()";
  int output = UNMATCHED;
  test_delim_match(input, output);
}

int main()
{
  run_test(test_delim_match_correct);
  run_test(test_delim_match_incorrect);
  run_test(test_delim_match_unmatched);
  printf("\nOK\n\n");
}
