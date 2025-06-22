#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "gaussSeidel.h"

void gaussSeidel(int ordem, float **A, float *b, float *x, float precisao)
{
    float *vet0 = malloc(ordem * sizeof(float));
    float *vet1 = malloc(ordem * sizeof(float));
    float *vetIntermedio = malloc(ordem * sizeof(float));
    float *vet2 = malloc(ordem * sizeof(float));

    float erro = precisao + 1;
    int i, j;
    
    for (i = 0; i < ordem; i++)
        vet0[i] = b[i] / A[i][i];

    while (erro > precisao)
    {
        for (i = 0; i < ordem; i++)
            vetIntermedio[i] = vet0[i];

        for (i = 0; i < ordem; i++)
        {
            float soma = 0;
            for (j = 0; j < ordem; j++)
            {
                if (i != j)
                    soma += A[i][j] * vetIntermedio[j];
            }
            vet1[i] = (b[i] - soma) / A[i][i];
            vetIntermedio[i] = vet1[i];
        }

        float maior1 = fabs(vet1[0]);
        for (i = 1; i < ordem; i++)
            if (fabs(vet1[i]) > maior1)
                maior1 = fabs(vet1[i]);

        for (i = 0; i < ordem; i++)
            vet2[i] = vet1[i] - vet0[i];

        float maior2 = fabs(vet2[0]);
        for (i = 1; i < ordem; i++)
            if (fabs(vet2[i]) > maior2)
                maior2 = fabs(vet2[i]);

        erro = maior2 / maior1;

        for (i = 0; i < ordem; i++)
            vet0[i] = vet1[i];
    }

    for (i = 0; i < ordem; i++)
        x[i] = vet1[i];

    free(vet0);
    free(vet1);
    free(vetIntermedio);
    free(vet2);
}
