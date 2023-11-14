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
    int getNVezesGanhou();
    int getNJogadas();
};

#endif // CLIENTE_H

