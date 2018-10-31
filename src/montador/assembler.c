#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "assembler.h"

const char instructions[23][6] = {
    "END",
    "ADD",
    "SUB",
    "AND",
    "OR",
    "XOR",
    "NOT",
    "JUMP",
    "JZ",
    "JNZ",
    "JN",
    "JNN",
    "PUSH",
    "POP",
    "CALL",
    "LOAD",
    "STORE",
    "READ",
    "WRITE",
    "COPY",
    "RET",
    "HALT",
    "WORD"
};

const char regs[8][3] = {"R0", "R1", "R2", "R3", "R4", "R5", "R6", "R7"};

void deleteComment (char* myStr)
{

    char *del = &myStr[strlen(myStr)];

    while (del > myStr && *del != ';') {
        del--;
    }
        
    if (*del == ';') {
        *del = '\0';
    }

    return;
}


char** look_for_symbols(FILE* input_stream)
{
    char** symbolic_table;
    symbolic_table = malloc(1000 * sizeof(char*));
    for(int i = 0; i < 1000; i++) {
        symbolic_table[i] = malloc(50 * sizeof(char));
        strcpy(symbolic_table[i], "#");
    }

    int PC = 0;
    char line_buffer[1000];
    char label[50];
    while(fscanf(input_stream, "%[^\n]\n", line_buffer) == 1) {
        
        char command[6];
        char arg1[20];
        char arg2[20];
        
        deleteComment(line_buffer);    
        
        if (line_buffer[0] == '\0' || strspn(line_buffer, " \r\n\t") == strlen(line_buffer)) {
            continue;
        }

        char* label_checker = strstr(line_buffer, ":");
        if (label_checker) {
            sscanf(line_buffer, "%[^:]", label);
            strcpy(symbolic_table[PC], label);
            PC++;
        }
        else {
            int pc_increment = sscanf(line_buffer,"%s %s %s", command, arg1, arg2);
            PC += pc_increment;
        }
        
    }
    return symbolic_table;
}


void single_arg_command(int PC, char* command, char* arg1, 
                        char** symbols, FILE* input_stream, FILE* output_stream)
{
    int is_regis = 0;

    for(int i = 0; i < 23; i++) {
        if(strcmp(command, instructions[i]) == 0) {
            fprintf(output_stream, "%d\n", i);
        }
    }

    for(int i = 0; i < 8; i++) {
        if(strcmp(arg1, regs[i]) == 0) {
            fprintf(output_stream, "%d\n", i);
            is_regis = 1;
        }
    }

    if(is_regis == 0) {
        for(int i = 0; i < 1000; i++) {
            if(strcmp(arg1, symbols[i]) == 0) {
                fprintf(output_stream, "%d\n", i - PC);
            }
        }
    }
}

void double_arg_command(int PC, char* command, char* arg1, char* arg2,
                        char** symbols, FILE* input_stream, FILE* output_stream)
{
    int is_regis = 0;
    for(int i = 0; i < 23; i++) {
        if(strcmp(command, instructions[i]) == 0) {
            fprintf(output_stream, "%d\n", i);
        }
    }

    for(int i = 0; i < 8; i++) {
        if(strcmp(arg1, regs[i]) == 0) {
            fprintf(output_stream, "%d\n", i);
        }
    }

    for(int i = 0; i < 8; i++) {
        if (strcmp(arg2, regs[i]) == 0) {
            fprintf(output_stream, "%d\n", i);
            is_regis = 1;    
        }
        
    }

    if(is_regis == 0) {
        for(int i = 0; i < 1000; i++) {
            if (strcmp(arg2, symbols[i]) == 0) {
                fprintf(output_stream, "%d\n", i);
                return;        
            }
        }
        
        fprintf(output_stream, "%d\n", atoi(arg2));
    }
}

void assemble(FILE* input_stream, FILE* output_stream, char** symbols)
{
    int PC = 0;
    char line_buffer[1000];
    char label[50];
    while(fscanf(input_stream, "%[^\n]\n", line_buffer) == 1) {
        
        char command[6];
        char arg1[20];
        char arg2[20];
        int pc_increment = 0;
        
        deleteComment(line_buffer);
        
        if (line_buffer[0] == '\0' || strspn(line_buffer, " \r\n\t") == strlen(line_buffer)) {
            continue;
        }
        
        char* label_checker = strstr(line_buffer, ":");
        
        if (label_checker) {
            pc_increment = sscanf(line_buffer,"%[^:]: %s %s %s", label, command, arg1, arg2);
            
            if (pc_increment == 3) {
                single_arg_command(PC, command, arg1, symbols, input_stream, output_stream);
            }
            else if (pc_increment == 4) {
                double_arg_command(PC, command, arg1, arg2, symbols, input_stream, output_stream);
            }
            else {
                fprintf(stderr, "[ERROR]: something went wrong!\n");
                return;
            }
            pc_increment--;
        }
        else {
            pc_increment = sscanf(line_buffer,"%s %s %s", command, arg1, arg2);
            
            if(pc_increment == 1) {
                if(strcmp(command, symbols[0]) == 0) {
                    return;
                }
                else if(strcmp(command, symbols[21]) == 0) {
                    fprintf(output_stream, "21\n");
                }
            }
            else if (pc_increment == 2) {
                single_arg_command(PC, command, arg1, symbols, input_stream, output_stream);
            }
            else if (pc_increment == 3) {
                double_arg_command(PC, command, arg1, arg2, symbols, input_stream, output_stream);
            }
            else {
                fprintf(stderr, "[ERROR]: something went wrong!\n");
                return;
            }
        }
        PC += pc_increment;
    }

}

