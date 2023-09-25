#include "../include/Auxiliar.h"
#include "../include/Sequencial.h"


int main(){
    Auxiliar auxiliar =* new Auxiliar();
    Sequencial sequencial =* new Sequencial();

    auxiliar.LerMatrizes();
    sequencial.MultiplicarMatrizes();
    return 0;
}