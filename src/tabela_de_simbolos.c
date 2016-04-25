#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "tabela_de_simbolos.h"
#include "token.h"

#define KNRM  "\e[0m"
#define KRED  "\e[31m"
#define KGRN  "\e[32m"
#define KYEL  "\e[33m"
#define KBLU  "\e[34m"
#define KMAG  "\e[35m"
#define KCYN  "\e[36m"
#define KWHT  "\e[37m"
#define RESET "\e[0m"

//struct simbolo
//{
//    char *lexema;
//    char *valor;
//    char *atributos;
//    
//    struct simbolo *prox;
//    struct simbolo *ant;
//};
//
//struct tabela_de_simbolos
//{
//    struct simbolo *inicio;
//    struct simbolo *atual;
//    unsigned int n_elementos;
//};


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

void listar_simbolos(struct tabela_de_simbolos *p_tabela)
{
    
}