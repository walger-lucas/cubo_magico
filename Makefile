###################################### My First Makefile #############################################
#Nome do Projeto
PROJ_NAME = CuboMagico
#Pasta Source e Output
SRC_DIR = ./src
OBJ_DIR = ./obj
#COMPILADOR E Flags do C
CC = gcc
# -c essencial, -g para debug -O2 para release -Wall da Warnings
CFLAGS = -c -Wall -g
#Bibliotecas -lm para math.h
LIBS = -lm
# .h que devem estar up to date em todos os arquivos
H_SOURCE_ALL = def.h def_cubo.h
#Arquivos C, H e O
C_SOURCE = $(wildcard $(SRC_DIR)/*.c $(SRC_DIR)/*/*.c $(SRC_DIR)/*/*/*.c)
H_SOURCE = $(wildcard $(SRC_DIR)/*.h $(SRC_DIR)/*/*.h $(SRC_DIR)/*/*/*.h)
OBJS = $(addprefix $(OBJ_DIR)/,$(subst .c,.o,$(notdir $(C_SOURCE))))
#Comando Remove
RM = rm -rf
#Linking
VPATH = $(dir $(C_SOURCE) $(H_SOURCE))
all: objFolder $(PROJ_NAME)

$(PROJ_NAME): $(OBJS)
	@ echo 'Building binary using GCC linker: $@'
	$(CC) $^ -o  $@ 
	@ echo 'Finished building binary: $@'
	@ echo ' '
$(OBJ_DIR)/io_cubo.o: io_cubo.c io_cubo.h def.h def_cubo.h
	@ echo 'Building target using GCC compiler: $<'
	$(CC) $< $(LIBS) $(CFLAGS) -o $@
	@ echo ' '
$(OBJ_DIR)/montador_cubo.o: montador_cubo.c montador_cubo.h def.h def_cubo.h
	@ echo 'Building target using GCC compiler: $<'
	$(CC) $< $(LIBS) $(CFLAGS) -o $@
	@ echo ' '
$(OBJ_DIR)/def_cubo.o: def_cubo.c def_cubo.h 
	@ echo 'Building target using GCC compiler: $<'
	$(CC) $< $(LIBS) $(CFLAGS) -o $@
	@ echo ' '	
$(OBJ_DIR)/%.o: %.c %.h H_SOURCE_ALL
	@ echo 'Building target using GCC compiler: $<'
	$(CC) $< $(LIBS) $(CFLAGS) -o $@
	@ echo ' '
$(OBJ_DIR)/main.o: main.c $(H_SOURCE)
	@ echo 'Building target using GCC compiler: $<'
	$(CC) $< $(LIBS) $(CFLAGS) -o $@
	@ echo ' '
objFolder:
	@mkdir -p $(OBJ_DIR)
clean:
	@$(RM) $(OBJ_DIR)/*.o $(PROJ_NAME) *~
	@rmdir $(OBJ_DIR)

.PHONY: all clean


