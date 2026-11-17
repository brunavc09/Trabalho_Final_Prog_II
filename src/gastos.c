#include "gastos.h"
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#ifdef _WIN32
#include <windows.h>
    #define strcasecmp _stricmp
#else
    #include <strings.h>
#endif
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
int normalizando_nome(char *registro,char *entrada_usuario) {
    size_t aux = strlen(entrada_usuario);
    if (aux=0) {
        return 0;
    }
     for (;*registro;registro++) {
         size_t i=0;
         while (i<aux && registro[i] && tolower((unsigned char)entrada_usuario[i])==tolower(registro[i])) {
             i++;
         }
     }
    return 0;
}

void coletar(no_avl_t *raiz,criterios_busca *criterios,busca_nome *busca) {
    if (raiz==NULL) {
        printf("Não foi possível encontrar o estoque.\n");
        return;
    }

    coletar(raiz->esquerda,criterios,busca);

    material *recurso=(material*) raiz->dado;
    if (recurso!=NULL) {

    }
}
material* buscar_por_nome_gastos(no_avl_t* raiz,char* insumo,char* marca,char* especificacoes) {
    if (insumo==NULL) {
        printf("O nome do material não foi informado.");
        return NULL;
    }

    criterios_busca aux={insumo,marca,especificacoes};
    busca_nome aux2={NULL,NULL,0,0,0};


}

double custos_totais(int total_insumos,no_avl_t *raiz) {
    char insumo[200],marca[100],esp[200],qtd[30],comando[5]="Sair";
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
        insumo[strcspn(insumo, "\r\n")] = '\0';
        aux2=strcmp(insumo,comando);
        if (aux2==0) {
            break;
        }
        printf("Adicionar marca: ");
        fgets(marca, 100, stdin);
        marca[strcspn(marca, "\r\n")] = '\0';
        printf("Adicione especificações: ");
        fgets(esp,200, stdin);
        esp[strcspn(esp, "\r\n")] = '\0';
        printf("Adicione a quantidade utilizada: ");
        fgets(qtd,30, stdin);
        aux=strtod(qtd,&fim);
        if (fim!=qtd) {
            material *resul_busca=BRUNA_buscar_por_nome(raiz,insumo);
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
