#include "entrada.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

int ler_texto(const char* mensagem, char* destino, int tamanho) {
    if (destino == NULL || tamanho <= 0) {
        return 0;
    }
    if (mensagem != NULL) {
        printf("%s", mensagem);
    }
    if (fgets(destino, tamanho, stdin) == NULL) {
        destino[0] = '\0';
        return 0;
    }
    if (strchr(destino, '\n') == NULL) {
        int c;
        while ((c = getchar()) != '\n' && c != EOF);
    }
    destino[strcspn(destino, "\r\n")] = '\0';
    for (int i = 0; destino[i] != '\0'; i++) {
        if (destino[i] == ';') {
            destino[i] = ',';
        }
    }
    return 1;
}

int ler_inteiro(const char* mensagem, int* destino) {
    if (destino == NULL) return 0;
    char linha[64];
    char* fim;

    while (1) {
        if (!ler_texto(mensagem, linha, sizeof(linha))) {
            return 0;
        }
        long valor = strtol(linha, &fim, 10);
        if (fim != linha && *fim == '\0') {
            *destino = (int)valor;
            return 1;
        }
        printf("Valor invalido. Tente novamente.\n");
    }
}

int ler_double(const char* mensagem, double* destino) {
    if (destino == NULL) return 0;
    char linha[64];
    char* fim;

    while (1) {
        if (!ler_texto(mensagem, linha, sizeof(linha))) {
            return 0;
        }
        for (int i = 0; linha[i] != '\0'; i++) {
            if (linha[i] == ',') {
                linha[i] = '.';
            }
        }
        double valor = strtod(linha, &fim);
        if (fim != linha && *fim == '\0' && isfinite(valor)) {
            *destino = valor;
            return 1;
        }
        printf("Valor invalido. Tente novamente.\n");
    }
}