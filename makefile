PROJ_NAME = mini_shell

#Pasta de destino para os arquivos .o
OBJ_DIR= obj

#compilador de flags
CC = gcc
CFLAGS = -Wall -Wextra -Werror

#Buscar os arquivos .c e criar os arquivos .o correspondentes
SRCS = $(wildcard *.c) $(wildcard */*.c)
OBJS = $(addprefix $(OBJ_DIR)/, $(notdir $(SRCS:.c=.o))) 

#Buscar os arquivos .h
VPATH = . funcoes

HDRS = $(wildcard *.h) $(wildcard */*.h)

EXEC = $(PROJ_NAME).exe

#regra para compilar tudo
all: setup $(OBJ_DIR) $(EXEC)

# Muda a cor para verde (0a) no início
setup:
	@color 0a
#regra para criar a pasta de destino dos arquivos .o
$(OBJ_DIR):
	@mkdir -p $(OBJ_DIR) 2>nul || exit 0

#Regra de compilação com "status" para mostrar o progresso
$(OBJ_DIR)/%.o: %.c $(HDRS)
	@chcp 65001 >nul && echo [###-------] 30% Compilando o programa... $<
	@$(CC) $(CFLAGS) -c $< -o $@

$(EXEC): $(OBJS)
	@chcp 65001 >nul && echo -------------------------------------------
	@chcp 65001 >nul && echo [######----] 60% Linkando o programa...
	@chcp 65001 >nul && echo [#########-] 90% Finalizando o processo...
	@chcp 65001 >nul && echo [##########] 100% Processo concluído! Criando o executável...
	@$(CC) $(CFLAGS) -o $@ $^
	@echo [LINKADO] $@ com sucesso!
	@echo -------------------------------------------

#regra para limpar os arquivos .o e o executável
clean:
	@del /q $(OBJ_DIR)\*.o $(EXEC) 2>nul || rm -rf $(OBJ_DIR) $(EXEC)

#regra para rodar o programa
run: all
		./$(EXEC)

#Regra para compilar o programa em modo debug
debug: CFLAGS += -g
debug: all

.PHONY: all clean run debug