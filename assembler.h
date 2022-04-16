#ifndef PROCESS_H
#define PROCESS_H

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

/**
 * @brief error codes returned by functions
 */

typedef enum ERRORS{
    ok,
    openning_file_error,    
    not_valid_function,
    empty_stack
} ERRORS;




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

ERRORS create_binar(FILE* file);
void devide_lines(char** array, size_t length);
size_t Get_reg_name(char * val);

#endif