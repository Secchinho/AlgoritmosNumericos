#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "fatoracaoLU.h"

float** alocacaoMat(int ordemMat)
{
    float **matriz = malloc(ordemMat * sizeof(float* ));
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

int main(int argc, char *argv[])
{
    if (argc != 2)
    {
        exit(1);
    }
    
    clock_t inicio, fim;

    int sistemas = 0;
    int contSistemas = 0;
    int ordemMat = 0;
    float precisao = 0;
    float tempo = 0;

    FILE *arq = fopen(argv[1], "r");

    if(arq == NULL)
    {
        printf("Nao foi possivel abrir o arquivo!\n");
        exit(1);
    }

    //lendo a quantidade de sistemas
    fscanf(arq, "%d", &sistemas);

    //lendo o tamanho da matriz e a precisão
    fscanf(arq, "%d %f", &ordemMat, &precisao);

    float **matriz = alocacaoMat(ordemMat);
    float **matrizL = alocacaoMat(ordemMat);
    float **matrizU = alocacaoMat(ordemMat);

     //preenchendo a matriz
    for(int i = 0; i < ordemMat; i++)
    {
        for(int j = 0; j < ordemMat; j++)
        {
            fscanf(arq, "%f", &matriz[i][j]);
        }
    }

    inicio = clock();
    fatoracaoLU(matriz, matrizL, matrizU, ordemMat);

    float *b = calloc(ordemMat, sizeof(float));
    float *x = calloc(ordemMat, sizeof(float));
    float *y = calloc(ordemMat, sizeof(float));

    for (int s = 0; s < sistemas; s++) 
    {
        printf("\nSistema %d:\n", s + 1);

        for (int i = 0; i < ordemMat; i++)
        {
            fscanf(arq, "%f", &b[i]);
        }
        
        resolverLU(matrizL, matrizU, b, x, y, ordemMat);

        printf("Vetor solução X:\n");
        for (int i = 0; i < ordemMat; i++)
        {
            printf("x[%d] = %f\n", i, x[i]);
        }
    }
    fim = clock();

    printf("Tempo de execução %f\n", (float)(fim - inicio) / CLOCKS_PER_SEC);
    //Resolver problemas com mais de um sistema no mesmo arquivo
    //while( contSistemas < sistemas){
        //printf ("%d SISTEMA \n", contSistemas + 1);
        //float vetor[ordemMat];

        //preenchendo o(s) vetor(es)
        //for(int i = 0; i < ordemMat; i++){
           // fscanf(arq, "%f", &vetor[i]);
        //}

        /*
            Função para receber e ler a matriz
        */

        /*
            Chamada das funções de resolução das matrizes
        */

        /*
            Comparação de resultados
        */
    //}
    liberarMat(matriz, ordemMat);
    liberarMat(matrizL, ordemMat);
    liberarMat(matrizU, ordemMat);
    free(b);
    free(x);
    free(y);
    fclose(arq);
    return 0;
}