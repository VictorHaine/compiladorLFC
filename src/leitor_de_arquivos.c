#include <stdio.h>
#include <stdlib.h>
#include "escritor.h"
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
    
    p_arquivo->conteudo = malloc(sizeof(char) * (p_arquivo->tamanho+1));
    size_t newLen = fread(p_arquivo->conteudo, sizeof(char), p_arquivo->tamanho, f);
    if(newLen == 0)
    {
        imprimir(COR_VERMELHO, "Ops! Ocorreu um erro ao ler o arquivo: %s\nTente novamente!", p_arquivo->caminho);
    }
    else
    {
        p_arquivo->conteudo[++newLen] = '\0';
    }
    fclose(f);
    
    return 1;
}