#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "eliminacaoDeGauss.h"

void gaussEliminacaoPivotamento(int ordem, float **A, float *B, float *x){
    // Eliminação de Gauss com pivotamento parcial
    for (int k = 0; k < ordem - 1; k++) {
        // Pivotamento parcial: encontrar o maior valor absoluto na coluna k
        int max = k;
        for (int i = k + 1; i < ordem; i++) {
            if (fabs(A[i][k]) > fabs(A[max][k])) {
                max = i;
            }
        }

        // Trocar linhas k e max se necessário
        if (max != k) {
            float *tempLinha = A[k];
            A[k] = A[max];
            A[max] = tempLinha;

            float tempB = B[k];
            B[k] = B[max];
            B[max] = tempB;
        }

        // Eliminação abaixo da linha pivô
        for (int i = k + 1; i < ordem; i++) {
            if (A[k][k] == 0) {
                printf("Erro: Divisão por zero detectada após pivotamento!\n");
                exit(1);
            }
            float fator = A[i][k] / A[k][k];
            for (int j = k; j < ordem; j++) {
                A[i][j] -= fator * A[k][j];
            }
            B[i] -= fator * B[k];
        }
    }
}