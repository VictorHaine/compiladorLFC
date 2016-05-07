#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "escritor.h"
#include "tabela_de_simbolos.h"
#include "token.h"

/**
 *  Função para inserir símbolos na tabela de símbolos.
 *
 *  @param p_tabela  Tabela de Símbolos
 *  @param p_simbolo Símbolo
 *
 *  @return 1 = sucesso
 */
int inserir_simbolo(struct tabela_de_simbolos *p_tabela, struct simbolo *p_simbolo)
{
    if(p_tabela->inicio == NULL)
    {
        p_tabela->inicio = p_simbolo;
    }
    
    p_simbolo->prox = NULL;
    p_simbolo->ant = p_tabela->atual;
    
    if(p_tabela->atual != NULL)
        p_tabela->atual->prox = p_simbolo;
    
    p_tabela->atual = p_simbolo;
    p_tabela->n_elementos++;
    
    return 1;
}

/**
 *  Função para buscar um símbolo existente, ou criar um novo símbolo caso não seja encontrado, para
 *  um dado lexema.
 *
 *  @param p_tabela Tabela de Símbolos
 *  @param lexema   Lexema a ser buscado
 *  @param valor    Valor para o símbolo
 *
 *  @return struct simbolo  Retorna o símbolo correspondente ao lexema buscado.
 */
struct simbolo* obter_simbolo(struct tabela_de_simbolos *p_tabela, char *lexema, char *valor)
{
    struct simbolo *simbolo_t = p_tabela->inicio;
    
    while (simbolo_t != NULL) {
        if(strcmp(lexema, simbolo_t->lexema) == 0)
        {
            break;
        }
        
        simbolo_t = simbolo_t->prox;
    }
    
    if(simbolo_t == NULL)
    {
        simbolo_t = malloc(sizeof(struct simbolo));
        simbolo_t->lexema = lexema;
        simbolo_t->valor = valor;
        inserir_simbolo(p_tabela, simbolo_t);
    }
    
    return simbolo_t;
}

/**
 *  Procedimento para exibir os símbolos existentes na Tabela de Símbolos, e caso o parâmetro
 *  p_caminho_arquivo seja diferente de nulo, escrever a tabela de símbolos no arquivo.
 *
 *  @param p_tabela          Tabela de Símbolos
 *  @param p_caminho_arquivo Caminho do arquivo para output dos símbolos
 */
void listar_simbolos(struct tabela_de_simbolos *p_tabela, char *p_caminho_arquivo)
{
    
    struct simbolo *p = p_tabela->inicio;
    int i = 0;
    
    // Imprime os Símbolos no STDOUT
    while (p != NULL) {
        imprimir(COR_AZUL, "\nSimbolo %03d -  Lexema: %s - Valor: %s\n", i, p->lexema, p->valor);
        imprimir(COR_VERDE, "Ant: %p , Prox: %p\n", i, p->ant, p->prox);
        
        i++;
        p = p->prox;
    }
    
    // Imprime os Símbolos no arquivo correspondente ao p_caminho_arquivo
    if(p_caminho_arquivo != NULL)
    {
        int len = 0;
        int tamanho_buffer = 4096;
        char *buffer = calloc(sizeof(char), tamanho_buffer);
        p = p_tabela->inicio;
    
        len += sprintf(len+buffer, " ¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯ Tabela de Simbolos ¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯");
        len += sprintf(len+buffer, "\n ______________________________________________________________________________________________________ \n");
        len += sprintf(len+buffer, "| SIMBOLO |  END. TABELA DE SIMBOLOS  |   LEXEMA   |    VALOR    |    PROX. END.    |     END. ANT     |\n");
        len += sprintf(len+buffer, " ¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯ \n");
        
        while (p != NULL) {
            len += sprintf(len+buffer, "|   %-3i   |      %-15p      |    %-4s    |   %-6s    |  %-14p  |  %-14p  |\n",
                           i, &p, p->lexema, p->valor, p->prox, p->ant);
            
            // Checa se o buffer já foi consumidor em mais de 2/3. Caso positivo, dobra o tamanho do buffer.
            if(len > tamanho_buffer*2/3)
            {
                tamanho_buffer = tamanho_buffer * 2;
                char *temp = calloc(sizeof(char), tamanho_buffer);
                strcpy(temp, buffer);
                free(buffer);
                buffer = calloc(sizeof(char), tamanho_buffer);
                strcpy(buffer, temp);
                free(temp);
            }
            
            i++;
            p = p->prox;
        }
        
        len += sprintf(len+buffer, " ¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯ \n");
        
        // Função para escrever no arquivo correspondente ao p_caminho_arquivo// Função para escrever no arquivo correspondente ao p_caminho_arquivo
        inserir_arquivo(buffer, p_caminho_arquivo);
    }
}