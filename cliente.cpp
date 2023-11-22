#include <iostream>
#include <string>
#include "cliente.h"

Cliente::Cliente(){

}

Cliente::~Cliente(){
    
}

Cliente::Cliente(int numeroCl, string nomeCl, int saldoCl) {
    this->numero = numeroCl;
    this->nome = nomeCl;
    this->saldo = saldoCl;
}

void Cliente::exportCl(ostream &f){
    f << "Nº: ["<< this->numero <<"] Nome: ["<< this->nome <<"] Saldo: ["<< this->saldo <<"]\n";
}

int Cliente::getNVezesGanhou(){
    return nVezesGanhou;
}

int Cliente::getNJogadas(){
    return nJogadas;
}

int Cliente::getNumero(){
    return numero;
}

void Cliente::incrJogadas(){
    nJogadas = nJogadas+1;
}

void Cliente::incrVezesGanhas(){
    nVezesGanhou = nVezesGanhou+1;
}

