#ifndef LFC_TABELA_DE_SIMBOLOS
#define LFC_TABELA_DE_SIMBOLOS

struct simbolo
{
	char *lexema;
	char *valor;
	char *atributos;

	struct simbolo *prox;
	struct simbolo *ant;
};

struct tabela_de_simbolos
{
	struct simbolo *inicio;
	struct simbolo *atual;
	unsigned int n_elementos;
};

int inserir_simbolo(struct tabela_de_simbolos *p_tabela, struct simbolo *p_simbolo);
struct simbolo* obter_simbolo(struct tabela_de_simbolos *p_tabela, char *lexema, char *valor);
void listar_simbolos(struct tabela_de_simbolos *p_tabela, char *p_caminho_arquivo);

#endif