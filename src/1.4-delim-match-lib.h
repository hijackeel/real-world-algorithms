#include <stddef.h>

typedef enum
{
  MATCHED_CORRECT = 0,
  MATCHED_INCORRECT = 1,
  UNMATCHED = 2
} delim_match_return;

int delim_match(char *input, size_t max);
// Input: string containing open/close delimiters (any of ()[]{}), and length.
// Output: return code indicating if/how delimiters match. See test cases.

char * delim_match_str(int result);
// Input: return code from delim_match.
// Output: human-friendly string describing return code.
