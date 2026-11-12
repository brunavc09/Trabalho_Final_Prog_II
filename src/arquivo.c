//
// Created by aluno on 12/11/2026.
//

#include "../include/arquivo.h"
#include <stdio.h>

static void salvar_estoque_rec(no_avl_t* raiz, FILE* arquivo) {
    if (raiz== NULL) {
        return;
    }
    salvar_estoque_rec(raiz->esquerda, arquivo);
    const material* mat = raiz->dado;
    fprintf(arquivo, "%d\n%s\n%s\n%s\n%d\n%.2f\n%s\n",
           mat->id,
           mat->insumo,
           mat->marca,
           mat->especificacoes,
           mat->quantidade,
           mat->valor_unitario,
           mat->local);
    salvar_estoque_rec(raiz->esquerda, arquivo);
}

void salvar_estoque(no_avl_t* raiz, const char* relatorio_estoque ) {
    FILE* arquivo = fopen(relatorio_estoque, "w");
    if (arquivo == NULL) {
        printf("Erro ao abrir o arquivo\n");
        return;
    }
    fprintf(arquivo,"%d\n", obter_proximo_id());
    salvar_estoque_rec(raiz, arquivo);
    fclose(arquivo);
}
