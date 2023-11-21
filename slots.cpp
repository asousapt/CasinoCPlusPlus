#include "slots.h"
#include "uteis.h"

slots::slots(int X, int Y) : maquina(X, Y, (float)10, (float)40, (float)100, (float)40, (float)30){
    C = nullptr;
}

slots::~slots(){

}

string slots::getTipo(){
    return "slots";
}

void slots::setCl(Cliente *utl){
    C = utl;
}

void slots::removeCl(){
    C = nullptr;
}

void slots::incrementarTemp(){
    Uteis U;
    int Valor = U.valorRand(0,4);

    if(!C){
        Valor = Valor * (-1);
    }

    this->adicionarTemp(Valor);
}

