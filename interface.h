#ifndef INTERFACE_H
#define INTERFACE_H
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<ncurses.h>
#include<limits.h>
#include"defs.h"
#include"util.h"
#include"state.h"


extern void print_greetings(void);
extern short read_line(char** in, size_t* size);

#endif
