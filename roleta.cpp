#include "roleta.h"
#include "uteis.h"

roleta::roleta(int X, int Y) : maquina(X, Y, 47.7, (float)20, (float)100, (float)20, (float)60){
    Jogadores = new list<Cliente*>;
}

roleta::~roleta(){

}

string roleta::getTipo(){
    return "roleta";
}

void roleta::addCl(Cliente *utl){
    Jogadores->push_back(utl);
}

void roleta::removeCl(){
    for (auto it = Jogadores->end(); it != Jogadores->end(); --it){
        Jogadores->erase(it);
    }
}

void roleta::incrementarTemp(){
    Uteis U;
    int Valor = U.valorRand(0,4);

    if(Jogadores->size() == 0){
        Valor = Valor * (-1);
    }

    this->adicionarTemp(Valor);
}

