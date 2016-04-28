#include <stdio.h>
#include <stdlib.h>

#include "leitor_de_arquivos.h"

int carregar_arquivo(struct arquivo *p_arquivo, char *p_caminho)
{
    if (p_caminho == NULL)
        return 0;
    
    p_arquivo->caminho = p_caminho;
    FILE *f = fopen(p_arquivo->caminho, "rb");
    
    if (!f)
        return 0;
    
    fseek(f, 0, SEEK_END);
    p_arquivo->tamanho = ftell(f);
    rewind(f);
    
    if (p_arquivo->tamanho == -1)
        return 0;
    
    p_arquivo->conteudo = malloc(p_arquivo->tamanho);
    fread(p_arquivo->conteudo, p_arquivo->tamanho+1, 1, f);
    fclose(f);
    
    return 1;
}