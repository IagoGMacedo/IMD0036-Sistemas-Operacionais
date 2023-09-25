#ifndef AUXILIAR_H
#define AUXILIAR_H
#include <vector>
#include <string>

class Auxiliar{
    public:
        Auxiliar();
        int LerMatrizes();
        int SalvarMatrizes(std::vector<std::vector<int>> matriz1, int linha1, int coluna1, std::string arquivoMatriz1);

};
#endif