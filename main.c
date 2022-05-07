// memory checking
//#define _CRTDBG_MAP_ALLOC
//#include <stdlib.h>
//#include <crtdbg.h>
//
#include <stdio.h>
#include <string.h>
#include "assembler.h"
#include <ctype.h>
int main(){
    FILE* asm_file = fopen("files/assembler.asm", "rb");
    if (asm_file == NULL) { printf_warning; exit(errno); }
    create_binar(asm_file);
    fclose(asm_file);
    //_CrtDumpMemoryLeaks();
  return 0;
} 
