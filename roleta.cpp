#include "roleta.h"
#include "uteis.h"

roleta::roleta(int X, int Y) : maquina(X, Y, 47.7, (float)20, (float)100, (float)20, (float)60){
    Jogadores = new list<Cliente*>;
}

roleta::~roleta(){
    delete Jogadores;
}

string roleta::getTipo(){
    return "roleta";
}

void roleta::addCl(Cliente *utl){
    Jogadores->push_back(utl);
}

void roleta::removeTodosCl(){
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

Cliente* roleta::pesquisaCl(int numero){
    for (auto it = Jogadores->begin(); it != Jogadores->end(); ++it){
        if ((*it)->getNumero() == numero){
            return (*it);
        }
    }
    return nullptr;
}

int roleta::contagemCl(){
    return Jogadores->size();
}

list<Cliente *>* roleta::getCl(){
    return Jogadores;
}

void roleta::removeCl(Cliente *Cl){
    for (auto it = Jogadores->begin(); it != Jogadores->end(); ++it){
        if ((*it)->getNumero() == Cl->getNumero()){
            Jogadores->erase(it);
            break;
        }
    }
}

