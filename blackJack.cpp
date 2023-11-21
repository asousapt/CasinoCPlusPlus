#include "blackJack.h"

blackJack::blackJack(int X, int Y) : maquina(X, Y, (float)1, (float)10, (float)30, (float)10, (float)10){
    
}

blackJack::~blackJack(){

}

string blackJack::getTipo(){
    return "blackjack";
}

