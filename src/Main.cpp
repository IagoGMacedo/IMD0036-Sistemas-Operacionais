#include "../include/Auxiliar.h"
#include "../include/Sequencial.h"
#include "../include/ParaleloThreads.h"
#include "../include/ParaleloProcessos.h"




int main(){
    Auxiliar auxiliar =* new Auxiliar();
    Sequencial sequencial =* new Sequencial();
    
    ParaleloThreads paralelo =* new ParaleloThreads();
    
    ParaleloProcessos processos =* new ParaleloProcessos();
    auxiliar.LerMatrizes();
    sequencial.MultiplicarMatrizes();
    std::cout << "finalizado auxiliar e sequencial" << std::endl;
    //processos.MultiplicarMatrizesProcessos();
    processos.TestandoProcessos();
    //paralelo.MultiplicarMatrizesThreads();
    return 0;
}