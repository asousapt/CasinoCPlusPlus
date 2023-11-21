#include "blackJack.h"
#include "uteis.h"

blackJack::blackJack(int X, int Y) : maquina(X, Y, (float)1, (float)10, (float)30, (float)10, (float)10){
    Jogadores = new list<Cliente*>;
}

blackJack::~blackJack(){

}

string blackJack::getTipo(){
    return "blackjack";
}

void blackJack::addCl(Cliente *utl){
    Jogadores->push_back(utl);
}

void blackJack::removeCl(){
    for (auto it = Jogadores->end(); it != Jogadores->end(); --it){
        Jogadores->erase(it);
    }
}

void blackJack::incrementarTemp(){
    Uteis U;
    int Valor = U.valorRand(0,4);

    if(Jogadores->size() == 0){
        Valor = Valor * (-1);
    }

    this->adicionarTemp(Valor);
}
