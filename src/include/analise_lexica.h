#ifndef LFC_ANALISE_LEXICA
#define LFC_ANALISE_LEXICA

#include "leitor_de_arquivos.h"
#include "token.h"
#include "tabela_de_simbolos.h"

struct container_lexico
{
	struct lista_de_tokens *lista_de_tokens;
	struct tabela_de_simbolos *tabela_de_simbolos;
    char *mensagem_de_erro;
};

struct container_lexico* obter_tokens(char *p_caminho);


#endif