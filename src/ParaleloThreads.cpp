#include "../include/ParaleloThreads.h"
#include <thread>

ParaleloThreads::ParaleloThreads(){
    this->numeroP = 1; //no minimo 1
    this->quantidadeRestante = 0;
}

void ParaleloThreads::ThreadCalculo(std::vector<std::vector<int>> matriz1, std::vector<std::vector<int>> matriz2, int numeroElemento, int contadorArquivo){
    auto start_time = std::chrono::high_resolution_clock::now();
    int contadorLocal = 0;
    int numeroLinha = numeroElemento/matriz1.size();
    int numeroColuna = numeroElemento % matriz2[0].size();
    int valor = 0;
    std::string stringValores = "";
    for(int i = numeroLinha;i<matriz1.size();i++){
        for(int j =numeroColuna;j<matriz2[0].size();j++){
            for(int k=0;k<matriz1[0].size(); k++){
                valor +=matriz1[i][k] * matriz2[k][j];
                stringValores += "c";
                stringValores.append(std::to_string(i));
                stringValores.append(std::to_string(j)+" ");
                stringValores.append(std::to_string(valor)+"\n");
                this->quantidadeRestante--;
                //this->numeroColuna++;
                contadorLocal++;
                if(contadorLocal == this->numeroP) //talvez adicionar mais uma condição aqui 
                    break;    
            }
        }
        valor = 0;
    }
    auto end_time = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end_time - start_time);

    this->SalvarMatriz(stringValores, duration.count(), contadorArquivo);
}

std::vector<std::vector<int>>* ParaleloThreads::MultiplicarMatrizesThreads(){
    //Recuperando matrizes
    std::vector<std::vector<int>> matriz1 = this->LerMatriz("../output/matriz1.txt");
    std::vector<std::vector<int>> matriz2 = this->LerMatriz("../output/matriz2.txt");

    this->qntdLinhaMatrizResultado  = matriz1.size();
    this->qntdColunaMatrizResultado = matriz2[0].size();

    //verificando se a multiplicação de matrizes eh possivel
    if(!matriz1[0].size() == matriz2.size()){
        std::cout << "não dá pra multiplicar isso" << std::endl;
        return nullptr;
    }

    this->quantidadeRestante = matriz1.size() * matriz2[0].size(); //numero total de elementos da matriz resultado
    int contadorArquivo = 0;
    int numeroElemento = 1;
    ParaleloThreads objeto;
    std::vector<std::thread> threads;
    while(this->quantidadeRestante > 0){
        //std::thread t1(ThreadCalculo, matriz1, matriz2, numeroLinha, numeroColuna, contadorArquivo);
        threads.emplace_back([&objeto, matriz1, matriz2, numeroElemento, contadorArquivo]() {
        objeto.ThreadCalculo(matriz1, matriz2, numeroElemento, contadorArquivo);
        });
        /*
        std::thread t1([&objeto, matriz1, matriz2, numeroLinha, numeroColuna, contadorArquivo]() {
        objeto.ThreadCalculo(matriz1, matriz2, numeroLinha, numeroColuna, contadorArquivo);
        });
        */
        contadorArquivo++;
        numeroElemento += this->numeroP;
        this->quantidadeRestante -= this->numeroP;
    }
    for (std::thread& thread : threads) {
        thread.join();
    }

    std::cout << "Todas as threads terminaram." << std::endl;

    return nullptr;
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

void ParaleloThreads::SalvarMatriz(std::string matriz1, int64_t  tempoDuracao, int contadorArquivo){
    std::string arquivoResultado = "../output/matrizResultado";
    arquivoResultado.append(std::to_string(contadorArquivo)+".txt");
    std::ofstream arquivo(arquivoResultado);

    // Verifique se o arquivo foi aberto c  om sucesso
    if (!arquivo.is_open()) {
        std::cerr << "Erro ao abrir o arquivo." << std::endl;
    }

    // Escreva o conteúdo no arquivo
    arquivo << this->qntdLinhaMatrizResultado << " " << this->qntdColunaMatrizResultado << std::endl; // linhas e colunas
    arquivo << matriz1;
    arquivo << tempoDuracao;
    // Feche o arquivo
    arquivo.close();

    std::cout << "Texto escrito com sucesso no arquivo " << arquivoResultado << std::endl;
}
