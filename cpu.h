#ifndef CPU_H
#define CPU_H

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <assert.h>
#include <string.h>
#include <stdint.h>
#include "stack/stack.h"
#include "assembler.h"
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


/**
 * @brief the stack of cpu
 */

typedef struct processor {
    stack* stack;
    int ax, bx, cx, dx;
} processor;

int main(const int argc, const char* argv[]);
processor* allocator();
void print_status(processor* cpu);
void diallocator(processor* cpu);
ERRORS mov_reg(processor * cpu, int a, int b);
ERRORS mov_val(processor * cpu, int a, int b);
ERRORS mov_opData();
ERRORS push_reg(processor* CPU, stack* stack, int reg_name);
ERRORS pop_reg(processor* cpu, int reg_name, int data);

#endif