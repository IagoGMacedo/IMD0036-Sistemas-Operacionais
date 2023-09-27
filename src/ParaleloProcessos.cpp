#include "../include/ParaleloProcessos.h"

ParaleloProcessos::ParaleloProcessos(){
    this->numeroP = 2; //no minimo 1
    this->quantidadeRestante = 0;
    this->qntdLinhaMatrizResultado = 1;
    this->qntdColunaMatrizResultado = 1;

}

void ParaleloProcessos::TestandoProcessos(){
    int valor;
    for(int i =0;i<10;i++){
        valor = fork();
    }
    if(valor==0){
        std::cout << "eh o meninin de papapi eh" << std::endl;
    }
}


void ParaleloProcessos::ProcessoCalculo(std::vector<std::vector<int>> matriz1, std::vector<std::vector<int>> matriz2, int numeroElemento, int qntdColunas, int contadorArquivo, int numeroLinhaTotal, int numeroColunaTotal, auto start_time){
    int contadorLocal = 0;
    std::string stringValores = "";
    std::cout << "qntd de colunas da matriz resultado" << qntdColunas <<std::endl;
    int numeroLinha = numeroElemento/qntdColunas;
    int numeroColuna = numeroElemento % qntdColunas;
    std::cout << "vou printar o " << numeroElemento << "º elemento, vou começar pela linha: " << numeroLinha << " e coluna: " << numeroColuna << std::endl;    
    std::cout << "valor p: " << this->numeroP << std::endl;    
    for(int i = numeroLinha;i<matriz1.size() &&  contadorLocal < this->numeroP;i++){
        for(int j =numeroColuna;j<matriz2[0].size() && contadorLocal < this->numeroP;j++){
            int valor = 0;
            for(int k=0;k<matriz1[0].size(); k++){
                valor +=matriz1[i][k] * matriz2[k][j];
            }
            stringValores += "c";
            stringValores.append(std::to_string(i + 1));
            stringValores.append(std::to_string(j + 1)+" ");
            stringValores.append(std::to_string(valor)+"\n");
            this->quantidadeRestante--;
            //this->numeroColuna++;
            contadorLocal++;
        }
        //this->numeroLinha++;
    }
    auto end_time = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end_time - start_time);

    this->SalvarMatriz(stringValores, duration.count(), contadorArquivo, numeroLinhaTotal, numeroColunaTotal);
}

std::vector<std::vector<int>>* ParaleloProcessos::MultiplicarMatrizesProcessos(){
    //Recuperando matrizes
    std::vector<std::vector<int>> matriz1 = this->LerMatriz("../output/matriz1.txt");
    std::vector<std::vector<int>> matriz2 = this->LerMatriz("../output/matriz2.txt");

    this->setQntdLinhaColuna(matriz1.size(), matriz2[0].size());
    int qntdLinhas = matriz1.size();
    int qntdColunas = matriz2[0].size();
    int qntdColunas2 = matriz2[0].size();


    //verificando se a multiplicação de matrizes eh possivel
    if(!matriz1[0].size() == matriz2.size()){
        std::cout << "não dá pra multiplicar isso" << std::endl;
        return nullptr;
    }

    this->quantidadeRestante = matriz1.size() * matriz2[0].size(); //numero total de elementos da matriz resultado
    int contadorArquivo = 0;
    int numeroElemento = 0;

    //std::cout << "Digite o número P: " << std::endl;
    //std::cin >> this->numeroP;


    while(this->quantidadeRestante > 0){
        //std::thread t1(ThreadCalculo, matriz1, matriz2, numeroLinha, numeroColuna, contadorArquivo);
        auto start_time = std::chrono::high_resolution_clock::now();
        pid_t pId = fork();
        if(pId == 0){
            //processo filho
            //nao sei se o this vai pegar aqui
            this->ProcessoCalculo(matriz1, matriz2, numeroElemento, qntdColunas,  contadorArquivo,qntdLinhas, qntdColunas2, start_time );
        }
        numeroElemento += this->numeroP;
        this->quantidadeRestante -= this->numeroP;
        contadorArquivo++;
    }
    /*
    for (std::thread& thread : threads) {
        thread.join();
    }
    */
    std::cout << "Todas os processos terminaram." << std::endl;

    return nullptr;
}

std::vector<std::vector<int>> ParaleloProcessos::LerMatriz(std::string nomeArquivo){

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

void ParaleloProcessos::SalvarMatriz(std::string matriz1, int64_t  tempoDuracao, int contadorArquivo, int numeroLinhaTotal, int numeroColunaTotal){
    std::string arquivoResultado = "../output/matrizResultado";
    arquivoResultado.append(std::to_string(contadorArquivo)+".txt");
    std::ofstream arquivo(arquivoResultado);

    // Verifique se o arquivo foi aberto c  om sucesso
    if (!arquivo.is_open()) {
        std::cerr << "Erro ao abrir o arquivo." << std::endl;
    }

    std::cout << "qntdlinhas: " << this->getQntdLinha()<<std::endl;

    // Escreva o conteúdo no arquivo
    arquivo << numeroLinhaTotal << " " << numeroColunaTotal << std::endl; // linhas e colunas
    arquivo << matriz1;
    arquivo << tempoDuracao;
    // Feche o arquivo
    arquivo.close();

    std::cout << "Texto escrito com sucesso no arquivo " << arquivoResultado << std::endl;
}

void ParaleloProcessos::setQntdLinhaColuna(int numeroLinha, int numeroColuna){
    this->qntdLinhaMatrizResultado = numeroLinha;
    this->qntdColunaMatrizResultado = numeroColuna;
}

int ParaleloProcessos::getQntdLinha(){
    return this->qntdLinhaMatrizResultado;
}
int ParaleloProcessos::getQntdColuna(){
    return this->qntdColunaMatrizResultado;
}
