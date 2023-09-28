#ifndef PPROCESSOS_H
#define PPROCESSOS_H
#include <vector>
#include <string>
#include <fstream>
#include <iostream>
#include <chrono>
#include <unistd.h>
#include <sys/wait.h>

class ParaleloProcessos{
    private:
        int numeroP;
        int quantidadeRestante;
        int qntdLinhaMatrizResultado;
        int qntdColunaMatrizResultado;
        void setQntdLinhaColuna(int numeroLinha, int numeroColuna);
        int getQntdLinha();
        int getQntdColuna();
    public:
        ParaleloProcessos();
        std::vector<std::vector<int>>* MultiplicarMatrizesProcessos();
        void ProcessoCalculo(std::vector<std::vector<int>> matriz1, std::vector<std::vector<int>> matriz2, int numeroElemento, int qntdColunas, int contadorArquivo, int numeroLinhaTotal, int numeroColunaTotal);
        std::vector<std::vector<int>> LerMatriz(std::string nomeArquivo);
        void SalvarMatriz(std::string matriz1, int64_t  tempoDuracao, int contadorArquivo,int numeroLinhaTotal, int numeroColunaTotal);
        void TestandoProcessos();
};
#endif