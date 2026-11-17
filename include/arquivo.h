#ifndef TRABALHO_FINAL_PROG_II_ARQUIVO_H
#define TRABALHO_FINAL_PROG_II_ARQUIVO_H

#include "estoque.h"
#include <libprg/libprg.h>


void salvar_estoque(no_avl_t* raiz, const char* relatorio_estoque );
no_avl_t* carregar_estoque(const char* relatorio_estoque);

#endif //TRABALHO_FINAL_PROG_II_ARQUIVO_H