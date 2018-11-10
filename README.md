# Khattab Machine

The Khattab  Machine is a project propused by Professor Renato Ferreira from my Basic Software class, the goal for the project is to expose students to the entire "software tower" going form the hight level languages (C/C++, Java, Pyhton) to the machine language, going through VM's, assembly, and multiple translations. 

The smallest allocable unit by the Khattab Machine(KBM) is a integer, every data processed by the KBM is an integer. The KBM has no less them 1000 memory positions, 3 especial registers and 8 general propose registers.

The tree especial registers are listed as bellow:
- PC (program counter): tells where is the next instruction
- SP (stack pointer): points to the top of the stack
- PEP : Hold the state of the last aritimetic operation, one for zero return operations the other for negative return operations.

## Instructions

| Code   | Symbol   | Parameters  | Behavior                        |
| ------ |:---------| :-----------|:--------------------------------|
| 01     | ADD      | R1 R2       | Reg[R1] ← Reg[R1] + Reg[R2]     |
| 02     | SUB      | R1 R2       | Reg[R1] ← Reg[R1]−Reg[R2] *     |
| 03     | AND      | R1 R2       | Reg[R1] ← Reg[R1] AND Reg[R2] * |
| 04     | OR       | R1 R2       | Reg[R1] ← Reg[R1] OR Reg[R2] *  |
| 05     | XOR      | R1 R2       | Reg[R1] ← Reg[R1] XOR Reg[R2] * | 
| 06     | NOT      | R1          | Reg[R1] ←NOT Reg[R1] *          |
| 07     | JUMP     | M           | PC ← PC + M                     |
| 08     | JZ       | M           | PEP[0],PC ← PC + M              |
| 09     | JNZ      | M           | !PEP[0],PC ← PC + M             |
| 10     | JN       | M           | PEP[negative],PC ← PC + M       |
| 11     | JNN      | M           | !PEP[negative],PC ← PC + M      |
| 12     | PUSH     | R           | AP ← AP −1 Mem[AP] ← Reg[R]     |
| 13     | POP      | R           | Reg[R] ← Mem[AP] & AP ← AP + 1    |
| 14     | CALL     | M           | AP ← AP −1 Mem[AP] ← PC & PC ← PC + M |
| 15     | LOAD     | R M         | Reg[R] ← Mem[M + PC]            |
| 16     | STORE    | R M         | Mem[M + PC] ← Reg[R]            |
| 17     | READ     | R           | Reg[R] ← “Read value”           |
| 18     | WRITE    | R           | “Write” Reg[R]                  | 
| 19     | COPY     | R1 R2       | Reg[R1] ← Reg[R2] *             | 
| 20     | RET      | None        | PC ← Mem[AP] AP ← AP + 1        |
| 21     | HALT     | None        | Stop execution                  |


## Emulator

#### READ and WRITE instructions use the emulator's stdin and stdout respectively. 

The files recognized by the emulator as executable are the ones using the _.mv_ extention. Check some examples in the  _tst/_  folder.

## Assembler

The assembler is implemented in an two-phased parse. First one adding labels to the symbols table, and the second one actually assembling the _.mv_ file for the emulator.

The assembler have two pseudo-instructions:
- WORD A: Save A in the current memory position
- END: Finish the assembler execution

Every line has the format showed bellow and the files expected by the assembler are _.amv_ files, and it outputs _.mv_ files.

``[<label>:] <operator> <operand1> <operand2> [; coment]``

