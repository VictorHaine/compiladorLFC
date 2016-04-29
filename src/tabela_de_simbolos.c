#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "tabela_de_simbolos.h"
#include "token.h"

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

void listar_simbolos(struct tabela_de_simbolos *p_tabela, char *p_caminho_arquivo)
{
    
    
    // struct token *p = p_lista->inicio;
    // int i = 0;
    
    // while (p != NULL) {
        
    //     imprimir(COR_AZUL, "\nToken %03d - Tipo Lexema: %s\n", i, tipo_lexema_nome[p->tipo_lexema]);
    //     imprimir(COR_MAGENTA, "%d : %d - Lexema: %s, Valor: %s, End. Tabela de Símbolos: %p\n",
    //                     p->linha, p->coluna, p->simbolo->lexema, p->simbolo->valor, &p->simbolo);
        
    //     i++;
    //     p = p->prox;
    // }
}