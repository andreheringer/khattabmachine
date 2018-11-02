
# Parametros de Ambiente

CC = gcc
 
CFLAGS = -Wall


# Parametros de Projeto

# TODO: altere a lista de forma que contenha todos os arquivos .c 
#       do seu projeto, que deve estar no diretório src/emulator
SRC_EMULATOR = main.c loader.c emu.c

OBJS_EMULATOR = $(SRC_EMULATOR:%.c=build/emulator/%.o)

SRC_ASSEMBLER = main.c assembler.c

OBJS_ASSEMBLER = $(SRC_ASSEMBLER:%.c=build/assembler/%.o)

assembler: bin/assembler

bin/assembler: $(OBJS_ASSEMBLER)
	@echo "+ Compilando programa \"$@\""
	@$(CC) $(CFLAGS) $(OBJS_ASSEMBLER) -o bin/assembler


# Objetos

build/%.o: src/%.c src/%.h
	@echo "- Compilando objeto \"$@\""
	@$(CC) -c $(CFLAGS) $< -o $@

build/%.o: src/%.c
	@echo "- Compilando objeto \"$@\""
	@$(CC) -c $(CFLAGS) $< -o $@

#


# Executaveis

emulator: bin/emulator

bin/emulator: $(OBJS_EMULATOR)
	@echo "+ Compilando programa \"$@\""
	@$(CC) $(CFLAGS) $(OBJS_EMULATOR) -o bin/emulator


# Objetos

build/%.o: src/emulator/%.c src/emulator/%.h
	@echo "- Compilando objeto \"$@\""
	@$(CC) -c $(CFLAGS) $< -o $@

build/%.o: src/emulator/%.c
	@echo "- Compilando objeto \"$@\""
	@$(CC) -c $(CFLAGS) $< -o $@


# Auxiliares

clean:
	rm -f bin/*
