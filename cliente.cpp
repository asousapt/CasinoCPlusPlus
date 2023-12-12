#include <iostream>
#include <iomanip>
#include <string>
#include "cliente.h"
#include "uteis.h"

Cliente::Cliente(){

}

Cliente::~Cliente(){
    
}

Cliente::Cliente(int numeroCl, string nomeCl, int saldoCl) {
    numero = numeroCl;
    nome = nomeCl;
    saldo = saldoCl;
    nVezesGanhou = 0;
    apostaPendente = 0;
    nJogadas = 0;


    Uteis U = Uteis();
    int valor = U.valorRand(25,100);
    percentAposta = valor;
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

string Cliente::getNome() {
    return this->nome;
}

float Cliente::getSaldo(){
    return this->saldo;
}

void Cliente::incrSaldo(float incr){
    saldo = saldo + incr;
}

float Cliente::percentSaldo(){
    return saldo * (percentAposta/100);
}

void Cliente::setApostaPendente(float aposta){
    apostaPendente = aposta;
}
    
float Cliente::getApostaPendente(){
    return apostaPendente;
}

//funcao que mostra um cliente 
void Cliente::mostrar() {
    cout << this->numero << "\t" << this->nome << left << setw(35) << "\t" << this->saldo << endl;
} 

