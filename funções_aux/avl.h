//
// Created by bruna on 06/11/2026.
//

#ifndef TRABALHO_FINAL_PROG_II_AVL_H
#define TRABALHO_FINAL_PROG_II_AVL_H

typedef struct No{
    int dados;
    struct No *esquerda;
    struct No *direita;
}No;

No* remover_no(No *raiz, int dados);
No* inserir_no(No *raiz,int valor);
No* buscar(No *raiz, int info);
void pre_ordem(No *raiz);
void em_ordem(No *raiz);
void pos_ordem(No *raiz);

#endif //TRABALHO_FINAL_PROG_II_AVL_H
