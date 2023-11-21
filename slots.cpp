#include "slots.h"


slots::slots(int X, int Y) : maquina(X, Y, (float)10, (float)40, (float)100, (float)40, (float)30){
    
}

slots::~slots(){

}

string slots::getTipo(){
    return "slots";
}
