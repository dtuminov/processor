/**
 * @file cpu.c
 * @author your name (you@domain.com)
 * @brief 
 * @version 0.1
 * @date 2022-03-08
 * 
 * @copyright Copyright (c) 2022
 * 
 */

#include "cpu.h"
#include "assembler.h"
#include <stdio.h>
#include <string.h>
#include "stack/stack.h"

//fz погуглить
int main(const int argc, const char* argv[]){
    FILE *file = fopen("files/binar.myexe", "r");
    stack*stack = stack_init();
    int cur_val = 0;
    if(stack == NULL)
       return -1;
    if (file == NULL) {
        printf("Не удалось открыть файл");
        getchar();
        return -1;
    }
    fseek(file, 0, SEEK_END);
    size_t file_bytes_size = ftell(file);
    fseek(file, 0, SEEK_SET);
    while(1 == fread(&cur_val, sizeof(int),1, file)) {
        if (cur_val == Push)
        {
            //организация кода
            double value = 0;
            fread(&value, sizeof(int),1, file);
            push(stack, value);
        } 
        else if(cur_val == Push_reg){
            int reg_name = 0;
            fread(&reg_name, sizeof(int),1, file);
            printf("%d\n\n", reg_name);
            push_reg(stack, reg_name);
        }
    }
    printf("stack:\n");
    for (size_t i = 0; i < stack->length; i++)
    {
        //printf("%lf\n", stack->arr[0]);
        printf("stack[%d] = %lf\n", i, stack->arr[i]);
    }
    
    stack_destroy(stack);
    fclose(file);
    return 0;
}

ERRORS mov_reg(int a, int b){
    processor cpu;
    return ok;
}

/**
 * @brief 
 * 
 * @param stack 
 * @param reg_name 
 * @return ERRORS 
 */

ERRORS push_reg(stack* stack, int reg_name){
    processor CPU;
    CPU.ax = 3.6;
    if(stack == NULL)
        return empty_stack;
    if(reg_name == ax){
        push(stack, CPU.ax);
        return ok;
    }
    else if(reg_name == bx){
        push(stack, CPU.bx);
        return ok;
    }
    else if(reg_name == cx){
        push(stack, CPU.cx);
        return ok;
    }
    else{
        push(stack, CPU.dx);
    }
    return ok;
}
