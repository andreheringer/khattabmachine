
#if !defined(ASSEMBLER)
#define ASSEMBLER

const char instructions[23][6];
const char regis[8][3];

char** look_for_symbols(FILE*);
void assemble(FILE* input_stream, FILE* output_stream, char** symbols);

#endif // ASSEMBLER
