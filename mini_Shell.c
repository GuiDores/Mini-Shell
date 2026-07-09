#include <stdio.h>
#include "cabecalho.h"
#include "funcoes/FUNCOES_SISTEMA_H.h"
#include "funcoes/FUNCOES_COMANDOS_H.h"

int main(){
#ifdef _WIN32
    SetConsoleOutputCP(CP_UTF8);
#endif

    printf("Olá, seja bem-vindo ao mini Shell!\n");
    printf("Digite um comando para começar: ");
    f_shell_loop();
    return 0;
}