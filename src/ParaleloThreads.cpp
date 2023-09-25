#include "../include/ParaleloThreads.h"
#include <thread>

ParaleloThreads::ParaleloThreads(){
    this->numeroColuna = 0;
    this->numeroLinha = 0;
    this->numeroP = 1; //no minimo 1
    this->quantidadeRestante = 0;
}

void ParaleloThreads::ThreadCalculo(std::vector<std::vector<int>> matriz1, std::vector<std::vector<int>> matriz2){
    auto start_time = std::chrono::high_resolution_clock::now();
    int contadorLocal = 0;
    for(int i = this->numeroLinha;i<matriz1.size();i++){
        for(int j =this->numeroColuna;j<matriz2[0].size();j++){  
            for(int k=0;k<matriz1[0].size(); k++){
                //matriz3[i][j] += matriz1[i][k] * matriz2[k][j]; resultado da multiplicação
                this->quantidadeRestante--;
                this->numeroColuna++;
                contadorLocal++;
                if(contadorLocal == numeroP)
                    break;    
            }
        }
        this->numeroLinha++;
    }
    auto end_time = std::chrono::high_resolution_clock::now();
    //to do: salvar no arquivo

}

std::vector<std::vector<int>>* ParaleloThreads::MultiplicarMatrizesThreads(){
    //Recuperando matrizes
    std::vector<std::vector<int>> matriz1 = this->LerMatriz("matriz1.txt");
    std::vector<std::vector<int>> matriz2 = this->LerMatriz("matriz2.txt");

    //verificando se a multiplicação de matrizes eh possivel
    if(!matriz1[0].size() == matriz2.size()){
        std::cout << "não dá pra multiplicar isso" << std::endl;
        return nullptr;
    }

    this->quantidadeRestante = matriz1.size() * matriz2[0].size(); //numero total de elementos da matriz resultado
    while(this->quantidadeRestante > 0){
        std::thread t1(ThreadCalculo, matriz1, matriz2);
        //ainda tenho que ver quando salvar os pedaços feitos
    }


    std::vector<std::vector<int>> matriz3(matriz1.size(), std::vector<int>(matriz2[0].size()));
    return &matriz3;
}

std::vector<std::vector<int>> ParaleloThreads::LerMatriz(std::string nomeArquivo){

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

    for(int i =0;i<nLinhas;i++){
        for(int j=0;j<nColunas;j++){
            std::cout << matriz1[i][j] <<" ";
        }
        std::cout<< "\n";
    }

    return matriz1;
};