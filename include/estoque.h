#ifndef TRABALHO_FINAL_PROG_II_ESTOQUE_H
#define TRABALHO_FINAL_PROG_II_ESTOQUE_H

#include <libprg/libprg.h>

typedef struct material {
    int id;
    char insumo[200];
    char marca[100];
    char especificacoes[200];
    int quantidade;
    float valor_unitario;
    char local[200];
} material;

#endif //TRABALHO_FINAL_PROG_II_ESTOQUE_H

