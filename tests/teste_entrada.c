#include <stdio.h>
#include "entrada.h"

int main(void) {
    char texto[100];
    int inteiro;
    double decimal;

    printf("=== TESTE DE ENTRADAS ===\n");
    printf("(Pressione Ctrl+Z + Enter no Windows ou Ctrl+D no Linux para testar o EOF)\n\n");

    if (ler_texto("1. Texto (teste espacos ou ';'): ", texto, sizeof(texto))) {
        printf("-> Retorno: 1 | Valor: [%s]\n\n", texto);
    } else {
        printf("-> Retorno: 0 (Entrada encerrada)\n\n");
    }

    if (ler_inteiro("2. Inteiro (teste 'abc', '12abc', '12' e '0'): ", &inteiro)) {
        printf("-> Retorno: 1 | Valor: %d\n\n", inteiro);
    } else {
        printf("-> Retorno: 0 (Entrada encerrada)\n\n");
    }

    if (ler_double("3. Decimal (teste '12,5' e 'nan'): ", &decimal)) {
        printf("-> Retorno: 1 | Valor: %.2lf\n\n", decimal);
    } else {
        printf("-> Retorno: 0 (Entrada encerrada)\n\n");
    }

    return 0;
}
