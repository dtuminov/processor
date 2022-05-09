#include "cpu.h"
#include "assembler.h"
#include <stdio.h>
#include <string.h>
#include "stack/stack.h"

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


int main(const int argc, const char* argv[]){
    FILE *file = fopen("files/binar.myexe", "r");
    CPU *cpu = allocator(); int cur_val = 0;
    if (file == NULL) {
        printf_warning;
    }

    fseek(file, 0, SEEK_END);
    size_t file_bytes_size = ftell(file);
    fseek(file, 0, SEEK_SET);

    if(file_bytes_size == 0){
        printf_warning;
    }

    int * bufer = (int*)calloc(sizeof(int), file_bytes_size);
    fread(bufer, sizeof(int),file_bytes_size, file);

    for (size_t i = 0; i < file_bytes_size; i++){
        if (bufer[i] == Push){
            push(cpu->stack, bufer[++i]);
        } 
        else if(bufer[i] == Push_reg){
            push_reg(cpu, cpu->stack, bufer[++i]);
        }
        else if(bufer[i] == Pop){
            pop_reg(cpu, bufer[++i]);
        }
        else if(bufer[i] == Mov_val){
            mov_val(cpu, bufer[++i], bufer[++i]);
        }
        else if(bufer[i] == Mov_reg){
            mov_reg(cpu, bufer[++i], bufer[++i]);
        }
        else if(bufer[i] == Add){
            add(cpu, bufer[++i], bufer[++i]);
        }
        else if(bufer[i] == Cmp){
            cmp(cpu, bufer[++i], bufer[++i]);
        }
        else if(bufer[i] == 18){
            iterLabel = i;
            if (ja(cpu) == JUMPED){
                i = bufer[++i] - 2; // почему блэт минус 2
            }
            else{
                ++i;
            }
        }
        else if( bufer[i] == 19){
            iterLabel = i;
            if (jmp(cpu) == JUMPED) {
                i = bufer[++i] - 3; /// почему - 3
            }
            else{
                ++i;
            }
        }
        else if(bufer[i] == Return){
            i = iterLabel  + 1;
        }
    }
    //closing 
    print_status (cpu);
    diallocator (cpu);
    free (bufer);
    fclose(file);
    return 0;
}

/**
 * @brief 
 * 
 * @param cpu 
 * @param a 
 * @param b 
 */

void mov_reg(CPU * cpu, int a, int b){
    if(cpu == NULL) { printf_warning; exit(errno); }
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
}

/**
 * @brief 
 * 
 * @param cpu 
 * @param a 
 * @param b 
 */

void mov_val(CPU * cpu, int a, int b){
    printf("%d\n%d\n",a,b);
    if(cpu == NULL) { printf_warning; exit(errno); }
    if(b == ax){ 
        cpu->ax = a; 
    }
    else if(b == bx){ cpu->bx = a; }
    else if(b == cx){ cpu->cx = a; }
    else if(b == dx){ cpu->dx = a; }
}

/**
 * @brief 
 * 
 * @param stack 
 * @param reg_name 
 * @return ERRORS 
 */

void push_reg(CPU* CPU, stack* stack, int reg_name){
    if(stack == NULL || CPU == NULL) { printf_warning; exit(errno); }
    if(reg_name == ax){ push(stack, CPU->ax); }
    else if(reg_name == bx){ push(stack, CPU->bx); }
    else if(reg_name == cx){ push(stack, CPU->cx); }
    else if(reg_name == dx){ push(stack, CPU->dx); }
}

/**
 * @brief 
 * 
 * @param cpu 
 * @param reg_name 
 * @param data 
 */

void pop_reg(CPU *cpu, int reg_name){
    if(cpu == NULL){ 
        printf_warning; 
    }
    if(reg_name == ax){
        cpu->ax = pop(cpu->stack);
    }
    else if(reg_name == bx){ 
        cpu->bx = pop(cpu->stack); 
    }
    else if(reg_name == cx){ 
        cpu->cx = pop(cpu->stack); 
    }
    else if(reg_name == dx){ 
        cpu->dx = pop(cpu->stack); 
    }
}

/**
 * @brief 
 * 
 * @return CPU* 
 */

CPU * allocator(){
    CPU *cpu = (CPU*)calloc(1, sizeof(cpu));
    cpu->stack = stack_init();
    cpu->ax=0, cpu->bx=0, cpu->cx =0, cpu->dx =0;
    return cpu;
}

void diallocator(CPU* cpu){
    free(cpu->stack->arr);
    free(cpu->stack);
    free(cpu);
}

void print_status(CPU* cpu){
    printf("---cpu---\n");
    printf("ax = %d\nbx = %d\ncx = %d\ndx = %d\n\n",cpu->ax,cpu->bx,cpu->cx,cpu->dx);
    for (size_t i = 0; i < cpu->stack->iter; i++)
    {
        printf("stack[%d] = %d\n", i, cpu->stack->arr[i]);
    }
}

void cmp(CPU* cpu, int secondReg,int firstReg){
    if (cpu == NULL)
        printf_warning;
    if(firstReg == ax){
        if (secondReg == bx)
        {
            cpu->cx = cpu->ax - cpu->bx;
        }
        else if (secondReg == cx)
        {
            cpu->cx = cpu->ax - cpu->cx;
        }
        else if (secondReg == dx)
        {
            cpu->cx = cpu->ax - cpu->dx;
        }
    }
    else if(firstReg == bx){
        if (secondReg == ax)
        {
            cpu->cx = cpu->bx - cpu->ax;
        }
        else if (secondReg == cx)
        {
            cpu->cx = cpu->bx - cpu->cx;
        }
        else if (secondReg == dx)
        {
            cpu->cx = cpu->bx - cpu->dx;
        }
    }
    else if(firstReg == cx){
        if (secondReg == ax)
        {
            cpu->cx = cpu->cx - cpu->ax;
        }
        else if (secondReg == bx)
        {
            cpu->cx = cpu->cx - cpu->bx;
        }
        else if (secondReg == dx)
        {
            cpu->cx = cpu->cx - cpu->dx;
        }
    }
    else if(firstReg == dx){
        if (secondReg == ax)
        {
            cpu->cx = cpu->dx - cpu->ax;
        }
        else if (secondReg == cx)
        {
            cpu->cx = cpu->dx - cpu->cx;
        }
        else if (secondReg == bx)
        {
            cpu->cx = cpu->dx - cpu->bx;
        }
    }
}

int ja(CPU* cpu){
    if(cpu->cx>0){
        return JUMPED;
    }
    else{
        return NJUMPED;
    }
}
int jmp(CPU* cpu){
    if(cpu->cx<=0){
        return JUMPED;
    }
    else{
        return NJUMPED;
    }
}
void add(CPU * cpu, int secondReg, int firstReg){
    if (cpu == NULL)
        printf_warning;
    if(firstReg == ax){
        if (secondReg == bx)
        {
            cpu->ax = cpu->ax + cpu->bx;
        }
        else if (secondReg == cx)
        {
            cpu->ax = cpu->ax + cpu->cx;
        }
        else if (secondReg == dx)
        {
            cpu->ax = cpu->ax + cpu->dx;
        }
    }
    else if(firstReg == bx){
        if (secondReg == ax)
        {
            cpu->bx = cpu->bx + cpu->ax;
        }
        else if (secondReg == cx)
        {
            cpu->bx = cpu->bx + cpu->cx;
        }
        else if (secondReg == dx)
        {
            cpu->bx = cpu->bx + cpu->dx;
        }
    }
    else if(firstReg == cx){
        if (secondReg == ax)
        {
            cpu->cx = cpu->cx + cpu->ax;
        }
        else if (secondReg == bx)
        {
            cpu->cx = cpu->cx + cpu->bx;
        }
        else if (secondReg == dx)
        {
            cpu->cx = cpu->cx + cpu->dx;
        }
    }
    else if(firstReg == dx){
        if (secondReg == ax)
        {
            cpu->dx = cpu->dx + cpu->ax;
        }
        else if (secondReg == cx)
        {
            cpu->dx = cpu->dx + cpu->cx;
        }
        else if (secondReg == bx)
        {
            cpu->dx = cpu->dx + cpu->bx;
        }
    }
}