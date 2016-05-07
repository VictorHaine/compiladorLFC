#ifndef LFC_TOKEN
#define LFC_TOKEN

//#include "tabela_de_simbolos.h"

enum tipo_lexema
{
	LEXEMA_ID,
	LEXEMA_INT,
	LEXEMA_DOUBLE,
	LEXEMA_CHAR,
    LEXEMA_STRING,
	LEXEMA_OP_SOMA,
    LEXEMA_OP_SOMA_UM,
	LEXEMA_OP_SUBTRACAO,
    LEXEMA_OP_SUBTRAI_UM,
	LEXEMA_OP_MULTIPLICACAO,
    LEXEMA_OP_DIVISAO,
	LEXEMA_OP_POTENCIA,
    LEXEMA_OP_ATRIBUICAO,
	LEXEMA_OP_IGUALDADE,
    LEXEMA_OP_DESIGUALDADE,
    LEXEMA_OP_MENOR_QUE,
    LEXEMA_OP_MAIOR_QUE,
    LEXEMA_OP_MENOR_IGUAL_QUE,
    LEXEMA_OP_MAIOR_IGUAL_QUE,
    LEXEMA_OP_E,
    LEXEMA_OP_OU,
    LEXEMA_FIM_DECLARACAO,
    LEXEMA_ABRE_PARENTESES,
    LEXEMA_FECHA_PARENTESES,
	LEXEMA_INICIO_ESCOPO,
	LEXEMA_FIM_ESCOPO,
	LEXEMA_INICIO_LOOP,
	LEXEMA_FIM_LOOP
};

extern char* tipo_lexema_nome[];

struct token
{
	enum tipo_lexema tipo_lexema;
	struct simbolo *simbolo;

	struct token *prox;
	struct token *ant;

	unsigned int linha;
	unsigned int coluna;
};

struct lista_de_tokens
{
	struct token *inicio;
	struct token *atual;
	unsigned int n_elementos;
};

int inserir_token(struct lista_de_tokens *p_lista, struct token *p_token);
int remover_token(struct lista_de_tokens *p_lista, struct token *p_token);
struct token* buscar_token(struct lista_de_tokens *p_lista, struct token *p_token);
void listar_tokens(struct lista_de_tokens *p_lista, char *p_caminho_arquivo);

#endif












