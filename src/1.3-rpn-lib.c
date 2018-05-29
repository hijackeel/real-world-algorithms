#include "1.3-rpn-lib.h"
#include "1.1-array-stack-double-lib.h"
#include <string.h>
#include <stdlib.h>

static double mul(double operand1, double operand2){return operand1 * operand2;}
static double add(double operand1, double operand2){return operand1 + operand2;}
static double sub(double operand1, double operand2){return operand1 - operand2;}
static double dvd(double operand1, double operand2){return operand1 / operand2;}
static double (*op[])(double, double) = {mul, add, NULL, sub, NULL, dvd};
// ascii jump table:                     42=* 43=+  44=, 45=-  46=. 47=/

double rpn_calc(char *input, size_t max)
{
  stack_double s = stack_double_create(max);

  double operand1, operand2;
  for (char *token = strtok(input, " "); token; token = strtok(NULL, " "))
  {
    if (token[0]=='*' || token[0]=='+' || token[0]=='-' || token[0]=='/')
    {
      operand2 = *stack_double_pop(&s);
      operand1 = *stack_double_pop(&s);
      stack_double_push(&s, (*op[token[0]-42])(operand1, operand2));
    }
    else
    {
      stack_double_push(&s, atof(token));
    }
  }

  double result = *stack_double_top(&s);
  stack_double_destroy(&s);
  return result;
}
