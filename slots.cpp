#include "slots.h"
#include "uteis.h"

slots::slots(int X, int Y) : maquina(X, Y, (float)10, (float)40, (float)100, (float)40, (float)30){
    C = nullptr;
}

slots::~slots(){

}

string slots::getTipo(){
    return "SLOTS";
}

void slots::setCl(Cliente *utl){
    C = utl;
}

void slots::removeTodosCl(){
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

Cliente* slots::pesquisaCl(int numero){
    if (C->getNumero() == numero){
        return C;
    }else{
        return nullptr;
    }
}

int slots::contagemCl(){
    if (C){
        return 1;
    }else{
        return 0;
    }
}

list<Cliente *>* slots::getCl(){
    list<Cliente *>* ListaRtn = new list<Cliente*>;
    ListaRtn->push_back(C);
    return ListaRtn;
}

void slots::removeCl(Cliente *Cl){
    if (C->getNumero() == Cl->getNumero()){
        C = nullptr;
    }
}

