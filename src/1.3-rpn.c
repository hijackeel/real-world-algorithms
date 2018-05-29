#include "1.3-rpn-lib.h"
#include <stdio.h>
#include <string.h>

#define BUFFER_SIZE 500

int main()
{
  char buffer[BUFFER_SIZE];
  char buffer_copy[BUFFER_SIZE];
  while(1)
  {
    // Prompt for input.
    printf("> ");
    fgets(buffer, BUFFER_SIZE, stdin);

    // Convert newline at end of user input to null terminator.
    strtok(buffer, "\n");

    // Calculate number of operands.
    strcpy(buffer_copy, buffer);
    size_t num_operands = 0;
    for (char *tok = strtok(buffer_copy, " "); tok; tok = strtok(NULL, " "))
    {
      if (tok[0]!='*' && tok[0]!='+' && tok[0]!='-' && tok[0]!='/')
      {
        num_operands++;
      }
    }

    // Display output.
    printf("%f\n\n", rpn_calc(buffer, num_operands));
  }
}
