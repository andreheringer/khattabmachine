
#if !defined(EMU)
#define EMU

#include <stdio.h>

int MEMORY[1000];
int REG[8];
int PC;
int SP;
char PEP[2];

int execution_loop(char exec_mode);


#endif // EMU
