#include "arquivo.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static void salvar_estoque_rec(no_avl_t* raiz, FILE* arquivo) {
    if (raiz== NULL) {
        return;
    }
    salvar_estoque_rec(raiz->esquerda, arquivo);
    const material* mat = raiz->dado;
    fprintf(arquivo, "%d;%s;%s;%s;%.2lf;%.2f;%s\n",
           mat->id,
           mat->insumo,
           mat->marca,
           mat->especificacoes,
           mat->quantidade,
           mat->valor_unitario,
           mat->local);
    salvar_estoque_rec(raiz->direita, arquivo);
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

no_avl_t* carregar_estoque(const char* relatorio_estoque) {
    int lidos = 0;
    int contador = 0;
    no_avl_t* raiz = NULL;

    FILE* arquivo = fopen(relatorio_estoque, "r");
    if (arquivo == NULL) {
        return NULL;
    }
    char linha[1024];
    if (fgets(linha, sizeof(linha), arquivo) != NULL) {
        sscanf(linha, "%d", &contador);
    }
    else {
        fclose(arquivo);
        return NULL;
    }
    while (fgets(linha, sizeof(linha), arquivo) != NULL) {
        if (strcmp(linha, "\n") == 0) {
            continue;
        }
        material* mat = (material*) malloc(sizeof(material));
        if (mat == NULL) {
            break;
        }
        lidos=sscanf(linha, "%d;%199[^;];%99[^;];%199[^;];%lf;%f;%199[^\n]", &mat->id,
            mat->insumo, mat->marca, mat->especificacoes, &mat->quantidade, &mat->valor_unitario, mat->local);
        if (lidos != 7) {
            printf("Uma linha foi ignorada\n");
            free(mat);
            continue;
        }
        raiz = inserir_na_arvore_avl(raiz, mat->id, mat);

    }
    definir_proximo_id(contador);
    fclose(arquivo);
    return raiz;
}