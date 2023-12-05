#include "craps.h"
#include "uteis.h"

craps::craps(int X, int Y) : maquina(X, Y, (float)10, (float)10, (float)30, (float)10, (float)20){
    Jogadores = new list<Cliente*>;
}

craps::~craps(){
    delete Jogadores;
}

string craps::getTipo(){
    return "CRAPS";
}

void craps::addCl(Cliente *utl){
    Jogadores->push_back(utl);
}

void craps::removeTodosCl(){
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

Cliente* craps::pesquisaCl(int numero){
    for (auto it = Jogadores->begin(); it != Jogadores->end(); ++it){
        if ((*it)->getNumero() == numero){
            return (*it);
        }
    }
    return nullptr;
}

int craps::contagemCl(){
    return Jogadores->size();
}

list<Cliente *>* craps::getCl(){
    return Jogadores;
}

void craps::removeCl(Cliente *Cl){
    for (auto it = Jogadores->begin(); it != Jogadores->end(); ++it){
        if ((*it)->getNumero() == Cl->getNumero()){
            Jogadores->erase(it);
            break;
        }
    }
}
