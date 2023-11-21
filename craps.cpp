#include "craps.h"

craps::craps(int X, int Y) : maquina(X, Y, (float)10, (float)10, (float)30, (float)10, (float)20){
    
}

craps::~craps(){

}

string craps::getTipo(){
    return "craps";
}

