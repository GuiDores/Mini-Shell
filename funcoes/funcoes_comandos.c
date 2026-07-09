#include <stdio.h>
#include "../cabecalho.h"

// Cria um arquivo vazio (touch)
void ft_create_file(char *filename){
    FILE *file = fopen(filename, "a");
    if (file){
        fclose(file);
        printf("Arquivo '%s' criado com sucesso.\n", filename);
    } else {
        perror("Erro ao criar o arquivo");
    }
}

// Remove um arquivo (rm)
void ft_delete_file(const char *filename){
    if (remove(filename) == 0){
        printf("Arquivo '%s' removido com sucesso.\n", filename);
    } else {
        perror("Erro ao remover o arquivo");
    }
}

// Função para listar arquivos no diretório atual (ls)
void ft_list_directory() {
    struct _finddata_t file_data;
    intptr_t handle;

    if ((handle = _findfirst("*", &file_data)) == -1L) {
        printf("Diretório vazio ou erro ao acessar o diretório.\n");
        return;
    }
    
    printf("\nListagem de arquivos:\n");
    do {
        // Verifica se é um diretório ou arquivo para imprimir o rótulo
        const char *type = (file_data.attrib & _A_SUBDIR) ? "<DIR>" : "<FILE>";
        printf("%-7s %s\n", type, file_data.name);
    } while (_findnext(handle, &file_data) == 0);

    _findclose(handle);
    printf("\n");
}