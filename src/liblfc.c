// #include <stdio.h>
// #include <stdlib.h>
// #include "liblfc.h"

// bool f_LoadFile(LFCSourceFile* self, char* p_file_path)
// {
//     if(p_file_path == NULL)
//         return false;
    
//     self->file_path = p_file_path;
//     FILE* file = fopen(self->file_path, "rb");
    
//     if(!file)
//         return false;
    
//     fseek(file, 0, SEEK_END);
//     self->file_size = ftell(file);
//     rewind(file);
    
//     if(self->file_size == -1)
//         return false;
    
//     self->file_content = malloc(self->file_size+1);
//     fread(self->file_content, self->file_size, 1, file);
//     fclose(file);

//     self->is_file_loaded = true;
//     return true;
// }

// char* f_GetFileContent(LFCSourceFile* self)
// {
//     return self->file_content;
// }

// long f_GetFileSize(LFCSourceFile* self)
// {
//     return self->file_size;
// }

// bool f_GetIsFileLoaded(LFCSourceFile* self)
// {
//     return self->is_file_loaded;
// }

// LFCSourceFile* NewLFCSourceFile()
// {
//     LFCSourceFile* s = malloc(sizeof(LFCSourceFile));
//     s->LoadFile = &f_LoadFile;
//     s->GetFileContent = &f_GetFileContent;
//     s->GetFileSize = &f_GetFileSize;
//     s->GetIsFileLoaded = &f_GetIsFileLoaded;
    
//     return s;
// }



// LFCTabelaDeSimbolos* f_GetSymbolTable(LFCAnalisadorLexico* self)
// {
//     LFCTabelaDeSimbolos ts = malloc(sizeof(LFCTabelaDeSimbolos));
//     LFCLexema a = malloc(sizeof(LFCLexema));
//     LFCLexema b = malloc(sizeof(LFCLexema));
    
//     a.tipo = (enum tipo_lexema)L_INT;
//     a.prox = b;
//     a.ant = null;
    
//     enum tipo_lexema tipo;
//     struct _LFCLexema* prox;
//     struct _LFCLexema* ant;
//     int* entrada_ts;
//     int linha;
//     int coluna;
// }

// LFCTabelaDeSimbolos* (*GetSymbolTable)      (void* self);
//     void                 (*PrintSymbolTable)    (void* self);



// LFCAnalisadorLexico* NewLFCAnalisadorLexico(LFCSourceFile* p_lfc_source_file);