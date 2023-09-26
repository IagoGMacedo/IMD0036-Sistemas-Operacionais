#include "../include/Auxiliar.h"

#include <stdlib.h>
#include <iostream>
#include <random>
#include <string>
#include <vector>
#include <fstream>

Auxiliar::Auxiliar(){
    //this->LerMatrizes();
}


int Auxiliar::LerMatrizes(){
    int n1, m1, n2, m2;

    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<int> distribution(1, 10);

    std::cout << "Digite quatro números inteiros separados por espaços: " << std::endl;
    std::cin >> n1;
    std::cin >> m1;
    std::cin >> n2;
    std::cin >> m2;

    std::vector<std::vector<int>> matriz1(n1, std::vector<int>(m1));
    std::vector<std::vector<int>> matriz2(n2, std::vector<int>(m2));


    for(int i =0;i<n1;i++){
        for(int j=0;j<m1;j++){
            matriz1[i][j] = distribution(gen);
        }
    }

    for(int i =0;i<n2;i++){
        for(int j=0;j<m2;j++){
            matriz2[i][j] = distribution(gen);
        }
    }

    
    this->SalvarMatrizes(matriz1, n1, m1, "../output/matriz1.txt");
    this->SalvarMatrizes(matriz2, n2, m2, "../output/matriz2.txt");
    return 0;
}

int Auxiliar::SalvarMatrizes(std::vector<std::vector<int>> matriz1, int linha1, int coluna1, std::string arquivoMatriz1){

    // Abra o arquivo em modo de escrita (criará um arquivo se não existir ou sobrescreverá se existir)
    std::ofstream arquivo(arquivoMatriz1);

    // Verifique se o arquivo foi aberto com sucesso
    if (!arquivo.is_open()) {
        std::cerr << "Erro ao abrir o arquivo." << std::endl;
        return 1;
    }

    // Escreva o conteúdo no arquivo
    arquivo << linha1 << " " << coluna1 << "\n\n" << std::endl; // linhas e colunas

    for(int i =0;i<linha1;i++){
        for(int j=0;j<coluna1;j++){
            arquivo << matriz1[i][j] << " ";
        }
        arquivo << "\n";
    }
    // Feche o arquivo
    arquivo.close();
    return 0;
}
