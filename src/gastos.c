//
// Created by aluno on 03/11/2026.
//

#include "gastos.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <libprg/libprg.h>

double custos_parciais(material *componente, double qtd_utilizada) {
    if (componente->quantidade==0 || componente==NULL) {
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

double custos_totais(int total_insumos,no_avl_t *raiz) {
    char insumo[200],marca[100],qtd[30];
    char *fim;
    double aux=0,total=0;

    if (total_insumos<=0) {
        printf("Operação não pode ser realizada\n");
        return 0;
    }

    for (int i=0;i<total_insumos;i++) {
        printf("Adicionar material: ");
        fgets(insumo, 200, stdin);
        insumo[strcspn(insumo, "\n")] = '\0';
        printf("Adicionar marca: ");
        fgets(marca, 100, stdin);
        marca[strcspn(marca, "\n")] = '\0';
        printf("Adicione a quantidade utilizada: ");
        fgets(qtd,30, stdin);
        aux=strtod(qtd,&fim);
        if (fim!=qtd) {
            material *resul_busca=buscar_por_nome(raiz,insumo);
            if (resul_busca==NULL) {
                continue;
            }
            else {
                total=total+custos_parciais(resul_busca,aux);
            }
        }
        else {
            printf("Ocorreu um problema na operação\n");
            return 0;
        }
    }
    return total;
}
