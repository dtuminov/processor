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

int main(const int argc, const char* argv[]){
    FILE *file = fopen("files/binar.myexe", "r");
    processor *cpu = allocator();
    int cur_val = 0;
    if(cpu->stack == NULL)
       return -1;
    if (file == NULL) {
        printf("Не удалось открыть файл"); // создать обработчик открытия фала
        getchar();
        return -1;
    }
    while(1 == fread(&cur_val, sizeof(int),1, file)) {
        if (cur_val == Push) {
            int value = 0;
            fread(&value, sizeof(value),1, file);
            push(cpu->stack, value);
        } 
        else if(cur_val == Push_reg) {
            int reg_name = 0;
            fread(&reg_name, sizeof(int),1, file);
            push_reg(cpu, cpu->stack, reg_name);
        }
        else if(cur_val == Pop) {
            int reg_name = 0;
            fread(&reg_name, sizeof(int),1, file);
            int val = pop(cpu->stack);
            pop_reg(cpu, reg_name, val);
            printf("oleg\n");
        }
        else if(cur_val == Mov_val){
            int reg_name = 0, value = 0;
            fread(&reg_name, sizeof(reg_name),1, file);
            fread(&value, sizeof(value),1, file);
            mov_val(cpu, reg_name, value);
        }
        else if(cur_val == Mov_reg){
            int firstReg = 0, secondReg = 0;
            fread(&firstReg, sizeof(firstReg),1, file);
            fread(&secondReg, sizeof(secondReg),1, file);
            mov_reg(cpu, firstReg, secondReg);
        }
    }
    
    print_status(cpu);
    diallocator(cpu);
    fclose(file);
    return 0;
}

ERRORS mov_reg(processor * cpu, int a, int b){
    if(cpu == NULL) {return not_valid_function;}
    if(a == ax){ 
        if(b == bx) cpu->ax = cpu->bx;
        else if(b == cx) cpu->ax = cpu->cx;
        else if(b == dx) cpu->ax = cpu->dx;
    }
    else if(a == bx){ 
        if(b == ax) cpu->bx = cpu->ax;
        else if(b == cx) cpu->bx = cpu->cx;
        else if(b == dx) cpu->bx = cpu->dx;
     }
    else if(a == cx){  
        if(b == bx) cpu->cx = cpu->bx;
        else if(b == ax) cpu->cx = cpu->ax;
        else if(b == dx) cpu->cx = cpu->dx;
     }
    else if(a == dx){ 
        if(b == bx) cpu->dx = cpu->bx;
        else if(b == ax) cpu->dx = cpu->ax;
        else if(b == cx) cpu->dx = cpu->cx;
    }
    return ok;
}

ERRORS mov_val(processor * cpu, int a, int b){
    if(cpu == NULL) 
        return not_valid_function;
    if(a == ax){ cpu->ax = b; return ok; }
    else if(a == bx){ cpu->bx = b; return ok; }
    else if(a == cx){ cpu->cx = b; return ok; }
    else if(a == dx){ cpu->dx = b; }
    return ok;
}

/**
 * @brief 
 * 
 * @param stack 
 * @param reg_name 
 * @return ERRORS 
 */

ERRORS push_reg(processor* CPU, stack* stack, int reg_name){
    if(stack == NULL || CPU == NULL)
        return empty_stack;
    if(reg_name == ax){ push(stack, CPU->ax); return ok; }
    else if(reg_name == bx){ push(stack, CPU->bx); return ok; }
    else if(reg_name == cx){ push(stack, CPU->cx); return ok; }
    else if(reg_name == dx){ push(stack, CPU->dx); }
    return ok;
}

ERRORS pop_reg(processor *cpu, int reg_name, int data){
    if(cpu == NULL) { return not_valid_function;}
    if(reg_name == ax){cpu->ax = data; }
    else if(reg_name == bx){ cpu->bx = data; }
    else if(reg_name == cx){ cpu->cx = data; }
    else if(reg_name == dx){ cpu->dx = data; }
    printf("ax = %d\nbx = %d\ncx = %d\ndx = %d\n\n",cpu->ax,cpu->bx,cpu->cx,cpu->dx);
    return ok;
}

processor * allocator(){
    processor *cpu = (processor*)calloc(1, sizeof(cpu));
    cpu->stack = stack_init();
    cpu->ax=0, cpu->bx=0, cpu->cx =0, cpu->dx =0;
    return cpu;
}

void diallocator(processor* cpu){
    free(cpu->stack->arr);
    free(cpu->stack);
    free(cpu);
}

void print_status(processor* cpu){
    printf("---cpu---\n");
    printf("ax = %d\nbx = %d\ncx = %d\ndx = %d\n\n",cpu->ax,cpu->bx,cpu->cx,cpu->dx);
    for (size_t i = 0; i < cpu->stack->iter; i++)
    {
        printf("stack[%d] = %d\n", i, cpu->stack->arr[i]);
    }
}