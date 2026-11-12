#include "estoque.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static int proximo_id = 1;

static void buscar_nome_rec(no_avl_t* no, const char * texto) {
    if (no == NULL) {
        return;
    }
    buscar_nome_rec(no->esquerda, texto);
    material* mat = no->dado;
    if ( strstr(mat->insumo, texto) != NULL ) {
        printf("Id do produto: %d\n", mat->id);
        printf("Nome: %s\n", mat->insumo);
        printf("Especificações: %s\n", mat->especificacoes);
        printf("Quantidade: %2lf\n", mat->quantidade);
        printf("Onde esta guardado\n", mat->local);
    }
    buscar_nome_rec(no->direita, texto);
}

material *buscar_por_id(no_avl_t *raiz, int id) {
    no_avl_t *no_encontrado = buscar_na_arvore_avl(raiz, id);
    if (no_encontrado == NULL) {
        return NULL;
    } else {
        return (material *) no_encontrado->dado;
    }
}

no_avl_t *cadastrar_material(no_avl_t *raiz, material *novo) {
    if (novo == NULL) {
        return raiz;
    }
    novo->id = proximo_id;
    proximo_id++;
    return inserir_na_arvore_avl(raiz, novo->id, novo);
}

no_avl_t* remover_material(no_avl_t* raiz, int id) {
    material* material_encontrado = buscar_por_id(raiz, id);
    if (material_encontrado == NULL) {
        return raiz;
    }
    no_avl_t* nova_raiz = remover_da_arvore_avl(raiz, id);
    free(material_encontrado);
    return nova_raiz;
}

int obter_proximo_id(void) {
    return proximo_id;
}
void definir_proximo_id(int novo_id) {
    proximo_id = novo_id;
}