#ifndef COMMAND_INVOKER_H
#define COMMAND_INVOKER_H
#include<sys/wait.h>
#include"interface.h"
#include"util.h"
#include"state.h"

typedef short (*CommandPtr)(char**,size_t size);
extern CommandPtr commands[];

#define GET_COMMAND(n)\
  ( \
    strcmp(n,"cd")   == 0? commands[0]:\
    strcmp(n,"exit") == 0? commands[1]: \
    NULL \
    )\


extern short cd(char** tokens, size_t size);
extern short quit(char** tokens, size_t size);

extern short launch(char** tokens, size_t size);

extern short split_input(char** input,char*** output, size_t* size);
extern short invoke_command(char*** tokens,size_t size);

#endif
