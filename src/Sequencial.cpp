#include "../include/Sequencial.h"
#include <string>
#include <vector>
#include <iostream>
#include <fstream>
#include <chrono>

Sequencial::Sequencial(){

};

std::vector<std::vector<int>> Sequencial::LerMatriz(std::string nomeArquivo){

    // Crie um objeto ifstream para ler o arquivo
    std::ifstream arquivo(nomeArquivo);

    // Verifique se o arquivo foi aberto com sucesso
    if (!arquivo.is_open()) {
        std::cout << "Não foi possível abrir o arquivo " << nomeArquivo << std::endl;
    }

    // Variável para armazenar as linhas do arquivo
    std::string linha;
    int nLinhas;
    int nColunas;

    // Recuperando número de linhas e colunas
    arquivo >> nLinhas;
    arquivo >> nColunas;

    std::vector<std::vector<int>> matriz1(nLinhas, std::vector<int>(nColunas));

    for(int i =0;i<nLinhas;i++){
        for(int j=0;j<nColunas;j++){
            arquivo >> matriz1[i][j];
        }
    }

    /*
    // Loop para ler o arquivo linha por linha
    while (std::getline(arquivo, linha)) {
        // Faça algo com a linha lida, neste caso, apenas imprima na tela
        std::cout << linha << std::endl;
    }
    */

    // Feche o arquivo após a leitura
    arquivo.close();
    return matriz1;
};

void Sequencial::MultiplicarMatrizes(){
    //Recuperando matrizes
    std::vector<std::vector<int>> matriz1 = this->LerMatriz("./output/matriz1.txt");
    std::vector<std::vector<int>> matriz2 = this->LerMatriz("./output/matriz2.txt");

    auto start_time = std::chrono::high_resolution_clock::now();

    //verificando se a multiplicação de matrizes eh possivel
    if(!matriz1[0].size() == matriz2.size()){
        std::cout << "não dá pra multiplicar isso" << std::endl;
    }

    std::vector<std::vector<int>> matriz3(matriz1.size(), std::vector<int>(matriz2[0].size()));

    //percorrendo linha
    for(int i =0;i<matriz1.size();i++){
        for(int j =0;j<matriz2[0].size();j++){  
            for(int k=0;k<matriz1[0].size(); k++){
                matriz3[i][j] += matriz1[i][k] * matriz2[k][j];
            }
        }
    }

    auto end_time = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end_time - start_time);
    this->SalvarMatriz(matriz3, matriz1.size(), matriz2[0].size(), duration.count());
}

void Sequencial::SalvarMatriz(std::vector<std::vector<int>> matriz1, int linha1, int coluna1, int64_t  tempoDuracao){
     std::string arquivoResultado = "./output/matrizResultado.txt";
     std::ofstream arquivo(arquivoResultado);

    // Verifique se o arquivo foi aberto c  om sucesso
    if (!arquivo.is_open()) {
        std::cerr << "Erro ao abrir o arquivo." << std::endl;
    }

    // Escreva o conteúdo no arquivo
    arquivo << linha1 << " " << coluna1 << std::endl; // linhas e colunas

    for(int i =0;i<linha1;i++){
        for(int j=0;j<coluna1;j++){
            arquivo <<"c"<<i+1<<j+1<<" " <<matriz1[i][j] << "\n";
        }
    }
    arquivo << tempoDuracao;
    // Feche o arquivo
    arquivo.close();
}
