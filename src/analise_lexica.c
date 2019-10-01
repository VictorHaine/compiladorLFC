#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include <time.h>
#include "analise_lexica.h"
#include "leitor_de_arquivos.h"
#include "tabela_de_simbolos.h"
#include "token.h"
#include "escritor.h"

/**
 *  Procedimento para "adicionar" um caractere no fim de uma lista
 *  de caracteres.
 *
 *  @param s Lista de caracteres
 *  @param c Caractere
 */
void append(char *s, char c)
{
    if(s == NULL)
        return;
    
    for (;*s;s+=1);
    
    *s++ = c; 
    *s++ = 0;
}

/**
 *  Procedimento para limpar uma lista de caracteres.
 *
 *  @param s Endereço do endereço da lista de caracteres
 */
void clean(char **s)
{
    *s = calloc(sizeof(char), 255);
}

/**
 *  Função para identificar os tokens e gerar a tabela de símbolos.
 *
 *  @param p_caminho Caminho do arquivo com o código a ser analisado.
 *
 *  @return Container léxico com os tokens, tabela de símbolos e ocasionalmente
 *          uma mensagem de erro.
 */
struct container_lexico* obter_tokens(char *p_caminho)
{
    // Aloca espaço em memória para um container léxico, será o retorno da função.
    struct container_lexico *container = malloc(sizeof(struct container_lexico));
    container->mensagem_de_erro = NULL;
    
    // Aloca espaço em memória para o arquivo que estamos analisando.
    struct arquivo *arq = malloc(sizeof(struct arquivo));
    
    if(!carregar_arquivo(arq, p_caminho))
    {
        container->mensagem_de_erro = "Não foi possível carregar o arquivo.";
        return container;
    }
    
    // Exibe o tamanho do arquivo a ser analisado em bytes.
    imprimir(COR_MAGENTA, "Arquivo \"%s\" - %lu bytes\n\n", arq->caminho, arq->tamanho);
    
    // Exibe o conteúdo do arquivo
    imprimir(COR_AZUL, "\nConteúdo:");
    imprimir(COR_CIANO, "\n%s", arq->conteudo);
    
    // Variáveis de controle de posição
    int linha = 1;
    int coluna = 1;
    
    // Buffer
    char *buffer;
    clean(&buffer);
    
    char *nameBuffer;
    clean(&nameBuffer);
    
    // Lista de Tokens
    struct lista_de_tokens *lista_de_tokens = malloc(sizeof(struct lista_de_tokens));
    lista_de_tokens->inicio = NULL;
    lista_de_tokens->atual = NULL;
    
    // Tabela de Símbolos
    struct tabela_de_simbolos *tabela_de_simbolos = malloc(sizeof(struct tabela_de_simbolos));
    tabela_de_simbolos->inicio = NULL;
    tabela_de_simbolos->atual = NULL;
    
    int n_strings = 0;
    
    for (int i = 0; i < arq->tamanho; i++)
    {
        // Checa comentários definidos por //
        if(arq->conteudo[i] == '/')
        {
            if(arq->conteudo[i+1] == '/')
            {
                while (arq->conteudo[i] != '\n') {
                    i++;
                }
                //linha++;
            }
        }
        
        // Checa quebras de linha, incrementa o número de linhas e reseta a coluna
        else if(arq->conteudo[i] == '\n')
        {
            coluna = 0;
            linha  = linha + 1;
            continue;
        }
        
        else if(arq->conteudo[i] == '"')
        {
            i++;
            int col_temp = coluna;
            
            while (arq->conteudo[i] != '\"' && arq->conteudo[i] != '\0') {
                append(buffer, arq->conteudo[i]);
                coluna++;
                i++;
            }
            
            sprintf(nameBuffer, "string%d", n_strings);
            
            struct token *token = malloc(sizeof(struct token));
            token->tipo_lexema = LEXEMA_STRING;
            token->simbolo = obter_simbolo(tabela_de_simbolos, nameBuffer, buffer);
            token->linha = linha;
            token->coluna = col_temp;

            n_strings++;
            i++;
            
            inserir_token(lista_de_tokens, token);
            
            clean(&nameBuffer);
            clean(&buffer);
            
        }
        
        else if(isdigit(arq->conteudo[i]))
        {
            append(buffer, arq->conteudo[i]);
            int col_temp = coluna;
            
            i++;
            
            while (isdigit(arq->conteudo[i]))
            {
                append(buffer, arq->conteudo[i]);
                i++;
                coluna++;
            }
            
            struct token *token = malloc(sizeof(struct token));
            token->tipo_lexema = LEXEMA_INT;
            token->simbolo = obter_simbolo(tabela_de_simbolos, buffer, buffer);
            token->linha = linha;
            token->coluna = col_temp;
            
            coluna++;
            
            inserir_token(lista_de_tokens, token);
            
            clean(&buffer);
        }
        
        else if(arq->conteudo[i] == '_' || isalnum(arq->conteudo[i]))
        {
            append(buffer, arq->conteudo[i]);
            int col_temp = coluna;
            
            while (isalnum(arq->conteudo[i+1]))
            {
                append(buffer, arq->conteudo[i+1]);
                i++;
                coluna++;
            }
            
            struct token *token = malloc(sizeof(struct token));
            token->tipo_lexema = LEXEMA_ID;
            token->simbolo = obter_simbolo(tabela_de_simbolos, buffer, NULL);
            token->linha = linha;
            token->coluna = col_temp;
            
            coluna++;
            
            inserir_token(lista_de_tokens, token);
            
            clean(&buffer);

        }
        
        else if(ispunct(arq->conteudo[i]))
        {
            append(buffer, arq->conteudo[i]);
            
            struct token *token = malloc(sizeof(struct token));
            token->simbolo = obter_simbolo(tabela_de_simbolos, buffer, NULL);
            token->linha = linha;
            token->coluna = coluna;
            
            switch (arq->conteudo[i]) {
                case '+':
                    if(arq->conteudo[i+1]=='+')
                    {
                        append(buffer, arq->conteudo[i+1]);
                        token->tipo_lexema = LEXEMA_OP_SOMA_UM;
                        i++;
                        coluna++;
                    }
                    else
                        token->tipo_lexema = LEXEMA_OP_SOMA;
                    break;
                    
                case '-':
                    if(arq->conteudo[i+1]=='-')
                    {
                        append(buffer, arq->conteudo[i+1]);
                        token->tipo_lexema = LEXEMA_OP_SUBTRAI_UM;
                        i++;
                        coluna++;
                    }
                    else
                        token->tipo_lexema = LEXEMA_OP_SUBTRACAO;
                    break;
                    
                case '*':
                    if(arq->conteudo[i+1]=='*')
                    {
                        append(buffer, arq->conteudo[i+1]);
                        token->tipo_lexema = LEXEMA_OP_POTENCIA;
                        i++;
                        coluna++;
                    }
                    else
                        token->tipo_lexema = LEXEMA_OP_MULTIPLICACAO;
                    break;
                    
                case '/':
                    token->tipo_lexema = LEXEMA_OP_DIVISAO;
                    break;
                    
                case '=':
                    if(arq->conteudo[i+1]=='=')
                    {
                        append(buffer, arq->conteudo[i+1]);
                        token->tipo_lexema = LEXEMA_OP_IGUALDADE;
                        i++;
                        coluna++;
                    }
                    else if(arq->conteudo[i+1]=='!')
                    {
                        append(buffer, arq->conteudo[i+1]);
                        token->tipo_lexema = LEXEMA_OP_DESIGUALDADE;
                        i++;
                        coluna++;
                    }
                    else
                        token->tipo_lexema = LEXEMA_OP_ATRIBUICAO;
                    break;
                    
                case '<':
                    if(arq->conteudo[i+1]=='=')
                    {
                        append(buffer, arq->conteudo[i+1]);
                        token->tipo_lexema = LEXEMA_OP_MENOR_IGUAL_QUE;
                        i++;
                        coluna++;
                    }
                    else
                        token->tipo_lexema = LEXEMA_OP_MENOR_QUE;
                    break;
                    
                case '>':
                    if(arq->conteudo[i+1]=='=')
                    {
                        append(buffer, arq->conteudo[i+1]);
                        token->tipo_lexema = LEXEMA_OP_MAIOR_IGUAL_QUE;
                        i++;
                        coluna++;
                    }
                    else
                        token->tipo_lexema = LEXEMA_OP_MAIOR_QUE;
                    break;
                    
                case '&':
                    if(arq->conteudo[i+1]=='&')
                    {
                        append(buffer, arq->conteudo[i+1]);
                        token->tipo_lexema = LEXEMA_OP_E;
                        i++;
                        coluna++;
                    }
                    break;
                    
                case '|':
                    if(arq->conteudo[i+1]=='|')
                    {
                        append(buffer, arq->conteudo[i+1]);
                        token->tipo_lexema = LEXEMA_OP_E;
                        i++;
                        coluna++;
                    }
                    break;
                
                case ';':
                    token->tipo_lexema = LEXEMA_FIM_DECLARACAO;
                    break;
                    
                case '(':
                    token->tipo_lexema = LEXEMA_ABRE_PARENTESES;
                    break;
                
                case ')':
                    token->tipo_lexema = LEXEMA_FECHA_PARENTESES;
                    break;
                
                case '{':
                    token->tipo_lexema = LEXEMA_INICIO_ESCOPO;
                    break;
                    
                case '}':
                    token->tipo_lexema = LEXEMA_FIM_ESCOPO;
                    break;
                    
                default:
                    break;
            }
            
            coluna++;
            
            inserir_token(lista_de_tokens, token);
            
            clean(&buffer);
        }
    }
    
    // Caminho do arquivo de output com a tabela de símbolos e lista de tokens
    char *caminhoOutput = calloc(sizeof(char), 255);
    const time_t timer = time(NULL);
    const struct tm *agora = gmtime(&timer);
#ifdef _WIN32
    sprintf(caminhoOutput, "..\\output\\%d_%d_%d.txt", agora->tm_mon, agora->tm_mday, agora->tm_hour);
#else
    sprintf(caminhoOutput, "../output/%d_%d_%d.txt", agora->tm_mon, agora->tm_mday, agora->tm_hour);
#endif
    
    // Listar os Tokens; Enviando no segundo parâmetro o caminho do arquivo a função escreve no arquivo a lista de tokens.
    listar_tokens(lista_de_tokens, caminhoOutput);
    // Listar os Símbolos; Enviando no segundo parâmetro o caminho do arquivo a função escreve no arquivo a Tabela de Símbolos.
    listar_simbolos(tabela_de_simbolos, caminhoOutput);
    
    // Atribui ao container léxico a lista de tokens e a tabela de símbolos
    container->lista_de_tokens = lista_de_tokens;
    container->tabela_de_simbolos = tabela_de_simbolos;
    
    // Container léxico pronto.
    return container;
}
