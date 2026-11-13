//
// Created by aluno on 03/11/2026.
//

#include "gastos.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <libprg/libprg.h>

double custos_parciais(material *componente, double qtd_utilizada) {
    if (componente==NULL || componente->quantidade==0) {
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
    char insumo[200],marca[100],qtd[30],comando[5]="Sair";
    char *fim;
    int aux2;
    double aux=0,total=0,parcial=0;

    if (total_insumos<=0) {
        printf("Total de itens não compatível com a operação.\n");
        return -1;
    }

    printf("Para finalizar a operação digite 'Sair' ao adicionar o material.\n\n");

    for (int i=0;i<total_insumos;i++) {
        printf("Adicionar material: ");
        fgets(insumo, 200, stdin);
        insumo[strcspn(insumo, "\n")] = '\0';
        aux2=strcmp(insumo,comando);
        if (aux2==0) {
            break;
        }
        printf("Adicionar marca: ");
        fgets(marca, 100, stdin);
        marca[strcspn(marca, "\n")] = '\0';
        printf("Adicione a quantidade utilizada: ");
        fgets(qtd,30, stdin);
        aux=strtod(qtd,&fim);
        if (fim!=qtd) {
            material *resul_busca=buscar_por_nome(raiz,insumo);
            if (resul_busca==NULL) {
                i--;
                continue;
            }
            else {
                parcial=custos_parciais(resul_busca,aux);
                if (parcial==-1) {
                    printf("Produto não possui quantidade em estoque.\n");
                    i--;
                    continue;
                }
                else if (parcial==-2) {
                    printf("Quantidade não compatível com estoque.\n");
                    i--;
                    continue;
                }
                else if (parcial==-3) {
                    printf("A quantidade utilizada foi informada como zero.\n");
                    i--;
                    continue;
                }
                else {
                    total=total+parcial;
                }
            }
        }
        else {
            printf("Ocorreu um problema na operação\n");
            i--;
            continue;
        }
    }
    return total;
}
