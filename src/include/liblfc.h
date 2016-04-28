// #include <stdbool.h>

// #ifndef LIBLFC_HEADER
// #define LIBLFC_HEADER

// /* ENUMS */
// enum tipo_lexema
// {
//     L_ID, L_INT, L_DOUBLE, L_CHAR,
//     L_MAIS, L_MENOS, L_VEZES, L_POTENCIA, L_EQOP,
//     L_INICIO_ESCOPO, L_FIM_ESCOPO, L_INICIO_LOOP, L_FIM_LOOP
// };	

// /* TYPEDEF */

// /* Source File - Representa um arquivo de código fonte. */
// typedef struct _LFCSourceFile
// {
//     char* file_path;
//     char* file_content;
//     long file_size;
//     bool is_file_loaded;
    
//     bool  (*LoadFile)           (void* self, char* p_file_path);
//     char* (*GetFileContent)     (void* self);
//     long  (*GetFileSize)        (void* self);
//     bool  (*GetIsFileLoaded)    (void* self);
// } LFCSourceFile;

// /* Lexema - Representa uma únidade básica de análise léxicas, com seus tipo,
//  * endereço do valor na tabela de símbolos, linha e coluna do primeiro caractér.
//  */
// typedef struct _LFCLexema
// {
//     enum tipo_lexema tipo;
//     struct _LFCLexema* prox;
//     struct _LFCLexema* ant;
//     int* LFCToken;
//     int linha;
//     int coluna;
// } LFCLexema;


// typedef struct _LFCToken
// {
    
// } LFCEntradaTS;


// /* Tabela de Símbolos - Representa uma estrutura que guarda todos os endereços 
//  * de valor dos lexemas processados.
//  */
// typedef struct _LFCTabelaDeSimbolos
// {
//     int tamanho;
    
//     LFCLexema* head;
// } LFCTabelaDeSimbolos;


// typedef struct _LFCAnalisadorLexico
// {
//     LFCSourceFile* lfc_source_file;
    
//     LFCTabelaDeSimbolos* (*GetSymbolTable)      (void* self);
//     void                 (*PrintSymbolTable)    (void* self);
// } LFCAnalisadorLexico;


// /* CONSTRUTORES */

// /* New LFC Source File - Cria um novo "objeto" do tipo Source File e retorna um
//  * ponteiro do endereço de memória associado.
//  */
// LFCSourceFile* NewLFCSourceFile();

// LFCAnalisadorLexico* NewLFCAnalisadorLexico(LFCSourceFile* p_lfc_source_file);

// #endif