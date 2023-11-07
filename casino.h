#include <iostream>
#include <list>
#include <ctime>
#include "cliente.h"
#include "maquina.h"
using namespace std;

class casino{
private:
    string nome;
    time_t hora_abertura;
    time_t hora_fecho;
    list<Cliente *> ListaCl;
    list<maquina *> ListaMq;
public:
    casino(string _nome, time_t _hora_abertura,time_t _hora_fecho);
    ~casino();
};

