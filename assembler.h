#ifndef PROCESS_H
#define PROCESS_H

#define printf_warning printf("Warning in function %s:%d\n", __FUNCTION__ ,__LINE__);
#define SWRITE printf("-[function %s writed] \n", str); 

/**
 * @file process.h
 * @author your name (you@domain.com)
 * @brief 
 * @version 0.1
 * @date 2021-12-18
 * 
 * @copyright Copyright (c) 2021
 * 
 */
 
#include "stack/stack.h"
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>
#include <conio.h>

typedef struct pair {
    char* str;
    int iter;
} pair;

/**
 * @brief instructions that the processor executes
 */

typedef enum CPU_functions {
    Push = 1, Push_reg,
    Pop, Pop_reg,
    Stack_destroy, Stack_init,
    Mov_val, Mov_reg, Top,
    Add, Sub,
    Mult, Div,
    ax, bx, cx, dx,
    Exit
} CPU_functions;

extern const char* cpu_functions[];
extern struct pair* marks;

struct pair* make_pair();
void delete_pair(struct pair* pair);
void create_binar(FILE* file);
void devide_lines(char** array, size_t length);
size_t Get_reg_name(char * val);

#endif