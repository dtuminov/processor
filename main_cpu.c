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
    int cur_val = 0;
    while(!feof(file)) {
        fread(&cur_val, sizeof(int),1, file);
        printf("%d\t", cur_val);
        if (cur_val == Push)
        {
            //__push(stack);
        }
        
    }
    stack_destroy(stack);
    return 0;
}