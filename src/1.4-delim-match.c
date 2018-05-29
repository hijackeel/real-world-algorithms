#include "1.4-delim-match-lib.h"
#include <stdio.h>
#include <string.h>

#define BUFFER_SIZE 500

int main()
{
  char buffer[BUFFER_SIZE];
  while(1)
  {
    // Prompt for input.
    printf("> ");
    fgets(buffer, BUFFER_SIZE, stdin);

    // Convert newline at end of user input to null terminator.
    strtok(buffer, "\n");

    // Display output.
    printf("%s\n\n", delim_match_str(delim_match(buffer, strlen(buffer))));
  }
}
