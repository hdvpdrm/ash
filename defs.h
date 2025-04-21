#ifndef DEFS_H
#define DEFS_H

//error definitions
#define ASH_MALLOC_FAILURE  -1
#define ASH_INPUT_FAILURE   -2
#define ASH_UNISTD_FAILURE  -3
#define ASH_NULL_POINTER    -4
#define ASH_UNKNOWN_COMMAND -5
#define ASH_INCORRECT_ARG_NUMBER -6
#define ASH_COMMAND_FAILURE -7
#define ASH_EXIT_SUCCESS     1
#define ASH_CLEAR            2 //restore cursor position

//redifine this macro if it's required, since it's already standard macro
#ifndef OK
#define OK 0
#endif

//constants
#define ASH_MAX_LENGTH 512
#endif
