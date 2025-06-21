#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "fatoracaoLU.h"

int main()
{
    clock_t inicio, fim;
    int sistemas=0;
    int contSistemas=0;
    int tamanho = 0;
    float precisao=0;
    float tempo = 0;

    FILE *arq = fopen("Sistema.txt", "r");
    if(arq==NULL){
        printf("Nao foi possivel abrir o arquivo!\n");
        return 0;
    }

    //lendo a quantidade de sistemas
    fscanf(arq, "%d", &sistemas);

    //lendo o tamanho da matriz e a precisão
    fscanf(arq, "%d %f", &tamanho, &precisao);

    float matriz[tamanho][tamanho];

     //preenchendo a matriz
    for(int i = 0; i < tamanho; i++){
        for(int j = 0; j < tamanho; j++){
            fscanf(arq, "%f", &matriz[i][j]);
        }
    }

    /*
        Função para receber e ler a matriz
    */

    /*
        Chamada das funções de resolução das matrizes
    */

    /*
        Comparação de resultados
    */
    return 0;
}