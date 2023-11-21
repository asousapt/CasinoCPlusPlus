#include "craps.h"

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

