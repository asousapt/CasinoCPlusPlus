#include <iostream>
using namespace std;

enum estado {ON = 1,OFF = 0,AVARIADA = 2};

class maquina{
private:
    static int id;
    estado estadoMaq;
    float percentGanhar,percentAvaria;
    int nAvarias,nUsos;
    int posX,posY;
    string TipoMaq;
public:
    maquina();
    ~maquina();
    virtual string getTipo();
    void desligarMq();
    bool compareId(int num);
    estado getEstado();
    void exportMQ(ostream &f = std::cout);
    int getID();
    int compareNUsos(maquina *MQ);
    float getPercentGanhar();
};


