//
// Created by aluno on 03/11/2026.
//

#include "gastos.h"
#include <stdio.h>
#include <string.h>
#include <libprg/libprg.h>

double custos_parciais(material *componente, double qtd_utilizada) {
    if (componente->quantidade==0 || componente->quantidade==NULL) {
        return -1;
    }
    else if (qtd_utilizada>componente->quantidade) {
        return -2;
    }
    else if (qtd_utilizada<=0) {
        return -3;
    }
    else {
        double valor_por_qtd;
        valor_por_qtd = componente->valor_unitario*qtd_utilizada;
        return valor_por_qtd;
    }
}

