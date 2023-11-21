#include "roleta.h"

roleta::roleta(int X, int Y) : maquina(X, Y, 47.7, (float)50, (float)50, (float)20, (float)60){
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

