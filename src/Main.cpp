#include "../include/Auxiliar.h"
#include "../include/Sequencial.h"
#include "../include/ParaleloThreads.h"
#include "../include/ParaleloProcessos.h"



int main(){
    Auxiliar auxiliar =* new Auxiliar();
    //Sequencial sequencial =* new Sequencial();
    
    ParaleloThreads paralelo =* new ParaleloThreads();
    
    //ParaleloProcessos processos =* new ParaleloProcessos();
    int n1, m1, n2, m2;
    std::cout << "Digite quatro números inteiros separados por espaços: " << std::endl;
    std::cin >> n1;
    std::cin >> m1;
    std::cin >> n2;
    std::cin >> m2;
    for(int i = 0; i < 1; i++){
        auxiliar.LerMatrizes(n1, m1, n2, m2);
        //sequencial.MultiplicarMatrizes();
        paralelo.MultiplicarMatrizesThreads();
    }
    //std::cout << "finalizado auxiliar e sequencial" << std::endl;
    //processos.MultiplicarMatrizesProcessos();
    //paralelo.MultiplicarMatrizesThreads();
    //std::cout <<" dels do ceu" <<std::endl;
    //processos.TestandoProcessos();
    
    return 0;
}