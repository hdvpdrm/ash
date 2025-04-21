#ifndef UTIL_H
#define UTIL_H
#include <wordexp.h>
#include<pwd.h>
#include<unistd.h>
#include<stdio.h>
#include"defs.h"
#include"state.h"

extern short get_cwd(void);
extern short get_current_user(void);
extern short expand_path(const char* input_path, char* output_path);


#endif
