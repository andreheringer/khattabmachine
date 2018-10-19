#include <stdlib.h>
#include <stdio.h>

#include "emu.h"

void update_pep(int last_command_return)
{
    if (last_command_return > 0)
    {
        PEP[0] = 1;
        PEP[1] = 0;
    }else
    {
        PEP[0] = 1;
        PEP[1] = 0;
    }
    return; 
}

int execute_command(int command_code)
{
    int aux_R1;
    int aux_R2;

    //command list
    switch (command_code)
    {
        case 1:
            /* ADD */
            PC++;
            aux_R1 = MEMORY[PC];
            PC++; 
            aux_R2 = MEMORY[PC];
            REG[aux_R1] = REG[aux_R1] + REG[aux_R2];
            update_pep(REG[aux_R1]);
            PC++; 
            break;
        
        case 2:
            /* SUB */
            PC++;
            aux_R1 = MEMORY[PC];
            PC++; 
            aux_R2 = MEMORY[PC];
            REG[aux_R1] = REG[aux_R1] - REG[aux_R2];
            update_pep(REG[aux_R1]);
            PC++; 
            break;
        
        case 3:
            /* AND */
            PC++;
            aux_R1 = MEMORY[PC];
            PC++; 
            aux_R2 = MEMORY[PC];
            REG[aux_R1] = REG[aux_R1] & REG[aux_R2];
            update_pep(REG[aux_R1]);
            PC++; 
            break;
        
        case 4:
            /* OR */
            PC++;
            aux_R1 = MEMORY[PC];
            PC++; 
            aux_R2 = MEMORY[PC];
            REG[aux_R1] = REG[aux_R1] | REG[aux_R2];
            update_pep(REG[aux_R1]);
            PC++; 
            break;
        
        case 5:
            /* XOR */
            PC++; 
            aux_R1 = MEMORY[PC];
            PC++;  
            aux_R2 = MEMORY[PC];
            REG[aux_R1] = REG[aux_R1] ^ REG[aux_R2];
            update_pep(REG[aux_R1]);
            PC++;
            break;
    
        case 6:
            /* NOT */
            PC++; 
            aux_R1 = MEMORY[PC]; 
            REG[aux_R1] = ~REG[aux_R1];
            update_pep(REG[aux_R1]);
            PC++;
            break;
        
        case 7:
            /* JUMP */
            PC++;
            PC = PC + MEMORY[PC];
            break;

        case 8:
            /* JZ */
            PC++;
            PC += (PEP[0]) ? MEMORY[PC]+1 : 1;
            break;

        case 9:
            /* JNZ */
            PC++;
            PC += (!PEP[0]) ? MEMORY[PC]+1 : 1;
            break;

        case 10:
            /* JN */
            PC++;
            PC += (PEP[1]) ? MEMORY[PC]+1 : 1;
            break;
        
        case 11:
            /* JNN */
            PC++;
            PC += (!PEP[1]) ? MEMORY[PC]+1 : 1;
            break;
        
        case 12:
            /* PUSH */
            SP--;
            PC++;
            aux_R1 = MEMORY[PC];
            MEMORY[SP] = aux_R1;
            PC++;
            break;
        
        case 13:
            /* POP */
            PC++;
            REG[PC] = MEMORY[SP];
            SP++;
            PC++;
            break;

        case 14:
            /* CALL */
            PC++;
            SP--;
            MEMORY[SP] = PC + 1;
            PC = PC + MEMORY[PC];
            break;
        
        case 15:
            /* LOAD */
            PC++;
            aux_R1 = MEMORY[PC];
            PC++;
            aux_R2 = MEMORY[PC];
            PC++;
            REG[aux_R1] = MEMORY[aux_R2 + PC];
            break;
        
        case 16:
            /* STORE */
            PC++;
            aux_R1 = MEMORY[PC];
            PC++;
            aux_R2 = MEMORY[PC];
            PC++;
            MEMORY[aux_R2 + PC] = REG[aux_R1];
            break;
        
        case 17:
            /* READ */
            PC++;
            aux_R1 = MEMORY[PC];
            scanf("%d", &REG[aux_R1]);
            PC++;
            break;
        
        case 18:
            /* WRITE */
            PC++;
            aux_R1 = MEMORY[PC];
            printf("%d\n", REG[aux_R1]);
            PC++;
            break;
        
        case 19:
            /* COPY */
            PC++;
            aux_R1 = MEMORY[PC];
            PC++;
            aux_R2 = MEMORY[PC];
            REG[aux_R1] = REG[aux_R2];
            update_pep(REG[aux_R1]);
            PC++;
            break;
        
        case 20:
            /* RET */
            PC = MEMORY[SP];
            SP++;
            break;

        case 21:
            return 0;

        default:
            fprintf(stderr, "[ERROR]: Command not found. Aborting execution loop.\n");
            break;
    }
    return 1;
}

int execution_loop(char exec_mode)
{
    while(execute_command(MEMORY[PC]))
    {
        if (exec_mode == 'v')
        {
            printf("PC: %d, SP: %d, PEP: %d %d\n", PC, SP, PEP[0], PEP[1]);
        }
        
    }
    if(MEMORY[PC] != 21)
    {
        //printf("End of execution.\n");
        fprintf(stderr, "[ERROR]: Somethig went wrong. Execution loop, ended without code 21.\n");
        return 1;
    }
    return 0;
}