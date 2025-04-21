#include<stddef.h>
#include"command_invoker.h"

int main(int argc, char** argv)
{
    char* in;
    char** tokens;
    size_t size = 0;

    get_cwd();
    get_current_user();
    
    short result = OK;
    while (1)
    {
        print_greetings();
        result = read_line(&in, &size);
        if (result == ASH_EXIT_SUCCESS)
            break;

        result = split_input(&in, &tokens, &size);
        result = invoke_command(&tokens, size);

        if (result == ASH_COMMAND_FAILURE)
        {
            printf("\nash: %s\n", ash_error_buf);
        }
        else if (result == ASH_UNKNOWN_COMMAND)
        {
            printf("\nash: unknown command: %s\n", tokens[0]);
        }
        else if (result == ASH_INCORRECT_ARG_NUMBER)
        {
            printf("\nash: %s\n", ash_error_buf);
        }
        else if (result == ASH_NULL_POINTER)
        {
            printf("\nash: empty\n");
        }

        for (size_t i = 0; i < size; ++i)
	  free(tokens[i]);
        free(tokens);

        if (result == ASH_EXIT_SUCCESS)
            break;

        if (result != ASH_CLEAR)
        {
            // Move down
            printf("\n");
        }
    }

    return 0;
}
