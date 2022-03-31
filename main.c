#include <stdio.h>
#include <string.h>
#include "assembler.h"
#include <ctype.h>
int main(){
    FILE* asm_file = fopen("files/assembler.asm", "rb");
    create_binar(asm_file);
    fclose(asm_file);
  return 0;
}
