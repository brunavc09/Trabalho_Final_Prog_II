#ifdef _WIN32
#include <windows.h>
#endif

#include <stdio.h>

int main(void) {
#ifdef _WIN32
    SetConsoleOutputCP(CP_UTF8);
    SetConsoleCP(CP_UTF8);
    #endif

    int opcao;
    printf("Sistema de estoque da marcenaria\n");
    printf("Especificações");
    do {
        printf("_______________________________\n");
        printf("Selecione a opção desejada:\n");
        printf("1. Adicionar ao estoque;\n");
        printf("2. Remover do estoque;\n");
        printf("3. Imprimir estoque;\n");
        printf("4. Verificar despesas;\n");
        printf("5. Sair;\n");
        printf("_______________________________\n");
        scanf("%d", &opcao);
        if (opcao > 5 || opcao < 1) {
            printf("A opção selecionada não existe. Tente novamente.\n");
        }
    } while (opcao!=5);
    return 0;
}