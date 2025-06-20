#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main()
{
    clock_t inicio, fim;
    double tempo;

    //criando ponteiro para o arquivo e abrindo
    FILE * arq = fopen("Sistema.txt", "r");

    //conferência do arquivo
    if (arq == NULL){
        printf("Nao foi possivel abrir o arquivo!\n");
        return 0;
    }

    int sistemas=0;
    int contSistemas=0;
    int tamanho=0;
    float precisao;
    int i=0;
    int j=0;

    //lendo quantidade de sistemas
    fscanf(arq, "%d", &sistemas);

    //não perco a posição de onde parou a leitura
    //lendo tamanho da matriz e precisão
    fscanf(arq, "%d %f", &tamanho, &precisao);

    float matriz[tamanho][tamanho];

    //preenchendo matriz
    for(i=0; i<tamanho; i++){
        for(j=0;j<tamanho;j++){
            fscanf(arq, "%f", &matriz[i][j]);
        }
    }

    //Resolver problemas com mais de um sistema no mesmo arquivo
    while(contSistemas<sistemas){
    printf ("%d SISTEMA \n", contSistemas+1);
    float vetor[tamanho];

    //preenchendo o(s) vetor(es)
    for(i=0;i<tamanho;i++){
        fscanf(arq, "%f", &vetor[i]);
    }

    //início da conta - início da contagem de tempo
    inicio = clock();

    float vet0[tamanho];

    //calculando o valor de X(0)
    for(i=0;i<tamanho;i++){
        vet0[i]=vetor[i]/matriz[i][i];
    }

    float vet1[tamanho];
    float vet2[tamanho];
    float erro = precisao + 1; //+1 serve para obrigar a entrada no while

    //conta será realizada até que o erro esteja aceitável (menor que a precisão)
    while(erro > precisao){
    float valor;

    //calculando o x(1)
    for(i=0;i<tamanho;i++){
        valor=0;
        for(j=0;j<tamanho;j++){
            if(i!=j){
                valor += vet0[j]*matriz[i][j];
            }
        }
        vet1[i] = (vetor[i] - valor)/matriz[i][i];
    }


    float maior1=0;

    //encontrando o maior valor
    for(i=0;i<tamanho-1;i++){ //fabs() considera o módulo do número
        if(fabs(vet1[i])>=fabs(vet1[i+1])){
            maior1 = fabs(vet1[i]);
        }
        else{
            maior1= fabs(vet1[i+1]);
        }
    }

    //calculando o x(2)
    for(i=0;i<tamanho;i++){
        vet2[i]=vet1[i] - vet0[i];
    }

    float maior2=0;

    //encontrando o maior valor
    for(i=0;i<tamanho-1;i++){ //fabs() considera o módulo do número
        if(fabs(vet2[i])>=fabs(vet2[i+1])){
            maior2 = fabs(vet2[i]);
        }
        else{
            maior2= fabs(vet2[i+1]);
        }
    }

    //calculando o erro
    erro = maior2/maior1;

    //reconfigurando o vetor para continuar o loop (se necessário)
    for(i=0;i<tamanho;i++){
        vet0[i] = vet1[i];
    }

    }

    //Resultado
    for(i=0;i<tamanho;i++){
        printf("X%d: %f\n", i+1, vet2[i]);
    }

    //imprimindo o erro real
    printf("Erro: %f\n", erro);

    contSistemas++;
    }

    //finalizando o contador de tempo
    fim = clock();
    printf ("Tempo de execucao: %.80f\n", tempo);

    //fechando o arquivo
    fclose(arq);
    return 0;
}
