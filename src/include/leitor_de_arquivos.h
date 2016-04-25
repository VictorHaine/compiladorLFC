#ifndef LFC_LEITOR_DE_ARQUIVOS
#define LFC_LEITOR_DE_ARQUIVOS

struct arquivo
{
    char *caminho;
	char *conteudo;
	unsigned long tamanho;
};

int carregar_arquivo(struct arquivo *p_arquivo, char *p_caminho);


#endif