#ifndef PTHREADS_H
#define PTHREADS_H
#include <vector>
#include <string>
#include <fstream>
#include <iostream>




class ParaleloThreads{
    public:
        ParaleloThreads();
        std::vector<std::vector<int>>* MultiplicarMatrizesThreads();
        void ThreadCalculo(std::vector<std::vector<int>> matriz1, std::vector<std::vector<int>> matriz2, int numeroLinha, int numeroColuna, int contadorArquivo);
        std::vector<std::vector<int>> LerMatriz(std::string nomeArquivo);
        void SalvarMatriz(std::string matriz1, int64_t  tempoDuracao, int contadorArquivo);

    private:
        int numeroP;
        int quantidadeRestante;
        int qntdLinhaMatrizResultado;
        int qntdColunaMatrizResultado;


};
#endif