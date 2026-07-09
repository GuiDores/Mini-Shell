#include "../cabecalho.h"
#ifndef FUNCOES_SISTEMA_H
#define FUNCOES_SISTEMA_H

void ft_parse_input(char *input, char **args);
int ft_builtin_command(char **args);
void ft_execute_command(char **args);
int f_shell_loop();
#endif // FUNCOES_SISTEMA_H