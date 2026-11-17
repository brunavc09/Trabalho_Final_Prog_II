#include <stdio.h>
#include "estoque.h"
#include "arquivo.h"

int main() {
    no_avl_t* raiz = NULL;

    //raiz = cadastrar_material(raiz, criar_material("Parafuso Sextavado", "Vonder", "Aco inox 5mm", 100.0, 0.50f, "Corredor A"));
   //raiz = cadastrar_material(raiz, criar_material("Martelo Unha", "Tramontina", "Cabo de madeira 25mm", 15.0, 34.90f, "Corredor B"));
   // raiz = cadastrar_material(raiz, criar_material("Chave de Fenda", "Gedore", "Ponta imantada 1/4", 22.0, 18.75f, "Corredor B"));
   // raiz = cadastrar_material(raiz, criar_material("Tinta Acrilica", "Suvinil", "Branco Fosco 18L", 8.0, 289.90f, "Corredor C"));
   // raiz = cadastrar_material(raiz, criar_material("Fio Eletrico", "Sil", "Flexivel 2.5mm Rolo 100m", 12.0, 145.00f, "Corredor D"));
   //raiz = cadastrar_material(raiz, criar_material("Cimento CP II", "Votoran", "Saco 50kg", 40.0, 32.50f, "Deposito Externo"));
    //raiz = cadastrar_material(raiz, criar_material("Luva de Protecao", "Volk", "Nitrilica Tamanho G", 50.0, 12.40f, "Corredor A"));

    //salvar_estoque(raiz, "estoque.txt");
    //printf("Arquivo 'estoque.txt' salvo com sucesso!\n");

    //destruir_arvore_avl(raiz);

    raiz = carregar_estoque("estoque.txt");
    //imprimir_arvore_avl_em_ordem(raiz);

    material* b = buscar_por_id(raiz, 3);
    if(b == NULL) {
        return 1;
    }
    printf("Insumo: %s\n", b->insumo);
    printf("Marca: %s\n", b->marca);
    printf("valor unitario: %.2lf\n", b->valor_unitario);

    raiz = cadastrar_material(raiz, criar_material("saco de coco", "bustão", "esta rasgada", 4.0, 20.78f, "geladeira"));

    salvar_estoque(raiz, "teste.txt");
    printf("Arquivo 'teste.txt' salvo com sucesso!\n");
    return 0;
}
