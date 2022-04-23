/**
 * @file assembler.c
 * @author tuminov dmitriy (you@domain.com)
 * @brief create binar file with code of functions
 * @version 2.14
 * @date 2022-03-18
 * 
 * @copyright Copyright (c) 2021
 * 
 */

#include "assembler.h"

/**
 * @brief the array of cpu and stack functions names
 * 
 */

const char* cpu_functions[] = {"stack_init", "pop", "push", "stack_destroy", "top"
, "mov", "add", "sub", "mult", "div", "exit"};

/**
 * @brief Create a binar object
 * 
 * @param file given file 
 * @return ERRORS 
 */

void create_binar(FILE* file){
    FILE *cpu_keys = fopen("files/binar.myexe", "w");
    //обработка открытия файла
    if (cpu_keys == NULL) { printf_warning; exit(errno); }
	char *lineBuf = NULL;
	size_t n = 0, nLines = 0, lineLength = 0, sizeIncrement = 10, i = 0;
	char **lines = calloc(sizeIncrement , sizeof(char**));
    // creating an array for working
	while ((lineLength = getline(&lineBuf, &n, file)) != -1) {
		
		if (i >= sizeIncrement) {
			sizeIncrement += sizeIncrement;
			char **tmp = realloc(lines, sizeIncrement * sizeof(char**));
			if (!tmp) {
				printf_warning;
				exit(errno);
			}
			lines = tmp;
		}
		// Remove \n from the line.
		lineBuf[strcspn(lineBuf, "\n")] = 0;
		// Allocate space on the heap for the line.
		*(lines + i) = malloc((lineLength + 1) * sizeof(char));
		// Copy the getline buffer into the new string.
		strcpy(*(lines + i), lineBuf);
		i++;
		// Keep track of the number of lines read for later use.
		nLines = i;
	}
    // main cycle
    for (size_t i = 0; i < nLines; i++) {
        char val[50], str[50];
        sscanf(lines[i], "%s", str);
        lines[i] += strlen(str);
        sscanf(lines[i], "%s", val);
        //pop
        if(strcmp(str, cpu_functions[1]) == 0){
            int name = Pop, reg_name = Get_reg_name(val);
            fwrite(&name, sizeof(name), 1, cpu_keys);
            fwrite(&reg_name, sizeof(reg_name), 1, cpu_keys);
            SWRITE;
        }
        //stack_init
        else if (strcmp(cpu_functions[0], str) == 0){ 
            printf("initialization of stack writed \n"); 
            int name = Stack_init;
            fwrite(&name, sizeof(name), 1, cpu_keys);
        }
        //push
        else if(strcmp(cpu_functions[2], str) == 0){
            int name, param;
            if (isdigit(val[0])) { name = Push; param = atoi(val); }
            else { name = Push_reg; param = Get_reg_name(val);}   
            fwrite(&name, sizeof(name), 1, cpu_keys);
            fwrite(&param, sizeof(param), 1, cpu_keys);
            SWRITE;
        }
        //top
        else if(strcmp(lines[i], cpu_functions[4]) == 0){
            fprintf(cpu_keys, "%d", Top);
        }  
        //mov
        else if(strcmp(str, cpu_functions[5]) == 0){
            int reg_name = 0;
            lines[i] += 1;
            sscanf(lines[i], "%s", val); //
            val[strlen(val)-1] = '\0';
            reg_name = Get_reg_name(val);
            lines[i] += 3;
            sscanf(lines[i], "%s", val);
            int name, param;
            if(isdigit(val[0])){ name = Mov_val; param = atoi(val); }
            else { name = Mov_reg; param = Get_reg_name(val); }
            fwrite(&name, sizeof(name), 1, cpu_keys);
            fwrite(&reg_name, sizeof(reg_name), 1, cpu_keys);
            fwrite(&param, sizeof(param), 1, cpu_keys);
            SWRITE;
        }
        //add
        else if(strcmp(lines[i], cpu_functions[6]) == 0){
            fprintf(cpu_keys, "%d", Add);
        }
        //sub
        else if(strcmp(lines[i], cpu_functions[7]) == 0){
            fprintf(cpu_keys, "%d", Sub);
        }
        //mult
        else if(strcmp(lines[i], cpu_functions[8]) == 0){
            fprintf(cpu_keys, "%d", Mult);
        }
        else if(strcmp(lines[i], cpu_functions[9]) == 0){
            fprintf(cpu_keys, "%d", Div);
            
        }
        else if(strcmp(lines[i], cpu_functions[10]) == 0){
            fprintf(cpu_keys, "%d", Exit);
        }
    }

    // Free the buffer utilised by `getline()`.
	free(lineBuf);
	// Free the lines of strings.
	for (size_t i = 0; i < nLines; i++)
		free(*(lines + i));
	free(lines);
    fclose(file);
    exit(errno);
}

/**
 * @brief 
 * 
 * @param val 
 * @return size_t 
 */

size_t Get_reg_name(char * val){
    if(val == NULL) { printf_warning; exit(errno); }
    if(strcmp(val, "ax") == 0)
        return ax;
    else if(strcmp(val, "bx") == 0)
        return bx;
    else if(strcmp(val, "cx") == 0)
        return cx;
    else if(strcmp(val, "dx") == 0)
        return dx;
    return -1;
}

/**
 * @brief 
 * 
 * @param lines 
 * @param length 
 */

void devide_lines(char** lines, size_t length){
    if(lines == NULL){ printf_warning; exit(errno); }
    //change '\n' to '\0' to iteration
    for (size_t i = 0; i < length; ++i) {
        char *ach;
        ach=strchr (lines[i], '\r');
        lines[i][ach-lines[i]] = '\0';
    }
}

/*struct pair* make_pair(){
    struct pair* pair = (struct pair*)calloc(sizeof(struct pair), 1);
    pair->iter = 0;
    return pair;
}*/
