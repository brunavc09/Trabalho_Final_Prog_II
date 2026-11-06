//
// Created by aluno on 03/11/2026.
//

#include "gastos.h"
#include <stdio.h>
#include <libprg/libprg.h>

double custos_parciais(material *componente, double qtd_utilizada) {
    if (componente->quantidade==0) {
        printf("O Material não está presente em estoque.\n");
        return 0;
    }
    else if (qtd_utilizada>componente->quantidade) {
        printf("A quantidade utilizada não condiz com a quantidade presente em estoque.\n");
        return 0;
    }
        double valor_por_qtd;
        valor_por_qtd = componente->valor_unitario*qtd_utilizada;
        return valor_por_qtd;
}