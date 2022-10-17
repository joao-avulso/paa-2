#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef struct{
    int numEnfeite;
    int pesoPacote;
}pacotes;

int max (int a, int b) { 
    return (a > b) ? a : b;
}

int arvNatal (int i, int qtdPacotes, int pesoGalho, pacotes *n) {
    if ((qtdPacotes==0) || (pesoGalho == 0) || (i < 0)) //caso base: não tem mais pacotes ou não da mais para colocar enfeite
        return 0;
    if (n[i].pesoPacote > pesoGalho) //excedeu o peso
        return arvNatal (i-1, qtdPacotes-1, pesoGalho, n);
    else //colocou
        return max (n[i].numEnfeite + arvNatal(i-1, qtdPacotes-1, pesoGalho - n[i].pesoPacote, n), arvNatal(i-1, qtdPacotes-1, pesoGalho, n));
}

int main(){
    FILE *entrada = fopen("entrada3.txt", "r");
    char buffer[10];
    int qtdGalhos, qtdPacotes, pesoGalho;

    fgets(buffer, sizeof(buffer), entrada);
    qtdGalhos = atoi(buffer);

    int galho[qtdGalhos];

    fgets(buffer, sizeof(buffer), entrada);
    for (int i = 0; i < qtdGalhos; i++){
        qtdPacotes = atoi(buffer);

        fgets(buffer, sizeof(buffer), entrada);
        pesoGalho = atoi(buffer);

        pacotes enfeites[qtdPacotes];

        for (int i = 0; i < qtdPacotes; i++){
            fscanf(entrada, "%i %i", &enfeites[i].numEnfeite, &enfeites[i].pesoPacote);
            fgetc(entrada);
        }

        printf("Galho %d:\n", i+1);
        printf("Numero total de enfeites = %d\n", arvNatal(qtdPacotes-1, qtdPacotes, pesoGalho, enfeites));

        printf("\n\n");

        fgets(buffer, sizeof(buffer), entrada);
    }

    fclose(entrada);
}