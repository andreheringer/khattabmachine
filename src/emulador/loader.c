#include <stdio.h>
#include <stdlib.h>

#include "loader.h"


int input_parser(const char *file_name, int mem_entrypoint, int stack_entrypoint, int *memory)
{
    FILE *input;
    int aux_buffer;
    input = fopen(file_name, "r");
    while(fscanf(input, "%d", &aux_buffer) == 1)
    {
        if(mem_entrypoint == stack_entrypoint)
        {
            fprintf(stderr, "[ERROR]:Stack and PC memory conflict, aborting...\n");
            return 1;
        }
        if(mem_entrypoint >= 1000)
        {
            fprintf(stderr, "[ERROR]: mem_entrypoint is too big\n");
            return 1;
        }
        memory[mem_entrypoint] = aux_buffer;
        mem_entrypoint++;
    }
    if(feof(input))
    {
        //if we find the end of file, we're done
        //printf("Load sucessful\n");
        fclose(input);
        return 0;
    }else
    {
        fprintf(stderr, "[ERRO]: Something went wrong.\n");
        return 1;
    }
    fclose(input);
    return 0;
}