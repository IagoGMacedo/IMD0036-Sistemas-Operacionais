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
        void ThreadCalculo(std::vector<std::vector<int>> matriz1, std::vector<std::vector<int>> matriz2);
        std::vector<std::vector<int>> LerMatriz(std::string nomeArquivo);
    private:
        int numeroLinha;
        int numeroColuna;
        int numeroP;
        int quantidadeRestante;

};
#endif