#include "1.3-rpn-lib.h"
#include "run_test.h"
#include <string.h>
#include <stdlib.h>
#include <assert.h>

static void test_rpn(char *input, double output)
{
  size_t num_operands = 0;
  char *input_copy = malloc(strlen(input)+1);
  strcpy(input_copy, input);
  for (char *tok = strtok(input_copy, " "); tok; tok = strtok(NULL, " "))
  {
    if (tok[0]!='*' && tok[0]!='+' && tok[0]!='-' && tok[0]!='/')
    {
      num_operands++;
    }
  }
  free(input_copy);
  assert(rpn_calc(input, num_operands) == output);
}

static void test_rpn_int()
{
  char input[] = "1 2 3 * + 2 - 2 /";
  double output = ((1.0+(2.0*3.0))-2.0)/2.0;
  test_rpn(input, output);
}

static void test_rpn_float()
{
  char input[] = "1.1 2.2 3.3 * + 9.99 - 2.5 /";
  double output = ((1.1+(2.2*3.3))-9.99)/2.5;
  test_rpn(input, output);
}

int main()
{
  run_test(test_rpn_int);
  run_test(test_rpn_float);
  printf("\nOK\n\n");
}
