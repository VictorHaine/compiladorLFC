#include <stdio.h>
#include <stdlib.h>
#include "analise_lexica.h"
#include "escritor.h"

#define DEBUG

char *caminho_do_arquivo;

int main(int argc, char* argv[])
{
    // Limpa o terminal, unix/dos.
    system("clear||cls");

    // #nois
    imprimir(COR_VERMELHO, "    __    ______ _____            __ __  _____ _____ ___   \n");
    imprimir(COR_VERMELHO, "   / /   / ____/ ____/           / // / / ____/ ____/ __ \\ \n");
    imprimir(COR_VERMELHO, "  / /   / /_  / /      ______   / // /_/ __/ / /   / /_/ /  \n");
    imprimir(COR_VERMELHO, " / /___/ __/ / /___   /_____/  /__  __/ /___/ /___/ _, _/   \n");
    imprimir(COR_VERMELHO, "/_____/_/    \\____/              /_/ /_____/\\____/_/ |_|    \n");
    imprimir(COR_VERMELHO, "                                                  V 1.0    \n");
    imprimir(COR_VERMELHO, "                                                            \n");

    // Verifica se algum caminho de arquivo foi passado como argumento para o programa,
    // caso contrário carrega um caminho padrão de um arquivo de testes.
    if(argv[1] != NULL)
        caminho_do_arquivo = argv[1];
    else
        caminho_do_arquivo = "../input/test1b.txt";
    
    // Chama a função obter_tokens do arquivo analise_lexica.c que tem retorno um container
    // léxico, com os tokens, tabela de símbolos e ocasionalmente uma mensagem de erro.
    struct container_lexico *container = obter_tokens(caminho_do_arquivo);
    
    // Verifica se a mensagem de erro do container léxico é nula, caso contrário imprimi
    // a mensagem para o usuário.
    if(container->mensagem_de_erro != NULL)
    {
        imprimir(COR_VERMELHO,"%s\n\n", container->mensagem_de_erro);
    }
    
    return 0;
}