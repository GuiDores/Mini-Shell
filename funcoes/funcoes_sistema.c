#include <stdio.h>
#include "../cabecalho.h"
#include "FUNCOES_COMANDOS_H.h"
#include "FUNCOES_SISTEMA_H.h"

// Função apenas para picar a string (Parse)
void ft_parse_input(char *input, char **args){
    int i = 0;
    char *token = strtok(input, " ");
    
    while(token != NULL && i < MAX_ARGS - 1){
        args[i++] = token;
        token = strtok(NULL, " ");
    }
    args[i] = NULL;
    
    for (int j = 0; j < i; j++){
        printf("Arg %d: %s\n", j, args[j]);
    }
}

// Função para comandos que o Windows não roda sozinho (Built-ins)
int ft_builtin_command(char **args){
    if (strcmp(args[0], "exit") == 0){
        printf("Saindo do mini Shell...\n");
        exit(0);
    }

    if (strcmp(args[0], "cd") == 0){
        if (args[1] != NULL && _chdir(args[1]) != 0){
            perror("Erro ao mudar de diretório");
        }
        return 1;
    }

    // Novo comando interno: ls
    if (strcmp(args[0], "ls") == 0){
        ft_list_directory();
        return 1;
    }

    // COMANDO: touch (criar arquivo)
    if (strcmp(args[0], "touch") == 0){
        if(args[1]) ft_create_file(args[1]);
        else printf("Uso: touch <nome_do_arquivo>\n");
        return 1;
    }

    // COMANDO: rm (remover arquivo)
    if (strcmp(args[0], "rm") == 0){
        if (args[1] != NULL){
            ft_delete_file(args[1]);
        } else {
            printf("Uso: rm <nome_do_arquivo>\n");
        }
        return 1;
    }

    // COMANDO: mkdir (criar pasta)
    if (strcmp(args[0], "mkdir") == 0){
        if (args[1]){
            if (_mkdir(args[1]) == 0) printf("Pasta '%s' criada com sucesso.\n", args[1]);
            else perror("Erro ao criar a pasta");
        }
        return 1;
    }
    
    return 0;
}

// Função para rodar programas externos (.exe)
void ft_execute_command(char **args){
    intptr_t status = _spawnvp(_P_WAIT, args[0],(const char * const *)args);
    if (status == -1) {
        perror("Erro ao executar o comando");
    }
}

int f_shell_loop(){
  
    char input[100];
    char *args[MAX_ARGS];
    char cwd[MAX_PATH]; // Buffer para o caminho atual

    while(1){
        if (_getcwd(cwd, sizeof(cwd)) != NULL) {
            printf("%s> ", cwd);
        } else {
            printf("mini_Shell> ");
        }

        if (fgets(input, sizeof(input), stdin) == NULL) break;
        input[strcspn(input, "\n")] = 0;
        ft_parse_input(input, args);
        if (args[0] == NULL) continue;

        // Tenta rodar interno, se não for, tenta externo
        if (!ft_builtin_command(args)){
            ft_execute_command(args);
        }
    }
        return 0;
}