#include"interface.h"

void print_greetings(void)
{
    printw("%s:%s$",username,cwd);
}
short read_line(char** in, size_t* size)
{
    *in = (char*)malloc(ASH_MAX_LENGTH);
    if (!*in) return ASH_MALLOC_FAILURE;

    int ch;
    int index = 0;
    *size = ASH_MAX_LENGTH;

    while ((ch = getch()) != '\n')
      {
        if (ch == 3) return ASH_EXIT_SUCCESS; // Handle Ctrl+C

        if (ch == KEY_BACKSPACE ||
            ch == 127           ||
            ch == 8             ||
            ch == KEY_DC)
	  {
            if (index > 0)
	      {
                int curs_y, curs_x;
                getyx(stdscr, curs_y, curs_x);
                move(curs_y, curs_x - 1);
                addch(' ');
                move(curs_y, curs_x - 1);
                (*in)[--index] = '\0'; // Correctly handle the input buffer
            }
        }
	else if (ch >= 32 && ch <= 126)
	  {
            if (index < *size - 1)
	      {
                (*in)[index++] = ch;
                printw("%c", ch);
                refresh();
            }
	    else
	      {
                *size += ASH_MAX_LENGTH;
                *in = realloc(*in, *size);
                if (!*in) return ASH_MALLOC_FAILURE;

                (*in)[index++] = ch;
                printw("%c", ch);
                refresh();
            }
        }
    }

    (*in)[index] = '\0';

    return OK;
}
