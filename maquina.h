#ifndef MAQUINA_H
#define MAQUINA_H
#include <iostream>

using namespace std;

enum estado {ON = 1,OFF = 0,AVARIADA = 2};

class maquina{
private:
    estado estadoMaq;
    float percentGanhar,percentAvaria, temperaturaMax;
    float temperaturaAtual;
    int nAvarias,nUsos;
    int posX,posY;
public:
    static int id;
    maquina();
    ~maquina();
    virtual string getTipo();
    void desligarMq();
    bool compareId(int num);
    estado getEstado();
    void exportMQ(ostream &f);
    int compareNUsos(maquina *MQ);
    float getPercentGanhar();
    void setPercentagemGanhar(float percent);
    int getPosY();
    int getPosX();
};
#endif


