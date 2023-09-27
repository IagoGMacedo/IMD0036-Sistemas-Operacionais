#ifndef PTHREADS_H
#define PTHREADS_H
#include <vector>
#include <string>
#include <fstream>
#include <iostream>

class ParaleloThreads{
    private:
        int numeroP;
        int quantidadeRestante;
        int qntdLinhaMatrizResultado;
        int qntdColunaMatrizResultado;
        void setQntdLinhaColuna(int numeroLinha, int numeroColuna);
        int getQntdLinha();
        int getQntdColuna();
    public:
        ParaleloThreads();
        std::vector<std::vector<int>>* MultiplicarMatrizesThreads();
        void ThreadCalculo(std::vector<std::vector<int>> matriz1, std::vector<std::vector<int>> matriz2, int numeroElemento, int qntdColunas, int contadorArquivo, int numeroLinhaTotal, int numeroColunaTotal, auto start_time);
        std::vector<std::vector<int>> LerMatriz(std::string nomeArquivo);
        void SalvarMatriz(std::string matriz1, int64_t  tempoDuracao, int contadorArquivo,int numeroLinhaTotal, int numeroColunaTotal);

};
#endif