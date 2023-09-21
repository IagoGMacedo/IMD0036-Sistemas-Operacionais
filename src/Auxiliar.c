#include <stdlib.h>
#include <stdio.h>



void lerMatrizes(){
    int n1, m1, n2, m2;
    srand(time(NULL));


    printf("Digite quatro números inteiros separados por espaços: \n");
    scanf("%d %d %d %d", &n1, &m1, &n2, &m2);

    int **matriz1 = (int **)malloc(n1 * sizeof(int *));
    int **matriz2 = (int **)malloc(n2 * sizeof(int *));

    for (int i = 0; i < n1; i++) {
        matriz1[i] = (int *)malloc(m1 * sizeof(int));
    }

    for (int i = 0; i < n2; i++) {
        matriz2[i] = (int *)malloc(m2 * sizeof(int));
    }


    for(int i =0;i<n1;i++){
        for(int j=0;j<m1;j++){
            matriz1[i][j] = rand() % (11);
        }
    }

    for(int i =0;i<n2;i++){
        for(int j=0;j<m2;j++){
            matriz2[i][j] = rand() % (11);
        }
    }

    
    salvarMatrizes(matriz1, n1, m1, "matriz1.txt");
    salvarMatrizes(matriz2, n2, m2, "matriz2.txt");

}

int salvarMatrizes(int **matriz1, int linha1, int coluna1, char* arquivoMatriz1){

    // Abra o arquivo em modo de escrita (criará um arquivo se não existir ou sobrescreverá se existir)
    FILE *arquivo = fopen(arquivoMatriz1, "w");

    // Verifica se o arquivo foi aberto com sucesso
    if (arquivo == NULL) {
        printf("Erro ao abrir o arquivo.\n");
        return 1;
    }

    // Escreva o conteúdo no arquivo
    for(int i =0;i<linha1;i++){
        for(int j=0;j<coluna1;j++){
            fprintf(arquivo, "%d ", matriz1[i][j]);
        }
        fprintf(arquivo, "\n");
    }

    // Feche o arquivo
    fclose(arquivo);

    printf("Texto escrito com sucesso no arquivo %s.\n", arquivoMatriz1);
    return 0;
}

int main(){
    lerMatrizes();

    return 0;
}