#ifndef CLIENTE_H
#define CLIENTE_H
#include <iostream>

using namespace std;

class Cliente{
private:
    int numero; 
    string nome; 
    float saldo;
    float apostaPendente;
    int nVezesGanhou;
    int nJogadas;
    float percentAposta;
public:
    Cliente();
    ~Cliente();
    Cliente(int numeroCl, string nomeCl, int saldoCl);
    void exportCl(ostream &f = std::cout);
    int getNVezesGanhou();
    int getNJogadas();
    int getNumero();
    string getNome();
    float getSaldo();
    void incrJogadas();
    void incrVezesGanhas();
    void incrSaldo(float incr);
    float percentSaldo();
    void setApostaPendente(float aposta);
    float getApostaPendente();
};

#endif // CLIENTE_H

