#include "cliente.h"

Cliente::Cliente(/* args */){

}

Cliente::~Cliente(){
    
}

Cliente::Cliente(int numeroCl, string nomeCl, int saldoCl) {
    this->numero = numeroCl;
    this->nome = nomeCl;
    this->saldo = saldoCl;
}