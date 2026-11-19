#include "estoque.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static int proximo_id = 1;
static void imprimir_material(const material* mat) {
    printf("----------------------------------------\n");
    printf("ID: %d | %s\n", mat->id, mat->insumo);
    printf("Marca: %s | Espec.: %s\n",
           mat->marca[0] != '\0' ? mat->marca : "-",
           mat->especificacoes[0] != '\0' ? mat->especificacoes : "-");
    printf("Qtd: %.2lf | Valor Unit.: R$ %.2f\n", mat->quantidade, mat->valor_unitario);
    printf("Local: %s\n", mat->local[0] != '\0' ? mat->local : "-");
}

static int buscar_nome_rec(const no_avl_t* no, const char* texto) {
    if (no == NULL) return 0;
    int achados = buscar_nome_rec(no->esquerda, texto);
    const material* mat = no->dado;
    if (strstr(mat->insumo, texto) != NULL) {
        imprimir_material(mat);
        achados++;
    }
    return achados + buscar_nome_rec(no->direita, texto);
}

static void listar_materiais_rec(const no_avl_t* no) {
    if (no == NULL) return;
    listar_materiais_rec(no->esquerda);
    imprimir_material(no->dado);
    listar_materiais_rec(no->direita);
}


void buscar_por_nome(no_avl_t* raiz, const char* insumo) {
    if (buscar_nome_rec(raiz, insumo) == 0) {
        printf("Nenhum material encontrado.\n");
    }
}

material *buscar_por_id(no_avl_t *raiz, int id) {
    no_avl_t *no_encontrado = buscar_na_arvore_avl(raiz, id);
    if (no_encontrado == NULL) {
        return NULL;
    } else {
        return (material *) no_encontrado->dado;
    }
}

no_avl_t *cadastrar_material(no_avl_t *raiz, material *novo) {
    if (novo == NULL) {
        return raiz;
    }
    novo->id = proximo_id;
    proximo_id++;
    return inserir_na_arvore_avl(raiz, novo->id, novo);
}

no_avl_t* remover_material(no_avl_t* raiz, int id) {
    material* material_encontrado = buscar_por_id(raiz, id);
    if (material_encontrado == NULL) {
        return raiz;
    }
    no_avl_t* nova_raiz = remover_da_arvore_avl(raiz, id);
    free(material_encontrado);
    return nova_raiz;
}

material* criar_material(const char* insumo, const char* marca, const char* especificacoes,double quantidade, float valor_unitario, const char* local) {
    material* m = calloc(1, sizeof(material));
    if (m == NULL) {
        printf("Erro na alocação de memória\n");
        return NULL;
    }
    snprintf(m->insumo, sizeof m->insumo, "%s", insumo);
    snprintf(m->marca, sizeof m->marca, "%s", marca);
    snprintf(m->especificacoes, sizeof m->especificacoes, "%s", especificacoes);
    m->quantidade=quantidade;
    m->valor_unitario=valor_unitario;
    snprintf(m->local, sizeof m->local, "%s", local);
    return m;
}

int obter_proximo_id(void) {
    return proximo_id;
}
void definir_proximo_id(int novo_id) {
    proximo_id = novo_id;
}

 void listar_materiais(no_avl_t* raiz) {
    if (raiz == NULL) {
        printf("Estoque vazio!\n");
        return;
    }
    listar_materiais_rec(raiz);
    printf("----------------------------------------\n");
}

int editar_material(no_avl_t* raiz, int id,  const char* insumo, const char* marca,
    const char* especificacoes, double quantidade, float valor_unitario, const char* local) {
    material* m = buscar_por_id(raiz, id);
    if (m == NULL) {
        return 0;
    }
    if (quantidade < 0 || valor_unitario < 0) return 0;
    snprintf(m->insumo, sizeof m->insumo, "%s", insumo);
    snprintf(m->marca, sizeof m->marca, "%s", marca);
    snprintf(m->especificacoes, sizeof m->especificacoes, "%s", especificacoes);
    m->quantidade=quantidade;
    m->valor_unitario=valor_unitario;
    snprintf(m->local, sizeof m->local, "%s", local);
    return 1;
}

int atualizar_quantidade(no_avl_t* raiz, int id, double nova_quantidade) {
    material* m = buscar_por_id(raiz, id);
    if (m == NULL) {
        return 0;
    }
    if (nova_quantidade < 0) {
        return 0;
    }
    m->quantidade = nova_quantidade;
    return 1;
}

int atualizar_valor_unitario(no_avl_t* raiz, int id, float novo_valor) {
    material* m = buscar_por_id(raiz, id);
    if (m == NULL) {
        return 0;
    }
    if (novo_valor < 0) {
        return 0;
    }
    m->valor_unitario = novo_valor;
    return 1;
}

int movimentar_quantidade(no_avl_t* raiz, int id, double variacao) {
    material* m = buscar_por_id(raiz, id);
    if (m == NULL) {
        return 0;
    }
    const double EPSILON = 1e-6;
    double quantidade_resultante = m->quantidade + variacao;
    if (quantidade_resultante < -EPSILON) {
        return 0;
    }
    if (quantidade_resultante < 0.0) {
        quantidade_resultante = 0.0;
    }
    m->quantidade = quantidade_resultante;
    return 1;
}
