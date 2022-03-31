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
#include <stdio.h>
#include <string.h>
#include <ctype.h>

/**
 * @brief the array of cpu and stack functions names
 * 
 */

const char* cpu_functions[] = {"stack_init", "pop", "push", "stack_destroy", "top"
, "mov", "add", "sub", "mult", "div", "exit"};

/**
 * @brief Create a binar object
 * 
 * @param file 
 * @return ERRORS 
 */

ERRORS create_binar(FILE* file){
    FILE *cpu_keys = fopen("files/binar.myexe", "w");
    if (cpu_keys == NULL || file == NULL){
        perror("ERROR");
		return EXIT_FAILURE;
    }

	char *lineBuf = NULL;
	size_t n = 0;
	size_t nLines = 0;
	size_t lineLength = 0;
	size_t sizeIncrement = 10;
	char **lines = malloc(sizeIncrement * sizeof(char**));
	size_t i = 0;

    // creating an array for working
	while ((lineLength = getline(&lineBuf, &n, file)) != -1) {
		
		if (i >= sizeIncrement) {
			sizeIncrement += sizeIncrement;
			char **tmp = realloc(lines, sizeIncrement * sizeof(char**));
			if (!tmp) {
				perror("realloc");
				return EXIT_FAILURE;
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
    // push \0 in the end of string 
    devide_lines(lines, nLines);

    // main cycle
    for (size_t i = 0; i < nLines; i++) {
        char val[50]; char str[50];
        sscanf(lines[i], "%s", str);
        lines[i] += strlen(str);
        sscanf(lines[i], "%s", val);
        //pop
        if(strcmp(str, cpu_functions[1]) == 0){
            printf("function pop writed \n"); 
            int name = Pop;
            fwrite(&name, sizeof(name), 1, cpu_keys);
        }
        //stack_init
        else if (strcmp(cpu_functions[0], str) == 0){ 
            printf("initialization of stack writed \n"); 
            int name = Stack_init;
            fwrite(&name, sizeof(name), 1, cpu_keys);
        }
        //push
        else if(strcmp(cpu_functions[2], str) == 0){
            printf("push writed\n");
            int name, param;
            if (isdigit(val[0])) { name = Push; param = atoi(val); }
            else { name = Push_reg; param = Get_reg_name(val);}   
            fwrite(&name, sizeof(name), 1, cpu_keys);
            fwrite(&param, sizeof(param), 1, cpu_keys);
        }
        //stack_destroy
        else if(strcmp(lines[i], cpu_functions[3]) == 0){
            fprintf(cpu_keys, "%d", Stack_destroy);
            return ok;
        }
        //top
        else if(strcmp(lines[i], cpu_functions[4]) == 0){
            fprintf(cpu_keys, "%d", Top);
            return ok;
        }  
        //mov
        else if(strcmp(lines[i], cpu_functions[5]) == 0){
            fprintf(cpu_keys, "%d", Mov);
            return ok;
        }
        //add
        else if(strcmp(lines[i], cpu_functions[6]) == 0){
            fprintf(cpu_keys, "%d", Add);
            return ok;
        }
        //sub
        else if(strcmp(lines[i], cpu_functions[7]) == 0){
            fprintf(cpu_keys, "%d", Sub);
            return ok;
        }
        //mult
        else if(strcmp(lines[i], cpu_functions[8]) == 0){
            fprintf(cpu_keys, "%d", Mult);
            return ok;
        }
        else if(strcmp(lines[i], cpu_functions[9]) == 0){
            fprintf(cpu_keys, "%d", Div);
            return ok;
        }
        else if(strcmp(lines[i], cpu_functions[10]) == 0){
            fprintf(cpu_keys, "%d", Exit);
            return ok;
        }
    }

    // Free the buffer utilised by `getline()`.
	free(lineBuf);
	// Free the lines of strings.
	for (size_t i = 0; i < nLines; i++)
		free(*(lines + i));
	free(lines);
    fclose(file);
    return ok;
}

/**
 * @brief 
 * 
 * @param val 
 * @return size_t 
 */

size_t Get_reg_name(char * val){
    if(val == NULL)
        return -1;
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
    if(lines == NULL)
        return;
    //change '\n' to '\0' to iteration
    for (size_t i = 0; i < length; ++i)
    {
       char *ach;
  
        ach=strchr (lines[i], '\r');
        lines[i][ach-lines[i]] = '\0';
    }
    
}

//check error with the end of file
//material heme darker high contrast 