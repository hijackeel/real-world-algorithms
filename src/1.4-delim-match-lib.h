#include <stddef.h>

typedef enum
{
  MATCHED_CORRECT = 0,
  MATCHED_INCORRECT = 1,
  UNMATCHED = 2
} delim_match_return;

int delim_match(char *input, size_t max);
