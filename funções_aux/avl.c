//
// Created by bruna on 06/11/2026.
//

#include "avl.h"
#include <stdio.h>
#include <stdlib.h>

No* remover_no(No *raiz, int dados) {
    if (raiz == NULL) return NULL;

    if (dados < raiz->dados) {
        raiz->esquerda = remover_no(raiz->esquerda, dados);
    }
    else if (dados > raiz->dados) {
        raiz->direita = remover_no(raiz->direita, dados);
    }
    else {
        if (raiz->esquerda == NULL && raiz->direita == NULL) {
            free(raiz);
            return NULL;
        }
        else if (raiz->esquerda == NULL) {
            No *aux = raiz->direita;
            free(raiz);
            return aux;
        }
        else if (raiz->direita == NULL) {
            No *aux = raiz->esquerda;
            free(raiz);
            return aux;
        }
        else {
            No *sucessor = raiz->direita;
            while (sucessor->esquerda != NULL)
                sucessor = sucessor->esquerda;

            raiz->dados = sucessor->dados;
            raiz->direita = remover_no(raiz->direita, sucessor->dados);
        }

    }
    return raiz;
}

No* inserir_no(No *raiz,int valor) {
    if (raiz == NULL) {
        No *aux = malloc(sizeof(No));
        if (aux == NULL) {
            return NULL;
        }
        aux->dados = valor;
        aux->esquerda = NULL;
        aux->direita = NULL;
        return aux;
    }
    else {
        if (valor < raiz->dados) {
            raiz->esquerda = inserir_no(raiz->esquerda, valor);
        }
        else if (valor > raiz->dados) {
            raiz->direita = inserir_no(raiz->direita, valor);
        }
        return raiz;
    }
}

No* buscar(No *raiz, int info) {
    if (raiz == NULL) {
        return NULL;
    }
    else {
        if (raiz->dados == info) {
            return raiz;
        }
        else {
            if (info > raiz->dados) {
                return buscar(raiz->direita, info);
            }
            else {
                return buscar(raiz->esquerda, info);
            }
        }
    }
}


void pre_ordem(No *raiz) {
    if (raiz == NULL) {
        return;
    }
    printf("%d ",raiz->dados);
    pre_ordem(raiz->esquerda);
    pre_ordem(raiz->direita);
}

void em_ordem(No *raiz) {
    if (raiz==NULL) {
        return;
    }
    em_ordem(raiz->esquerda);
    printf("%d ",raiz->dados);
    em_ordem(raiz->direita);
}

void pos_ordem(No *raiz) {
    if (raiz == NULL) {
        return;
    }
    pos_ordem(raiz->esquerda);
    pos_ordem(raiz->direita);
    printf("%d ",raiz->dados);
}
