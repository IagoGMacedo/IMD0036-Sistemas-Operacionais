#include "../include/Auxiliar.h"
#include "../include/Sequencial.h"
#include "../include/ParaleloThreads.h"



int main(){
    Auxiliar auxiliar =* new Auxiliar();
    Sequencial sequencial =* new Sequencial();
    ParaleloThreads paralelo =* new ParaleloThreads();

    auxiliar.LerMatrizes();
    sequencial.MultiplicarMatrizes();
    std::cout << "finalizado auxiliar e sequencial" << std::endl;
    paralelo.MultiplicarMatrizesThreads();
    return 0;
}