#include "craps.h"
#include "uteis.h"

craps::craps(int X, int Y) : maquina(X, Y, (float)10, (float)10, (float)30, (float)10, (float)20){
    Jogadores = new list<Cliente*>;
}

craps::~craps(){

}

string craps::getTipo(){
    return "craps";
}

void craps::addCl(Cliente *utl){
    Jogadores->push_back(utl);
}

void craps::removeCl(){
    for (auto it = Jogadores->end(); it != Jogadores->end(); --it){
        Jogadores->erase(it);
    }
}

void craps::incrementarTemp(){
    Uteis U;
    int Valor = U.valorRand(0,4);

    if(Jogadores->size() == 0){
        Valor = Valor * (-1);
    }

    this->adicionarTemp(Valor);
}
