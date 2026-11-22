#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <libprg/libprg.h>
#include "estoque.h"
#include "arquivo.h"
#include "gastos.h"
#include "entrada.h"

#ifdef _WIN32
#include <windows.h>
#endif

#define TAM_TEXTO 100
#define LIMITE_ESTOQUE_BAIXO 10

typedef struct no_pilha {
    material* backup;
    struct no_pilha* prox;
} no_pilha_t;

typedef struct no_lista {
    const material* mat;
    struct no_lista* prox;
} no_lista_t;

static void empilhar_backup(no_pilha_t** topo, const material* original) {
    if (original == NULL) return;

    material* copia = malloc(sizeof(material));
    if (copia == NULL) return;
    memcpy(copia, original, sizeof(material));

    no_pilha_t* novo = malloc(sizeof(no_pilha_t));
    if (novo == NULL) {
        free(copia);
        return;
    }

    novo->backup = copia;
    novo->prox = *topo;
    *topo = novo;
}

static material* desempilhar_backup(no_pilha_t** topo) {
    if (*topo == NULL) return NULL;

    no_pilha_t* removido = *topo;
    material* dados = removido->backup;
    *topo = removido->prox;
    free(removido);

    return dados;
}

static void liberar_pilha_desfazer(no_pilha_t** topo) {
    while (*topo != NULL) {
        material* dados = desempilhar_backup(topo);
        free(dados);
    }
}

static void inserir_fim_lista(no_lista_t** inicio, no_lista_t** fim, const material* mat) {
    no_lista_t* novo = malloc(sizeof(no_lista_t));
    if (novo == NULL) return;

    novo->mat = mat;
    novo->prox = NULL;

    if (*inicio == NULL) {
        *inicio = novo;
        *fim = novo;
    } else {
        (*fim)->prox = novo;
        *fim = novo;
    }
}
