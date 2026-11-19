#include <stdio.h>
#include <stdlib.h>
#include <libprg/libprg.h>
#include "estoque.h"
#include "arquivo.h"
#include "gastos.h"
#include "entrada.h"

#ifdef _WIN32
#include <windows.h>
#endif

static void liberar_arvore_estoque(no_avl_t* raiz) {
    if (raiz == NULL) {
        return;
    }
    liberar_arvore_estoque(raiz->esquerda);
    liberar_arvore_estoque(raiz->direita);
    free(raiz->dado);
    free(raiz);
}

int main(void) {
    #ifdef _WIN32
    SetConsoleOutputCP(CP_UTF8);
    SetConsoleCP(CP_UTF8);
    #endif

    const char* NOME_ARQUIVO = "estoque.txt";
    no_avl_t* raiz = carregar_estoque(NOME_ARQUIVO);
    int opcao = 0;

    while (1) {
        printf("\n=== CONTROLE DE ESTOQUE - MARCENARIA ===\n");
        printf("1. Cadastrar material\n");
        printf("2. Listar materiais\n");
        printf("3. Buscar / Editar / Movimentar\n");
        printf("4. Calcular custos de producao\n");
        printf("5. Sair\n");

        if (!ler_inteiro("Escolha uma opcao: ", &opcao)) {
            printf("\nEntrada encerrada.\n");
            opcao = 5;
        }

        if (opcao == 5) {
            printf("Salvando estoque e encerrando...\n");
            salvar_estoque(raiz, NOME_ARQUIVO);
            liberar_arvore_estoque(raiz);
            break;
        }

        switch (opcao) {
            case 1:
                printf("Em construcao.\n");
                break;
            case 2:
                listar_materiais(raiz);
                break;
            case 3:
                printf("Em construcao.\n");
                break;
            case 4:
                printf("Em construcao.\n");
                break;
            default:
                printf("Opcao inexistente. Tente novamente.\n");
                break;
        }
    }

    return 0;
}
