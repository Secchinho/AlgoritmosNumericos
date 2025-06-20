#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main()
{
    clock_t inicio, fim;
    float tempo;

    //criando um ponteiro para arquivo e abrindo
    FILE *arq = fopen("Sistema.txt", "r");

    //conferindo se é válido
    if(arq==NULL){
        printf("Nao foi possivel abrir o arquivo!\n");
        return 0;
    }

    int sistemas=0;
    int contSistemas=0;
    int tamanho;
    float precisao=0;
    int i, j;

    //lendo a quantidade de sistemas
    fscanf(arq, "%d", &sistemas);

    //lendo o tamanho da matriz e a precisão
    fscanf(arq, "%d %f", &tamanho, &precisao);

    float matriz[tamanho][tamanho];

    //preenchendo a matriz
    for(i=0;i<tamanho;i++){
        for(j=0;j<tamanho;j++){
            fscanf(arq, "%f", &matriz[i][j]);
        }
    }

    //resolver um ou mais sistemas lineares presentes no arquivo
    while(contSistemas<sistemas){

    printf("%d SISTEMA\n", contSistemas+1);
    float vetor[tamanho];

    //preenchendo o(os) vetor(es)
    for(i=0;i<tamanho;i++){
        fscanf(arq, "%f", &vetor[i]);
    }

    float vet0[tamanho];

    //início da conta - início da contagem de tempo
    inicio = clock();

    //calculando o X(0)
    for(i=0;i<tamanho;i++){
        vet0[i] = vetor[i]/matriz[i][i];
    }

    float vet1[tamanho];
    float vetIntermedio[tamanho];
    float valor;
    float erro = precisao+1;
    float vet2[tamanho];

    //repetir até que o erro esteja aceitável
    while(erro>precisao){

    //criando um vetor auxiliar
    for(i=0;i<tamanho;i++){
        vetIntermedio[i]=vet0[i];
    }

    //calculando o x(1)
    for(i=0;i<tamanho;i++){
        valor=0;
        for(j=0;j<tamanho;j++){
            if(i!=j){
                valor += vetIntermedio[j]*matriz[i][j];
            }
        }
        vet1[i] = (vetor[i] - valor)/matriz[i][i];
        vetIntermedio[i] = vet1[i];
    }

    float maior1=0;

    //encontrando o maior valor em módulo
    for(i=0;i<tamanho-1;i++){
        if(fabs(vet1[i])>=fabs(vet1[i+1])){
            maior1=fabs(vet1[i]);
        }
        else{
            maior1=fabs(vet1[i+1]);
        }
    }

    //cálculo
    for(i=0;i<tamanho;i++){
        vet2[i] = vet1[i] - vet0[i];
    }

    float maior2=0;

    //encontrando o maior valor em módulo
    for(i=0;i<tamanho-1;i++){
        if(fabs(vet2[i])>=fabs(vet2[i+1])){
            maior2=fabs(vet2[i]);
        }
        else{
            maior2=fabs(vet2[i+1]);
        }
    }

    //calculando erro
    erro = maior2/maior1;

    //reconfigurando o vetor para continuar o loop (se necessário)
    for(i=0;i<tamanho;i++){
        vet0[i]=vet1[i];
    }
    }

    contSistemas++;

    for(i=0;i<tamanho;i++){
        printf("X%d: %f\n", i+1, vet2[i]);
    }

    printf("Erro: %f\n", erro);

    }

    //finalização da contagem de tempo
    fim = clock();
    printf("Tempo de execucao: %.80f\n", tempo);

    //fechando arquivo
    fclose(arq);
    return 0;
}
