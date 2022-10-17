#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef struct{
    int h;
    int r;
    char cor[10];
}cilindros;

int comparaRaio(const void *x, const void *y) {
    int a = ((cilindros*)x)->r;
    int b = ((cilindros*)y)->r;
    return (a - b);
}

int max(int arr[], int n){
    int i;
    int max = arr[0];
    for (i = 1; i < n; i++)
        if (arr[i] > max)
            max = arr[i];
    return max;
}

int validaCores(char cor1[], char cor2[]){
    if(!strcmp(cor1, "LARANJA") && !strcmp(cor2, "VERMELHO"))
        return 0;
    if(!strcmp(cor1, "AZUL") && !strcmp(cor2, "LARANJA"))
        return 0;
    if(!strcmp(cor1, "VERDE") && !strcmp(cor2, "AZUL"))
        return 0;
    if(!strcmp(cor1, "VERMELHO") && !strcmp(cor2, "VERDE"))
        return 0;
    return 1;
}

void torreCilindros(cilindros *A, int i, int n, int *memo){
    if (i == 0){
        memo[i] = A[i].h;
    }
    else if (i > 0 && i < n){
        if (A[i].r > A[i-1].r){
            int j = 1;
            while ((j<=i) && !validaCores(A[i].cor, A[i-j].cor)){
                j++;
            }
            if (j>i)
                memo[i] = A[i].h;
            else
                memo[i] = A[i].h + memo[i-j];
        }
        else{
            int j = 2;
            while ((j<=i) || (!(A[i].r > A[i-j].r) && !validaCores(A[i].cor, A[i-j].cor)))
                j++;
            if (j>i)
                memo[i] = A[i].h;
            else
                memo[i] = A[i].h + memo[i-j];
        }
    }
    else
        return;
    torreCilindros(A, i+1, n, memo);
}

int main(){
    FILE *entrada = fopen("entrada.txt", "r");
    char buffer[20];
    int qtd_cilindros;

    fgets(buffer, sizeof(buffer), entrada);

    while(buffer[0] != '0'){
        qtd_cilindros = atoi(buffer);
        cilindros torre[qtd_cilindros];
        int memo[qtd_cilindros];

        for(int i = 0; i < qtd_cilindros; i++)
            fscanf(entrada,"%d %d %s", &torre[i].h, &torre[i].r, torre[i].cor);

        qsort(torre, qtd_cilindros, sizeof(cilindros), comparaRaio);

        torreCilindros(torre, 0, qtd_cilindros, memo);

        printf("%d centimetros\n", max(memo, qtd_cilindros));

        fgetc(entrada);
        fgets(buffer, sizeof(buffer), entrada);
    }
    fclose(entrada);
}