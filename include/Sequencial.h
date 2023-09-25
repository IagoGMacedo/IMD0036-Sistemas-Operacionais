#ifndef SEQUENCIAL_H
#define SEQUENCIAL_H

#include <vector>
#include <string>

class Sequencial{
    public:
        Sequencial();
        std::vector<std::vector<int>> LerMatriz(std::string nomeArquivo);
        void MultiplicarMatrizes();
        void SalvarMatriz(std::vector<std::vector<int>> matriz1, int linha1, int coluna1, int64_t  tempoDuracao);



};
#endif