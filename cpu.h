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

int main(const int argc, const char* argv[]);
ERRORS mov_reg(int a, int b);
ERRORS mov_val(int a, int b);
ERRORS mov_opData();
ERRORS _push(stack* stack, int info);
double _pop(stack* stack);
ERRORS push_reg(stack* stack, int reg_name);

#endif