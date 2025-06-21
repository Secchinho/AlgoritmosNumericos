#include <stdio.h>
#include <stdlib.h>

void fatoracaoLU(double **matrizA, double **matrizL, double **matrizU, int ordemMat)
{
    for(int i = 0; i < ordemMat; i++)
    {
        //Construindo a matriz U
        for(int k = i; k < ordemMat; k++)
        {
            matrizU[i][k] = matrizA[i][k];
            for(int j = 0; i < j; j++)
            {
                matrizU[i][k] -= matrizL[i][j] * matrizU[j][k];
            }
        }

        //Construindo a matriz L
        for (int k = i; k < ordemMat; k++)
        {
            if(i == k)
            {
                matrizL[i][i] = 1;
            }
            else
            {
                matrizL[k][i] = matrizA[k][i];
                for(int j = 0; j < i; j++)
                {
                    matrizL[k][i] -= matrizL[k][j] * matrizU[j][i];
                }
                matrizL[k][i] /= matrizU[i][i];
            }
        }
    }
}

void resolverLU(double **matrizL, double **matrizU, double *b, double *x, double *y, int ordemMat)
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

void substituicaoLy(double **matrizL, double *b, double *y, int ordemMat)
{
    for(int i = 0; i < ordemMat; i ++)
    {
        y[i] = b[i];
        for(int j = 0; j < i; j++)
        {
            y[i] -= matrizL[i][j] * y[j];
        }
    }
}

void substituicaoUx(double **matrizU, double *y, double *x, int ordemMat)
{
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
