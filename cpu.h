#ifndef CPU_H
#define CPU_H

#define JUMPED 1
#define NJUMPED -1

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
    int status;
} processor;

int main(const int argc, const char* argv[]);
processor* allocator();
void print_status(processor* cpu);
void diallocator(processor* cpu);
void cmp(processor* cpu, int firstReg,int secondReg);
void mov_reg(processor * cpu, int a, int b);
void mov_val(processor * cpu, int a, int b);
void mov_opData();
void push_reg(processor* CPU, stack* stack, int reg_name);
void pop_reg(processor* cpu, int reg_name, int data);
int ja(processor* cpu);
int jmp(processor* cpu);
void goto_label();
#endif