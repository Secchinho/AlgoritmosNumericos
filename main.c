#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include "eliminacaoDeGauss.h"
#include "fatoracaoLU.h"
#include "gaussSeidel.h"
#include "gaussJacobi.h"

float** alocacaoMat(int ordemMat)
{
    float **matriz = malloc(ordemMat * sizeof(float*));
    for(int i = 0; i < ordemMat; i++)
    {
        matriz[i] = calloc(ordemMat, sizeof(float));
    }
    return matriz;
}


void liberarMat(float **matriz, int ordemMat)
{
    for(int i = 0; i < ordemMat; i++)
    {
        free(matriz[i]);
    }
    free(matriz);
}


void copiarMatriz(float **origem, float **destino, int ordem)
{
    for (int i = 0; i < ordem; i++) {
        for (int j = 0; j < ordem; j++) {
            destino[i][j] = origem[i][j];
        }
    }
}

int main(int argc, char *argv[])
{
    if (argc != 2)
    {
        printf("Uso: %s <arquivo_entrada>\n", argv[0]);
        exit(1);
    }
    
    clock_t inicio, fim;

    int sistemas = 0;
    int ordemMat = 0;
    float precisao = 0;

    FILE *arq = fopen(argv[1], "r");

    if(arq == NULL)
    {
        printf("Nao foi possivel abrir o arquivo!\n");
        exit(1);
    }

    //Lendo a quantidade de sistemas
    fscanf(arq, "%d", &sistemas);
    
    //Lendo o tamanho da matriz e a precisão
    fscanf(arq, "%d %f", &ordemMat, &precisao);

    //Alocação das matrizes
    float **matriz = alocacaoMat(ordemMat);
    float **matrizL = alocacaoMat(ordemMat);
    float **matrizU = alocacaoMat(ordemMat);
    float **matrizCopia = alocacaoMat(ordemMat);

    //Preenchendo a matriz
    for(int i = 0; i < ordemMat; i++)
    {
        for(int j = 0; j < ordemMat; j++)
        {
            fscanf(arq, "%f", &matriz[i][j]);
        }
    }

    //Leitura dos vetores B para cada sistema
    float **bSistemas = malloc(sistemas * sizeof(float*));
    for (int s = 0; s < sistemas; s++) 
    {
        bSistemas[s] = malloc(ordemMat * sizeof(float));
        for (int i = 0; i < ordemMat; i++) {
            fscanf(arq, "%f", &bSistemas[s][i]);
        }
    }

    float *b = calloc(ordemMat, sizeof(float));
    float *x = calloc(ordemMat, sizeof(float));
    float *y = calloc(ordemMat, sizeof(float));

    //=================== Eliminação de Gauss ===================
    printf("\nResultados e tempo de execução da Eliminação de Gauss:\n");
    
    inicio = clock();
    
    for (int s = 0; s < sistemas; s++) 
    {
        printf("\nSistema %d:\n", s + 1);
        
        for (int i = 0; i < ordemMat; i++)
            b[i] = bSistemas[s][i];

        copiarMatriz(matriz, matrizCopia, ordemMat);
        
        gaussEliminacaoPivotamento(ordemMat, matrizCopia, b, x);

        printf("Vetor solução X:\n");
        
        for (int i = 0; i < ordemMat; i++)
            printf("x[%d] = %f\n", i, x[i]);
    }
    
    fim = clock();
    
    printf("Tempo de execução Eliminação de Gauss: %f\n", (float)(fim - inicio) / CLOCKS_PER_SEC);

    //=================== Fatoração LU ===================
    printf("\nResultados e tempo de execução da Fatoração LU:\n");
    
    inicio = clock();
    
    copiarMatriz(matriz, matrizCopia, ordemMat);
    
    fatoracaoLU(matrizCopia, matrizL, matrizU, ordemMat);
    
    for (int s = 0; s < sistemas; s++) 
    {
        printf("\nSistema %d:\n", s + 1);
        
        for (int i = 0; i < ordemMat; i++)
            b[i] = bSistemas[s][i];

        for (int i = 0; i < ordemMat; i++) 
            x[i] = y[i] = 0;
        
        resolverLU(matrizL, matrizU, b, x, y, ordemMat);

        printf("Vetor solução X:\n");
        
        for (int i = 0; i < ordemMat; i++)
            printf("x[%d] = %f\n", i, x[i]);
    }
    
    fim = clock();
    
    printf("Tempo de execução FatoraçãoLU: %f\n", (float)(fim - inicio) / CLOCKS_PER_SEC);

    //=================== Gauss-Seidel ===================
    printf("\nResultados e tempo de execução da Gauss Seidel:\n");
    
    inicio = clock();
    
    for (int s = 0; s < sistemas; s++) 
    {
        printf("\nSistema %d:\n", s + 1);
        
        for (int i = 0; i < ordemMat; i++)
            b[i] = bSistemas[s][i];

        copiarMatriz(matriz, matrizCopia, ordemMat);
        
        for (int i = 0; i < ordemMat; i++) 
            x[i] = 0;
        
        gaussSeidel(ordemMat, matrizCopia, b, x, precisao);

        printf("Vetor solução X:\n");
        
        for (int i = 0; i < ordemMat; i++)
            printf("x[%d] = %f\n", i, x[i]);
    }
    
    fim = clock();
    
    printf("Tempo de execução GaussSeidel: %f\n", (float)(fim - inicio) / CLOCKS_PER_SEC);

    //=================== Gauss-Jacobi ===================
    printf("\nResultados e tempo de execução da Gauss Jacobi:\n");
    
    inicio = clock();
    
    for (int s = 0; s < sistemas; s++) 
    {
        printf("\nSistema %d:\n", s + 1);
        
        for (int i = 0; i < ordemMat; i++)
            b[i] = bSistemas[s][i];

        copiarMatriz(matriz, matrizCopia, ordemMat);
        
        for (int i = 0; i < ordemMat; i++) 
            x[i] = 0;
        
        gaussJacobi(ordemMat, matrizCopia, b, x, precisao);

        printf("Vetor solução X:\n");
        
        for (int i = 0; i < ordemMat; i++)
            printf("x[%d] = %f\n", i, x[i]);
    }
    
    fim = clock();
    
    printf("Tempo de execução GaussJacobi: %f\n", (float)(fim - inicio) / CLOCKS_PER_SEC);

    //Liberação de memória
    liberarMat(matriz, ordemMat);
    liberarMat(matrizL, ordemMat);
    liberarMat(matrizU, ordemMat);
    liberarMat(matrizCopia, ordemMat);
    
    free(b);
    free(x);
    free(y);
    
    for (int s = 0; s < sistemas; s++) free(bSistemas[s]);
    free(bSistemas);
    fclose(arq);

    return 0;
}
