#include"util.h"


short expand_path(const char* input_path, char* output_path)
{
    wordexp_t p;
    int ret;

    ret = wordexp(input_path, &p, 0);
    if (ret != 0)
      {
        strcpy(ash_error_buf, "Failed to expand path!");
        return ASH_COMMAND_FAILURE;
      }

    if (p.we_wordc != 1)
      {
        strcpy(ash_error_buf, "Path expansion resulted in multiple words!");
        wordfree(&p);
        return ASH_COMMAND_FAILURE;
      }

    strncpy(output_path, p.we_wordv[0], ASH_MAX_LENGTH - 1);
    output_path[ASH_MAX_LENGTH - 1] = '\0';

    wordfree(&p);

    return OK;
}

short get_cwd(void)
{
    if (getcwd(cwd, PATH_MAX) == NULL)
    {
        return ASH_UNISTD_FAILURE;
    }

    struct passwd *pw = getpwuid(getuid());
    if (pw == NULL)
    {
        return ASH_UNISTD_FAILURE;
    }

    const char *homedir = pw->pw_dir;
    size_t homedir_len = strlen(homedir);

    if (strcmp(cwd, homedir) == 0)
    {
        strcpy(cwd, "~");
    }
    else if (strncmp(cwd, homedir, homedir_len) == 0 && cwd[homedir_len] == '/')
    {
        memmove(cwd + 1, cwd + homedir_len, strlen(cwd) - homedir_len + 1);
        cwd[0] = '~';
    }

    return OK;
}
short get_current_user(void)
{ 
  username = getlogin();
  if (username == NULL) 
    {
      struct passwd *pw = getpwuid(getuid());
      if (pw != NULL) 
        {
	  username = pw->pw_name;
        } 
      else 
        {
	  perror("getpwuid() error");
	  return ASH_UNISTD_FAILURE;
        }
    }
  return OK;
}
