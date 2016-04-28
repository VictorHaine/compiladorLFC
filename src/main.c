#include <stdio.h>
#include <stdlib.h>
#include "analise_lexica.h"
#include "escritor.h"

#define DEBUG

char *caminho_do_arquivo;

int main(int argc, char* argv[])
{
    imprimir("%s, teste", COR_VERMELHO, "teste");
    
    // // Limpa o terminal, unix/dos.
    // system("clear||cls");

    // // #nois
    // printf(TCOLOR "    __    ______ _____            __ __  _____ _____ ___   \n" RESET);
    // printf(TCOLOR "   / /   / ____/ ____/           / // / / ____/ ____/ __ \\ \n" RESET);
    // printf(TCOLOR "  / /   / /_  / /      ______   / // /_/ __/ / /   / /_/ /  \n" RESET);
    // printf(TCOLOR " / /___/ __/ / /___   /_____/  /__  __/ /___/ /___/ _, _/   \n" RESET);
    // printf(TCOLOR "/_____/_/    \\____/              /_/ /_____/\\____/_/ |_|    \n" RESET);
    // printf(TCCOLOR "                                                   V 1.0    \n" RESET);
    // printf(TCOLOR "                                                            \n" RESET);

    // // Verifica se algum caminho de arquivo foi passado como argumento para o programa,
    // // caso contrário carrega um caminho padrão de um arquivo de testes.
    // if(argv[1] != NULL)
    //     caminho_do_arquivo = argv[1];
    // else
    //     caminho_do_arquivo = "../input/test1b.txt";
    
    // // Chama a função obter_tokens do arquivo analise_lexica.c que tem retorno um container
    // // léxico, com os tokens, tabela de símbolos e ocasionalmente uma mensagem de erro.
    // struct container_lexico *container = obter_tokens(caminho_do_arquivo);
    
    // // Verifica se a mensagem de erro do container léxico é nula, caso contrário imprimi
    // // a mensagem para o usuário.
    // if(container->mensagem_de_erro != NULL)
    // {
    //     printf(KRED "%s\n\n" RESET, container->mensagem_de_erro);
    // }
    
    return 0;
}