#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "assembler.h"


int main(int argc, char const *argv[])
{
    char **table;
    FILE* input_file;
    FILE* output_file;;
    
    input_file = fopen(argv[1], "r");
    table = look_for_symbols(input_file);
    fclose(input_file);

    output_file = fopen(argv[2], "w");
    input_file = fopen(argv[1], "r");
    assemble(input_file, output_file, table);
    fclose(input_file);
    fclose(output_file);
    
    for(int i = 0; i < 1000; i++)
    {
        if (strcmp(table[i], "#")) {
            printf("label: %s\t pc: %d\n", table[i], i);
        }

    }
    
    return 0;
}
