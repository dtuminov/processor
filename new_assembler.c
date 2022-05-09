#include "assembler.h"

/**
 * @file assemb ler.c
 * @author tuminov dmitriy (you@domain.com)
 * @brief create binar file with code of functions
 * @version 3.7
 * @date 2022-03-18
 * 
 * @copyright Copyright (c) 2021
 * 
 */

/**
 * @brief the array of cpu and stack functions names
 */

const char* cpu_functions[] = {"stack_init", "pop", "push", "stack_destroy", "top"
, "mov", "add", "sub", "mult", "div", "ja", "jmp", "cmp", "return"};

//количество меток в файле
int labels_size = 0;

//лимит на количество меток
//количство меток в файле хранится в labels_size
pair labels[200];

/**
 * @brief Create a binar object
 * @param file given file 
 * @return ERRORS 
 */


void create_binar(FILE* file){
    FILE *cpu_keys = fopen("files/binar.myexe", "w");
    //обработка открытия файла
    if (cpu_keys == NULL)  
        printf_warning;
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
    //ищем количество меток в файле
    find_labels(lines, nLines);
    // цикл заполения бинарника
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
        //push
        else if(strcmp(cpu_functions[2], str) == 0){
            int name, param;
            if (isdigit(val[0])) { name = Push; param = atoi(val); }
            else { name = Push_reg; param = Get_reg_name(val);}   
            fwrite(&name, sizeof(name), 1, cpu_keys);
            fwrite(&param, sizeof(param), 1, cpu_keys);
            SWRITE;
        }
        //mov переделать
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
        else if(strcmp(str, cpu_functions[6]) == 0){
            int name = Add, reg_name = 0;
            fwrite(&name, sizeof(name), 1, cpu_keys);
            lines[i] += 1;
            sscanf(lines[i], "%s", val);
            val[strlen(val)-1] = '\0';
            reg_name =  Get_reg_name(val);
            fwrite(&reg_name, sizeof(reg_name), 1, cpu_keys);
            reg_name = Get_reg_name(val);
            lines[i] += 3;
            sscanf(lines[i], "%s", val);
            reg_name =  Get_reg_name(val);
            fwrite(&reg_name, sizeof(reg_name), 1, cpu_keys);
            SWRITE;
        }
        //sub
        else if(strcmp(str, cpu_functions[7]) == 0){
        }
        //mult
        else if(strcmp(str, cpu_functions[8]) == 0){
        }
        else if(strcmp(str, cpu_functions[9]) == 0){
        }
        //ja
        else if(strcmp(str, cpu_functions[10]) == 0){
            int name = J_a;
            int lab = Get_label_name(labels, val) ;
            fwrite(&name, sizeof(name), 1, cpu_keys);
            fwrite(&lab, sizeof(lab), 1, cpu_keys);
            SWRITE;
        }
        //jmp
        else if(strcmp(str, cpu_functions[11]) == 0){
            int name = Jmp;
            int lab = Get_label_name(labels, val) ;
            fwrite(&name, sizeof(name), 1, cpu_keys);
            fwrite(&lab, sizeof(lab), 1, cpu_keys);
            SWRITE;
        }
        //cmp переделать
        else if(strcmp(str, cpu_functions[12]) == 0){
            int name = Cmp, reg_name = 0;
            fwrite(&name, sizeof(name), 1, cpu_keys);
            lines[i] += 1;
            sscanf(lines[i], "%s", val);
            val[strlen(val)-1] = '\0';
            reg_name =  Get_reg_name(val);
            fwrite(&reg_name, sizeof(reg_name), 1, cpu_keys);
            reg_name = Get_reg_name(val);
            lines[i] += 3;
            sscanf(lines[i], "%s", val);
            reg_name =  Get_reg_name(val);
            fwrite(&reg_name, sizeof(reg_name), 1, cpu_keys);
            SWRITE;
        }
        //exit
        else if(strcmp(str, cpu_functions[13]) == 0){
            int name = Return;
            fwrite(&name, sizeof(name), 1, cpu_keys);
            SWRITE;
        }
    }
    fclose(file);
    // Free the buffer utilised by `getline()`.
	free(lineBuf);
	// Free the lines of strings.
	for (size_t i = 0; i < nLines; i++)
		free(*(lines + i));
	free(lines);
   // delete_pair(pair);
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

//ГОВНОКОД ФИКС
//это вообще пиздец
// я сам не ебу что она делает
char* my_strcpy(char* str){
    size_t length = strlen(str) + 2;
    char  *new = (char*)calloc(sizeof(char), length);
    strcpy(new, str);
    new[length-2] = ':'; new[length-1] = '\0';
    return new;
}

//ГОВНОКОД ПОФИКСТЬ
char* my_strcmp(char* first){
   for (size_t i = 0; i < strlen(first); i++)
   {
       if (first[i] == '\r')
       {
           first[i] = '\0';
       }
   }
   return first;
    
}
// 167 строка... ФИКС
size_t Get_label_name(pair array[], char * label){
    label = my_strcpy(label);
    for (size_t i = 0; i < labels_size; i++)
    {   
        array[i].str = my_strcmp(array[i].str);
        if (strcmp(array[i].str, label) == 0){
            return array[i].iter;
        }
    }
    return -1;
}

/**
 * @brief 
 * 
 * @param lines 
 * @param length 
 */

void devide_lines(char** lines, size_t length){
    if(lines == NULL){ printf_warning; }
    //change '\n' to '\0' to iteration
    for (size_t i = 0; i < length; ++i) {
        char *ach;
        ach=strchr (lines[i], '\r');
        lines[i][ach-lines[i]] = '\0';
    }
}

/**
 * @brief 
 * 
 * @param code_of_position 
 * @param name_of_label 
 * @return struct pair 
 */

struct pair make_pair(int code_of_position, char* name_of_label){
    if(name_of_label == NULL)
        printf_warning;
    pair pair;
    pair.iter = code_of_position;
    pair.str = name_of_label;
    return pair;
}

void find_labels(char** bufer, int lenght){
    if(NULL == bufer)
        printf_warning; 
    int iter = 0, val = 0; 
    for (size_t i = 0; i < lenght; i++) {
        val += get_count_of_spase(bufer[i]);
        if (strchr(bufer[i], ':') != NULL) {
            if (i > 0 ) {
                val++;
            }
            labels[iter] = make_pair(val, bufer[i]);
            iter++; labels_size++;
        }
    }
}

//эта штука блять считает количество пробелов в строке и из этого
//возвращает сколько слов в строке
int get_count_of_spase(char* str){
    if (str == NULL){
        printf_warning;
    }
    int val = 0;
    for (size_t i = 0; i < strlen(str); i++)
    {
        if(strchr(str, ':') != 0){
            return 0;
        }
        if (str[i] == ' ') {
            val++;
        } 
    }
    return ++val;
}