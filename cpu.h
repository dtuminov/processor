#ifndef CPU_H
#define CPU_H
#define JUMPED 1
#define NJUMPED -1
#define BinarPath "files/binar.myexe"
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
typedef struct CPU {
    stack* stack;
    int ax, bx, cx, dx;
    int status;
} CPU;
int main(const int argc, const char* argv[]);
CPU* allocator();
void print_status(CPU* cpu);
void diallocator(CPU* cpu);
void cmp(CPU* cpu, int firstReg,int secondReg);
void mov_reg(CPU * cpu, int a, int b);
void mov_val(CPU * cpu, int a, int b);
void mov_opData();
void add(CPU * cpu, int firstReg, int secondReg);
void push_reg(CPU* CPU, stack* stack, int reg_name);
void pop_reg(CPU* cpu, int reg_name);
int ja(CPU* cpu);
int jmp(CPU* cpu);
void call(CPU *cpu, int i);
void goto_label();
#endif