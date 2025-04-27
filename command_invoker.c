#include"command_invoker.h"

CommandPtr commands[] =
  {
    &cd,
    &quit
  };


short cd(char** tokens, size_t size)
{
  if(size != 2)
    {
      strcpy(ash_error_buf,"cd command suppose to have 1 argument only!");
      return ASH_INCORRECT_ARG_NUMBER;
    }
  if (!tokens[1])
    {
      strcpy(ash_error_buf, "Argument for cd command is NULL!");
      return ASH_COMMAND_FAILURE;
    }

  char expanded_path[ASH_MAX_LENGTH];
  if(expand_path(tokens[1],expanded_path) != OK) return ASH_COMMAND_FAILURE;
  
  if(chdir(expanded_path) == 0)
    {
      get_cwd();
    }
  else
    {
      strcpy(ash_error_buf,"failed to change directory!");
      return ASH_COMMAND_FAILURE;
    }
  
  return OK;
}
short quit(char** tokens, size_t size)
{
  if(size != 1)
    {
      strcpy(ash_error_buf,"exit command has no arguments!");
      return ASH_COMMAND_FAILURE;
    }
  return ASH_EXIT_SUCCESS;
}
short launch(char** tokens, size_t size)
{
  if (!tokens || size == 0)
    {
      return ASH_NULL_POINTER;
    }
  pid_t pid,wpid;
  int status;

  tokens[size] = NULL;
  pid = fork();
  if (pid == 0)
    {
      // Child process
      if (execvp(tokens[0], tokens) == -1)
	{
	  perror("ash: execvp");
	}
      exit(EXIT_FAILURE);
    }
  else if (pid < 0)
    {
      // Fork failed
      perror("ash: fork");
      return ASH_NULL_POINTER;
    }
  else
    {
      // Parent process
      do
	{
	  wpid = waitpid(pid, &status, WUNTRACED);
	}
      while (!WIFEXITED(status) && !WIFSIGNALED(status));
    }
  return OK;
}
short launch_pipeline(char** tokens, size_t size)
{

}

short split_input(char** input, char*** output, size_t* size)
{
    if (!input || !*input) return ASH_NULL_POINTER;

    size_t count = 0;
    size_t capacity = 1; 

    *output = (char**)malloc(capacity * sizeof(char*));
    if (!*output) return ASH_MALLOC_FAILURE;

    char* token = strtok(*input, " ");
    while (token != NULL)
      {
        if (count >= capacity)
	  {
            capacity *= 2;
            char** temp = (char**)realloc(*output, capacity * sizeof(char*));
            if (!temp)
	      {
                for (size_t i = 0; i < count; i++)
		  {
                    free((*output)[i]);
		  }
		
                free(*output);
                return ASH_MALLOC_FAILURE;
	      }
            *output = temp;
	  }
        (*output)[count] = strdup(token);
        if (!(*output)[count])
	  {
            for (size_t i = 0; i < count; i++)
	      {
                free((*output)[i]);
	      }
            free(*output);
            return ASH_MALLOC_FAILURE;
	  }
        count++;
        token = strtok(NULL, " ");
      }
    
    *size = count;
    return OK;
}
short invoke_command(char*** tokens,size_t size)
{
  if(!tokens || size == 0)
    return ASH_NULL_POINTER; 
  
  char** arr = *tokens;
  char* head = arr[0];
  CommandPtr command = GET_COMMAND(head);
  if(command != NULL)
    {
      return command(arr,size);
    }
  else if(is_pipeline(arr,size))
    {
    }  
  else if(strcmp(head,"clear") == 0)
    {
      launch(arr,size);
      return ASH_CLEAR;
    }

  return launch(arr,size);
}
bool is_pipeline(char** tokens, size_t size)
{
  for(size_t i = 0;i<size;++i)
    {
      if(strcmp(tokens[i],"|") == 0) return true;
    }
  return false;
}
