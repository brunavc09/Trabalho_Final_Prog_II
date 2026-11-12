#ifndef TRABALHO_FINAL_PROG_II_ESTOQUE_H
#define TRABALHO_FINAL_PROG_II_ESTOQUE_H

#include <libprg/libprg.h>

typedef struct material {
    int id;
    char insumo[200];
    char marca[100];
    char especificacoes[200];
    double quantidade;
    float valor_unitario;
    char local[200];
} material;

no_avl_t* cadastrar_material(no_avl_t* raiz, material* novo);
material* buscar_por_id(no_avl_t* raiz, int id);
void buscar_por_nome(no_avl_t* raiz, const char * insumo);
no_avl_t* remover_material(no_avl_t* raiz, int id);
material* criar_material(const char* insumo, const char* marca, const char* especificacoes,double quantidade, float valor_unitario, const char* local);
int obter_proximo_id(void);
void definir_proximo_id(int novo_id);

#endif //TRABALHO_FINAL_PROG_II_ESTOQUE_H

