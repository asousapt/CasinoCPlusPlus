#ifndef CLIENTE_H
#define CLIENTE_H
#include <iostream>

using namespace std;

class Cliente{
private:
    int numero; 
    string nome; 
    int saldo;
    int nVezesGanhou;
    int nJogadas;
public:
    Cliente();
    ~Cliente();
    Cliente(int numeroCl, string nomeCl, int saldoCl);
    void exportCl(ostream &f = std::cout);
    int getNVezesGanhou();
    int getNJogadas();
    int getNumero();
    void incrJogadas();
    void incrVezesGanhas();
};

#endif // CLIENTE_H

