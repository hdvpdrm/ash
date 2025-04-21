#include<stddef.h>
#include<ncurses.h>
#include"command_invoker.h"

int main(int argc, char** argv)
{
    prepare_interface();
    
    char* in;
    char** tokens;    
    size_t size = 0;

    short result = OK;
    while(1)
    {
        print_greetings();
        result = read_line(&in,&size);
	if(result == ASH_EXIT_SUCCESS)break;
	
	result = split_input(&in,&tokens,&size);
	result = invoke_command(&tokens,size);              

	if(result == ASH_COMMAND_FAILURE)
	  {
	    printw("\nash: %s", ash_error_buf);
	  }
	else if(result == ASH_UNKNOWN_COMMAND)
	  {
	    printw("\nash: unknown command: %s",tokens[0]);
	  }
	else if(result == ASH_INCORRECT_ARG_NUMBER)
	  {
	    printw("\nash: %s",ash_error_buf);
	  }
	else if(result == ASH_NULL_POINTER)
	  {
	    printw("\nash : fuck");
	  }

	for(size_t i = 0;i<size;++i)free(tokens[i]);
	free(tokens);

	
	if(result == ASH_EXIT_SUCCESS)break;


	
	//move down
        getyx(stdscr,curs_y,curs_x);
	move(curs_y+1,0);
	
    }
 
    refresh();
    endwin();
    return 0;
}
