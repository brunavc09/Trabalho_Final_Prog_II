// Created by aluno on 03/11/2026.
//

#ifndef TRABALHO_FINAL_PROG_II_GASTOS_H
#define TRABALHO_FINAL_PROG_II_GASTOS_H

#include <libprg/libprg.h>
#include "estoque.h"

double custos_parciais(material *componente, double qtd_utilizada);
double custos_totais(int total_insumos,no_avl_t *raiz);

#endif //TRABALHO_FINAL_PROG_II_GASTOS_H