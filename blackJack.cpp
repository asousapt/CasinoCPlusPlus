#include "blackJack.h"
#include "uteis.h"

blackJack::blackJack(int X, int Y) : maquina(X, Y, (float)1, (float)10, (float)30, (float)10, (float)10){
    Jogadores = new list<Cliente*>;
}

blackJack::~blackJack(){
    delete Jogadores;
}

string blackJack::getTipo(){
    return "blackjack";
}

void blackJack::addCl(Cliente *utl){
    Jogadores->push_back(utl);
}

void blackJack::removeTodosCl(){
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

Cliente* blackJack::pesquisaCl(int numero){
    for (auto it = Jogadores->begin(); it != Jogadores->end(); ++it){
        if ((*it)->getNumero() == numero){
            return (*it);
        }
    }
    return nullptr;
}

int blackJack::contagemCl(){
    return Jogadores->size();
}

list<Cliente *>* blackJack::getCl(){
    return Jogadores;
}

void blackJack::removeCl(Cliente *Cl){
    for (auto it = Jogadores->begin(); it != Jogadores->end(); ++it){
        if ((*it)->getNumero() == Cl->getNumero()){
            Jogadores->erase(it);
            break;
        }
    }
}
