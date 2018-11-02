#include <stdio.h>
#include <stdlib.h>

#include "loader.h"
#include "emu.h"

int main(int argc, char const *argv[])
{
    sscanf(argv[1],"%d", &PC);
    sscanf(argv[2], "%d", &SP);
    int mem_entrypoint;
    sscanf(argv[3], "%d", &mem_entrypoint);
    char mode;
    sscanf(argv[4], "%c", &mode);

    int input_return = input_parser(argv[5], mem_entrypoint, SP, MEMORY);

    if (input_return != 0)
    {
        printf("Meh.\n");
        return 1;
    }
    PC = PC + mem_entrypoint;
    return execution_loop(mode);
}
