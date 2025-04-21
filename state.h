#ifndef STATE_H
#define STATE_H
#include<string.h>
#include<limits.h>
#include"defs.h"

extern int curs_y,curs_x;
extern char cwd[PATH_MAX];
extern char* username;

extern char ash_error_buf[ASH_MAX_LENGTH];

#endif
