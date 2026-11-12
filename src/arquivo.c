//
// Created by aluno on 12/11/2026.
//

#include "../include/arquivo.h"

#include <stdio.h>

static void salvar_estoque_rec(no_avl_t* raiz, FILE* arquivo) {
    if (raiz== NULL) {
        return;
    }
    buscar_por_nome()
}
void salvar_estoque(no_avl_t* raiz, const char* relatorio_estoque ) {
    definir_proximo_id(raiz);
    FILE* arquivo = fopen(relatorio_estoque, "w");
    if (arquivo == NULL) {
        printf("Erro ao abrir o arquivo\n");
        return;
    }



}
