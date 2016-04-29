#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "escritor.h"
#include "tabela_de_simbolos.h"
#include "token.h"

char* tipo_lexema_nome[] = {
    "ID",
    "Inteiro",
    "Duplo",
    "Char",
    "Operador Soma",
    "Operador Soma Um",
    "Operador Subtracao",
    "Operador Subtrair Um",
    "Operador Multiplicacao",
    "Operador Divisao",
    "Operador Potencia",
    "Operador Atribuicao",
    "Operador Igualdade",
    "Operador Desigualdade",
    "Operador Menor que",
    "Operador Maior que",
    "Operador Menor Igual que",
    "Operador Maior Igual que",
    "Operador E",
    "Operador OU",
    "Fim de Declaracao",
    "Abre Parenteses",
    "Fecha Parenteses",
    "Inicio de Escopo",
    "Fim de Soma",
    "Inicio de Loop",
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

void listar_tokens(struct lista_de_tokens *p_lista, char *p_caminho_arquivo)
{   
    struct token *p = p_lista->inicio;
    int i = 0;
    
    if(p_caminho_arquivo == NULL)
    {
        while (p != NULL) {
            imprimir(COR_AZUL, "\nToken %03d - Tipo Lexema: %s\n", i, tipo_lexema_nome[p->tipo_lexema]);
            imprimir(COR_MAGENTA, "%d : %d - Lexema: %s, Valor: %s, End. Tabela de Símbolos: %p\n",
                            p->linha, p->coluna, p->simbolo->lexema, p->simbolo->valor, &p->simbolo);
            
            i++;
            p = p->prox;
        }
    }
    else
    {
        int len = 0;
        int tamanho_buffer = 4096;
        char *buffer = calloc(sizeof(char), tamanho_buffer);
        
        len += sprintf(len+buffer, "\n ______________________________________________________________________________________________________ \n");
        len += sprintf(len+buffer, "|  TOKEN |     Tipo de Lexema     |  Lexema  | Linha | Coluna |     Valor    | End. Tabela de Símbolos |\n");
        len += sprintf(len+buffer, " ¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯ \n");
        
        while (p != NULL) {
            len += sprintf(len+buffer, "|   %-3.2d  | %-22s |  %-6s  |  %-4.3d |  %-4.3d  |  %-10s  | %-23p |\n",
                            i, tipo_lexema_nome[p->tipo_lexema],
                            p->simbolo->lexema, p->linha, p->coluna,
                            p->simbolo->valor, &p->simbolo);
            
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
        
        inserir_arquivo(buffer, "output/test1b.txt");
        // printf("%s", buffer);
        
    }
    
    
}