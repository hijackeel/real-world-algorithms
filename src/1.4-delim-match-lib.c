#include "1.4-delim-match-lib.h"
#include "1.1-array-stack-char-lib.h"
#include <string.h>

char * delim_match_str(int result)
{
  switch (result)
  {
    case MATCHED_CORRECT: return "Correct match!";
    case MATCHED_INCORRECT: return "Incorrect match!";
    case UNMATCHED: return "Unmatched!";
    default: return "Undefined!";
  }
}

int delim_match(char *input, size_t max)
{
  stack_char s = stack_char_create(max);

  for (size_t i=0; i<strlen(input); i++)
  {
    if (input[i] == '(' || input[i] == '[' || input[i] == '{')
    {
      stack_char_push(&s, input[i]);
    }
    else if
    (
      (input[i] == ')' && *stack_char_top(&s) == '(') ||
      (input[i] == ']' && *stack_char_top(&s) == '[') ||
      (input[i] == '}' && *stack_char_top(&s) == '{')
    )
    {
      stack_char_pop(&s);
    }
    else if
    (
      (input[i] == ')' && *stack_char_top(&s) != '(') ||
      (input[i] == ']' && *stack_char_top(&s) != '[') ||
      (input[i] == '}' && *stack_char_top(&s) != '{')
    )
    {
      return MATCHED_INCORRECT;
    }
  }

  int result = stack_char_empty(&s) ? MATCHED_CORRECT : UNMATCHED;
  stack_char_destroy(&s);
  return result;
}
