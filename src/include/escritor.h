#ifndef LFC_ESCRITOR
#define LFC_ESCRITOR

#include <stdarg.h>
#include <stdio.h>

enum cor {
  COR_PADRAO,
  COR_VERMELHO,
  COR_VERDE,
  COR_AMARELO,
  COR_AZUL,
  COR_MAGENTA,
  COR_CIANO,
  COR_BRANCO
};

char *traduzir_cor_unix(enum cor p_cor);
int traduzir_cor_windows(enum cor p_cor);
void imprimir(enum cor p_cor, const char *format, ... );
int inserir_arquivo(char *p_conteudo, char *p_caminho_arquivo);

#endif