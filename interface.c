#include"interface.h"

void print_greetings(void)
{
  printf("%s:%s$ ", username, cwd);
  fflush(stdout); 
}
short read_line(char** in, size_t* size)
{
  *in = (char*)malloc(ASH_MAX_LENGTH);
  if (!*in) return ASH_MALLOC_FAILURE;
  
  int ch;
  size_t index = 0;
  *size = ASH_MAX_LENGTH;
  
  while ((ch = getchar()) != '\n' && ch != EOF)
    {
      if (ch == 3)
	{ // Handle Ctrl+C
	  free(*in);
	  return ASH_EXIT_SUCCESS;
        }

      if (ch == 127 || ch == 8)
	  { // Handle backspace
            if (index > 0)
	      {
                printf("\b \b"); // Move cursor back and overwrite the character
                (*in)[--index] = '\0'; // Correctly handle the input buffer
	      }
        }
      else if (ch >= 32 && ch <= 126)
	{ // Handle printable characters
            if (index < *size - 1)
	      {
                (*in)[index++] = ch;
                putchar(ch);
                fflush(stdout);
	      }
	    else
	      {
                *size += ASH_MAX_LENGTH;
                *in = realloc(*in, *size);
                if (!*in) return ASH_MALLOC_FAILURE;
		
                (*in)[index++] = ch;
                putchar(ch);
                fflush(stdout);
	      }
        }
    }
  
  (*in)[index] = '\0';
  putchar('\n'); // Move to the next line after reading input
  fflush(stdout);
  
  return OK;
}
