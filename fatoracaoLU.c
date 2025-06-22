#include <stdio.h>
#include <stdlib.h>
#include "fatoracaoLU.h"

void fatoracaoLU(float **matrizA, float **matrizL, float **matrizU, int ordemMat)
{
    //Inicializa L como identidade e faz uma cópia de A em U
    for(int i = 0; i < ordemMat; i++)
    {
        for(int j = 0; j < ordemMat; j++)
        {
            if(i == j)
            {
                matrizL[i][j] = 1;
            }
            else
            {
                matrizL[i][j] = 0;
            }

            matrizU[i][j] = matrizA[i][j];
        }
    }

    //Escalonamento de A para formar U e L

    for(int i = 0; i < ordemMat - 1; i++)
    {
        for(int j = i + 1; j < ordemMat; j++)
        {
            float m = matrizU[j][i] / matrizU[i][i];
            matrizL[j][i] = m;

            for(int k = i; k < ordemMat; k++)
            {
                matrizU[j][k] -= m * matrizU[i][k];
            }
        }
    }
}

void resolverLU(float **matrizL, float **matrizU, float *b, float *x, float *y, int ordemMat)
{
    
    //Resolvendo o Ly = B
    for(int i = 0; i < ordemMat; i ++)
    {
        y[i] = b[i];
        for(int j = 0; j < i; j++)
        {
            y[i] -= matrizL[i][j] * y[j];
        }
    }

    //Resolvendo o Ux = y
    for(int i = ordemMat - 1; i >= 0; i--)
    {
        x[i] = y[i];
        for(int j = i + 1; j < ordemMat; j++)
        {
            x[i] -= matrizU[i][j] * x[j];
        }
        x[i] /= matrizU[i][i];
    }
}
