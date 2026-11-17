#ifdef _WIN32
#include <windows.h>
#endif

#include <stdio.h>

int main(void) {
#ifdef _WIN32
    SetConsoleOutputCP(CP_UTF8);
    SetConsoleCP(CP_UTF8);
    #endif

    printf("Sistema de estoque da marcenaria\n");
    printf("Especificações");
    return 0;
}