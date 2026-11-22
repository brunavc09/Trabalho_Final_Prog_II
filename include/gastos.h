#ifndef TRABALHO_FINAL_PROG_II_GASTOS_H
#define TRABALHO_FINAL_PROG_II_GASTOS_H

#include <libprg/libprg.h>
#include "estoque.h"

typedef struct {
    char *insumos;
    char *marca;
    char *especificacoes;
}criterios_busca;

typedef struct {
    material *primeiro_achado;
    material *correspondente_exato;
    int achados;
    int exatos;
    int listar;
}busca_nome;

double custos_parciais(const material *componente, double qtd_utilizada);
double custos_totais(int total_insumos,no_avl_t *raiz);
static int normalizando_nome(const char *registro,const char *entrada_usuario);
static int conferir_campos(const char *registro_adicional, const char *filtro);
static int conferir_campos_exatos(const char *registro_adicional, const char *filtro);
static void detalhar_material(material *recurso);
static void coletar(const no_avl_t *raiz,criterios_busca *criterios,busca_nome *busca);
material *buscar_por_nome_gastos(no_avl_t* raiz,char* insumo,char* marca,char* especificacoes);

#endif //TRABALHO_FINAL_PROG_II_GASTOS_H