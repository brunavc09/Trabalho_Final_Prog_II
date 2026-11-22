#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <libprg/libprg.h>
#include "estoque.h"
#include "arquivo.h"
#include "gastos.h"
#include "entrada.h"

#ifdef _WIN32
#include <windows.h>
#endif

#define TAM_TEXTO 100
#define LIMITE_ESTOQUE_BAIXO 10

typedef struct no_pilha {
    material* backup;
    struct no_pilha* prox;
} no_pilha_t;

typedef struct no_lista {
    const material* mat;
    struct no_lista* prox;
} no_lista_t;

static void empilhar_backup(no_pilha_t** topo, const material* original) {
    if (original == NULL) return;

    material* copia = malloc(sizeof(material));
    if (copia == NULL) return;
    memcpy(copia, original, sizeof(material));

    no_pilha_t* novo = malloc(sizeof(no_pilha_t));
    if (novo == NULL) {
        free(copia);
        return;
    }

    novo->backup = copia;
    novo->prox = *topo;
    *topo = novo;
}

static material* desempilhar_backup(no_pilha_t** topo) {
    if (*topo == NULL) return NULL;

    no_pilha_t* removido = *topo;
    material* dados = removido->backup;
    *topo = removido->prox;
    free(removido);

    return dados;
}

static void liberar_pilha_desfazer(no_pilha_t** topo) {
    while (*topo != NULL) {
        material* dados = desempilhar_backup(topo);
        free(dados);
    }
}

static void inserir_fim_lista(no_lista_t** inicio, no_lista_t** fim, const material* mat) {
    no_lista_t* novo = malloc(sizeof(no_lista_t));
    if (novo == NULL) return;

    novo->mat = mat;
    novo->prox = NULL;

    if (*inicio == NULL) {
        *inicio = novo;
        *fim = novo;
    } else {
        (*fim)->prox = novo;
        *fim = novo;
    }
}

static void coletar_abaixo_de_10(const no_avl_t* no, no_lista_t** inicio, no_lista_t** fim) {
    if (no == NULL) return;

    coletar_abaixo_de_10(no->esquerda, inicio, fim);

    const material* mat = (const material*)no->dado;
    if (mat != NULL && mat->quantidade < LIMITE_ESTOQUE_BAIXO) {
        inserir_fim_lista(inicio, fim, mat);
    }

    coletar_abaixo_de_10(no->direita, inicio, fim);
}

static void listar_estoque_baixo(const no_avl_t* raiz) {
    no_lista_t* inicio = NULL;
    no_lista_t* fim = NULL;

    coletar_abaixo_de_10(raiz, &inicio, &fim);

    printf("\n--- MATERIAIS COM ESTOQUE BAIXO (< %d UNIDADES) ---\n", LIMITE_ESTOQUE_BAIXO);
    if (inicio == NULL) {
        printf("Nenhum material abaixo de %d unidades.\n", LIMITE_ESTOQUE_BAIXO);
        return;
    }

    no_lista_t* atual = inicio;
    while (atual != NULL) {
        const material* m = atual->mat;
        printf("ID: %d | %s | Qtd: %.2lf | Local: %s\n",
               m->id, m->insumo, m->quantidade, strlen(m->local) > 0 ? m->local : "-");

        no_lista_t* temp = atual;
        atual = atual->prox;
        free(temp);
    }
    printf("---------------------------------------------------\n");
}

static void liberar_arvore_estoque(no_avl_t* raiz) {
    if (raiz == NULL) return;
    liberar_arvore_estoque(raiz->esquerda);
    liberar_arvore_estoque(raiz->direita);
    free(raiz->dado);
    free(raiz);
}

static void menu_cadastrar(no_avl_t** raiz, const char* nome_arquivo) {
    printf("\n--- CADASTRAR MATERIAL ---\n");

    char insumo[TAM_TEXTO] = "";
    char marca[TAM_TEXTO] = "";
    char especificacoes[TAM_TEXTO] = "";
    char local[TAM_TEXTO] = "";
    double quantidade = 0.0;
    double valor_temp = 0.0;

    ler_texto("Insumo (nome): ", insumo, sizeof(insumo));
    if (strlen(insumo) == 0) {
        printf("Erro: o nome do insumo nao pode ser vazio.\n");
        return;
    }

    ler_texto("Marca: ", marca, sizeof(marca));
    ler_texto("Especificacoes: ", especificacoes, sizeof(especificacoes));
    if (!ler_double("Quantidade inicial: ", &quantidade)) return;
    if (!ler_double("Valor unitario (R$): ", &valor_temp)) return;

    if (quantidade < 0.0 || valor_temp < 0.0) {
        printf("Erro: quantidade e valor unitario nao podem ser negativos.\n");
        return;
    }

    ler_texto("Local de armazenamento: ", local, sizeof(local));

    material* novo = criar_material(insumo, marca, especificacoes, quantidade, (float)valor_temp, local);
    if (novo != NULL) {
        *raiz = cadastrar_material(*raiz, novo);
        salvar_estoque(*raiz, nome_arquivo);
        printf("Material cadastrado (ID: %d) e salvo com sucesso!\n", novo->id);
    } else {
        printf("Erro ao criar o material.\n");
    }
}

static void menu_gerenciar(no_avl_t** raiz, no_pilha_t** pilha_desfazer, const char* nome_arquivo) {
    int sub_opcao = 0;
    printf("\n--- BUSCAR / EDITAR / REMOVER ---\n");
    printf("1. Buscar por ID\n");
    printf("2. Buscar por nome\n");
    printf("3. Editar material\n");
    printf("4. Remover material\n");
    printf("0. Voltar\n");

    if (!ler_inteiro("Escolha uma opcao: ", &sub_opcao)) return;

    switch (sub_opcao) {
        case 1: {
            int id;
            if (ler_inteiro("Digite o ID para busca: ", &id)) {
                material* mat = buscar_por_id(*raiz, id);
                if (mat != NULL) {
                    printf("----------------------------------------\n");
                    printf("ID: %d | %s\n", mat->id, mat->insumo);
                    printf("Marca: %s | Espec.: %s\n",
                           strlen(mat->marca) > 0 ? mat->marca : "-",
                           strlen(mat->especificacoes) > 0 ? mat->especificacoes : "-");
                    printf("Qtd: %.2lf | Valor Unit.: R$ %.2f\n", mat->quantidade, mat->valor_unitario);
                    printf("Local: %s\n", strlen(mat->local) > 0 ? mat->local : "-");
                    printf("----------------------------------------\n");
                } else {
                    printf("Material com ID %d nao encontrado.\n", id);
                }
            }
            break;
        }
        case 2: {
            char texto[TAM_TEXTO] = "";
            ler_texto("Digite o nome (ou parte dele): ", texto, sizeof(texto));
            buscar_por_nome(*raiz, texto);
            break;
        }
        case 3: {
            int id;
            if (ler_inteiro("Digite o ID do material a editar: ", &id)) {
                material* atual = buscar_por_id(*raiz, id);
                if (atual == NULL) {
                    printf("Material com ID %d nao encontrado.\n", id);
                    break;
                }

                empilhar_backup(pilha_desfazer, atual);

                char insumo[TAM_TEXTO] = "";
                char marca[TAM_TEXTO] = "";
                char especificacoes[TAM_TEXTO] = "";
                char local[TAM_TEXTO] = "";
                double quantidade = 0.0;
                double valor_temp = 0.0;

                printf("Informe os novos dados do material:\n");
                ler_texto("Novo insumo: ", insumo, sizeof(insumo));
                ler_texto("Nova marca: ", marca, sizeof(marca));
                ler_texto("Novas especificacoes: ", especificacoes, sizeof(especificacoes));
                if (!ler_double("Nova quantidade: ", &quantidade)) {
                    free(desempilhar_backup(pilha_desfazer));
                    break;
                }
                if (!ler_double("Novo valor unitario (R$): ", &valor_temp)) {
                    free(desempilhar_backup(pilha_desfazer));
                    break;
                }
                ler_texto("Novo local: ", local, sizeof(local));

                if (editar_material(*raiz, id, insumo, marca, especificacoes, quantidade, (float)valor_temp, local)) {
                    salvar_estoque(*raiz, nome_arquivo);
                    printf("Material atualizado e salvo com sucesso!\n");
                } else {
                    free(desempilhar_backup(pilha_desfazer));
                    printf("Erro ao editar material (verifique se quantidade/valor nao sao negativos).\n");
                }
            }
            break;
        }
        case 4: {
            int id;
            if (ler_inteiro("Digite o ID do material a remover: ", &id)) {
                if (buscar_por_id(*raiz, id) == NULL) {
                    printf("Material com ID %d nao encontrado.\n", id);
                    break;
                }
                *raiz = remover_material(*raiz, id);
                salvar_estoque(*raiz, nome_arquivo);
                printf("Material removido e estoque salvo!\n");
            }
            break;
        }
        case 0:
            break;
        default:
            printf("Opcao invalida.\n");
            break;
    }
}

static void executar_desfazer(no_avl_t* raiz, no_pilha_t** pilha_desfazer, const char* nome_arquivo) {
    material* anterior = desempilhar_backup(pilha_desfazer);
    if (anterior == NULL) {
        printf("Nada para desfazer.\n");
        return;
    }

    if (editar_material(raiz, anterior->id, anterior->insumo, anterior->marca,
                        anterior->especificacoes, anterior->quantidade,
                        anterior->valor_unitario, anterior->local)) {
        salvar_estoque(raiz, nome_arquivo);
        printf("Edicao desfeita! Material ID %d (%s) restaurado.\n", anterior->id, anterior->insumo);
    } else {
        printf("Nao foi possivel desfazer: o material ID %d nao existe mais no estoque.\n", anterior->id);
    }

    free(anterior);
}

void calcular_gastos(no_avl_t *raiz) {
    char entrada[30],*fim;
    printf("Quantos materiais foram utilizados?\n");
    fgets(entrada,30,stdin);
    if (fgets(entrada, sizeof(entrada), stdin) == NULL) {
        return;
    }
    entrada[strcspn(entrada, "\r\n")] = '\0';

    long aux=strtol(entrada,&fim,10);
    if (fim==entrada || *fim!='\0') {
        printf("Número inválido.\n");
        return;
    }

    double custo=custos_totais((int)aux,raiz);
    if (custo>=0) {
        printf("O gasto total foi %lf\n", custo);
    }
}


int main(void) {
#ifdef _WIN32
    SetConsoleOutputCP(CP_UTF8);
    SetConsoleCP(CP_UTF8);
#endif

    const char* NOME_ARQUIVO = "estoque.txt";
    no_avl_t* raiz = carregar_estoque(NOME_ARQUIVO);
    no_pilha_t* pilha_desfazer = NULL;
    int opcao = 0;

    while (1) {
        printf("\n=== CONTROLE DE ESTOQUE - MARCENARIA ===\n");
        printf("1. Cadastrar material\n");
        printf("2. Listar materiais\n");
        printf("3. Buscar / Editar / Remover\n");
        printf("4. Desfazer ultima edicao\n");
        printf("5. Listar materiais abaixo de %d unidades\n", LIMITE_ESTOQUE_BAIXO);
        printf("6. Calcular gastos com projeto\n");
        printf("7. Sair\n");

        if (!ler_inteiro("Escolha uma opcao: ", &opcao)) {
            printf("\nEntrada encerrada.\n");
            opcao = 7;
        }

        if (opcao == 7) {
            printf("Salvando estoque e encerrando...\n");
            salvar_estoque(raiz, NOME_ARQUIVO);
            liberar_pilha_desfazer(&pilha_desfazer);
            liberar_arvore_estoque(raiz);
            break;
        }

        switch (opcao) {
            case 1:
                menu_cadastrar(&raiz, NOME_ARQUIVO);
                break;
            case 2:
                listar_materiais(raiz);
                break;
            case 3:
                menu_gerenciar(&raiz, &pilha_desfazer, NOME_ARQUIVO);
                break;
            case 4:
                executar_desfazer(raiz, &pilha_desfazer, NOME_ARQUIVO);
                break;
            case 5:
                listar_estoque_baixo(raiz);
                break;
            case 6:
                calcular_gastos(raiz);
                break;
            default:
                printf("Opcao inexistente. Tente novamente.\n");
                break;
        }
    }

    return 0;
}
