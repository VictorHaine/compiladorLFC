#include <stdio.h>
#include <stdlib.h>
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

char* tipo_lexema_nome[] = {
    
    "ID",
    "Inteiro",
    "Duplo",
    "Char",
    "Operador Soma",
    "Operador Soma Um",
    "Operador Subtração",
    "Operador Subtrair Um",
    "Operador Multiplicação",
    "Operador Divisão",
    "Operador Potência",
    "Operador Atribuição",
    "Operador Igualdade",
    "Operador Desigualdade",
    "Operador Menor que",
    "Operador Maior que",
    "Operador Menor Igual que",
    "Operador Maior Igual que",
    "Operador E",
    "Operador OU",
    "Fim de Declaração",
    "Abre Parenteses",
    "Fecha Parenteses",
    "Início de Escopo",
    "Fim de Soma",
    "Início de Loop",
    "Fim de Loop"
};

int inserir_token(struct lista_de_tokens *p_lista, struct token *p_token)
{
    if(p_lista->inicio == NULL)
    {
        p_lista->inicio = p_token;
    }
    
    p_token->prox = NULL;
    p_token->ant = p_lista->atual;
    
    if(p_lista->atual != NULL)
        p_lista->atual->prox = p_token;
    
    p_lista->atual = p_token;
    p_lista->n_elementos++;
    
    return 1;
}

int remover_token(struct lista_de_tokens *p_lista, struct token *p_token)
{
    return -1;
}

struct token* buscar_token(struct lista_de_tokens *p_lista, struct token *p_token)
{
    return NULL;
}

void listar_tokens(struct lista_de_tokens *p_lista)
{
    struct token *p = p_lista->inicio;
    int i = 0;
    
    while (p != NULL) {
        
        printf(KBLU "\nToken %03d - Tipo Lexema: %s\n" RESET, i, tipo_lexema_nome[p->tipo_lexema]);
        printf(KMAG "%d : %d - Lexema: %s, Valor: %s, End. Tabela de Símbolos: %p\n" RESET,
                        p->linha, p->coluna, p->simbolo->lexema, p->simbolo->valor, &p->simbolo);
        
        i++;
        p = p->prox;
    }
}