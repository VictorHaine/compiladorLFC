#include <stdarg.h>
#include <stdio.h>
#include <escritor.h>
#ifdef _WIN32
#include <windows.h>
#endif

char *traduzir_cor_windows(enum cor p_cor)
{
    #ifdef _WIN32
    switch(p_cor)
    {
        case COR_VERMELHO:
            return FOREGROUND_RED;
            break;
            
        case COR_AZUL:
            return FOREGROUND_BLUE;
            break;
            
        case COR_VERDE:
            return FOREGROUND_GREEN;
            break;
            
        default:
            return "";
    }
    #endif
}

char *traduzir_cor_unix(enum cor p_cor)
{
    switch(p_cor)
    {
        case COR_VERMELHO:
            return "\e[31m";
            break;
            
        case COR_VERDE:
            return "\e[32m";
            break;
            
        case COR_AMARELO:
            return "\e[33m";
            break;
        
        case COR_AZUL:
            return "\e[34m";
            break;
        
        case COR_MAGENTA:
            return "\e[35m";
            break;
        
        case COR_CIANO:
            return "\e[36m";
            break;
            
        case COR_BRANCO:
        case COR_PADRAO:
        default:
            return "\e[0m";
            break;
    }
}

void imprimir(const char *format, enum cor p_cor, ... )
{
    char buffer[256];
    va_list args;
    va_start (args, format);
    vsprintf (buffer,format, args);
    va_end (args);
    
    #ifdef _WIN32
        HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
        CONSOLE_SCREEN_BUFFER_INFO consoleInfo;
        WORD saved_attributes;

        GetConsoleScreenBufferInfo(hConsole, &consoleInfo);
        saved_attributes = consoleInfo.wAttributes;
    
        SetConsoleTextAttribute(hConsole, traduzir_cor_windows(p_cor));
        printf(buffer);
    
        SetConsoleTextAttribute(hConsole, saved_attributes);
    #else
        printf("%s%s%s", traduzir_cor_unix(p_cor), buffer, traduzir_cor_unix(COR_PADRAO));
    #endif
}