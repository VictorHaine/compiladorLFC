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
    "String",
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

/**
 *  Função para inserir um Token em uma lista de tokens
 *
 *  @param p_lista Lista de Tokens
 *  @param p_token Token
 *
 *  @return 1 = sucesso
 */
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

/**
 *  TODO:
 *  Função para remover um Token de uma lista de tokens
 *
 *  @param p_lista Lista de Tokens
 *  @param p_token Token
 *
 *  @return 1 = sucesso
 */
int remover_token(struct lista_de_tokens *p_lista, struct token *p_token)
{
    return -1;
}

/**
 *  TODO:
 *  Função para buscar um Token em uma lista de tokens
 *
 *  @param p_lista Lista de Tokens
 *  @param p_token Token
 *
 *  @return 1 = sucesso
 */
struct token* buscar_token(struct lista_de_tokens *p_lista, struct token *p_token)
{
    return NULL;
}


/**
 *  Procedimento para listar os tokens existentes numa lista de tokens, e caso o parâmetro
 *  p_caminho_arquivo seja diferente de nulo, escrever a lista de tokens no arquivo.
 *
 *  @param p_lista           Lista de Tokens
 *  @param p_caminho_arquivo Caminho do arquivo para output dos tokens
 */
void listar_tokens(struct lista_de_tokens *p_lista, char *p_caminho_arquivo)
{   
    struct token *p = p_lista->inicio;
    int i = 0;
    
    // Imprime os Tokens no STDOUT
    while (p != NULL) {
        imprimir(COR_AZUL, "\nToken %03d - Tipo Lexema: %s\n", i, tipo_lexema_nome[p->tipo_lexema]);
        imprimir(COR_MAGENTA, "%d : %d - Lexema: %s, Valor: %s, End. Tabela de Símbolos: %p\n",
                        p->linha, p->coluna, p->simbolo->lexema, p->simbolo->valor, &p->simbolo);
        
        i++;
        p = p->prox;
    }

    // Imprime os Tokens no arquivo correspondente ao p_caminho_arquivo
    if(p_caminho_arquivo != NULL)
    {
        int len = 0;
        int tamanho_buffer = 4096;
        char *buffer = calloc(sizeof(char), tamanho_buffer);
        p = p_lista->inicio;
        
        len += sprintf(len+buffer, " ¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯ Lista de Tokens ¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯");
        len += sprintf(len+buffer, "\n ______________________________________________________________________________________________________ \n");
        len += sprintf(len+buffer, "|  TOKEN |     Tipo de Lexema     |  Lexema  | Linha | Coluna |     Valor    | End. Tabela de Símbolos |\n");
        len += sprintf(len+buffer, " ¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯ \n");
        
        while (p != NULL) {
            len += sprintf(len+buffer, "|   %-3.2d  | %-22s |  %-6s  |  %-4.3d |  %-4.3d  |  %-10s  | %-23p |\n",
                            i, tipo_lexema_nome[p->tipo_lexema],
                            p->simbolo->lexema, p->linha, p->coluna,
                            p->simbolo->valor, &p->simbolo);
            
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
        
        // Função para escrever no arquivo correspondente ao p_caminho_arquivo
        inserir_arquivo(buffer, p_caminho_arquivo);
    }   
}