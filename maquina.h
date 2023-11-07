#include <iostream>
using namespace std;

enum estado {ON = 1,OFF = 0,AVARIADA = 2};

class maquina{
private:
    int numero;
    estado estadoMaq;
public:
    maquina(/* args */);
    ~maquina();
    virtual string getTipo();
};


