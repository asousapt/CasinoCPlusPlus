#ifndef MAQUINA_H
#define MAQUINA_H
#include <iostream>
#include <list>
#include "cliente.h"

using namespace std;

enum estado {ON = 1,OFF = 0,AVARIADA = 2};


class maquina{
private:
    estado estadoMaq;
    float percentGanhar, percentAvaria, percentagemAviso, temperaturaMax, temperaturaAtual;
    int nAvarias, nUsos, posX, posY, id;
    static int nSeq;
public:
    maquina(int X, int Y, float percGanhar, float percAvaria, float tempMax, float tempAtual, float percAviso);
    ~maquina();
    virtual string getTipo();
    virtual void addCl(Cliente *utl);
    virtual Cliente* pesquisaCl(int numero);
    virtual int contagemCl();
    virtual list<Cliente *>* getCl();
    void desligarMq();
    bool compareId(int num);
    estado getEstado();
    void setEstado(estado stt);
    void exportMQ(ostream &f = std::cout);
    int compareNUsos(maquina *MQ);
    float getPercentGanhar();
    void setPercentagemGanhar(float percent);
    int getPosY();
    int getPosX();
    int getID();
    bool ganhou();
    bool avaria();
    void reparar();
    virtual void incrementarTemp();
    void adicionarTemp(int icr);
    bool checkTemp();
    void AvisarPercentGanhar();
    virtual void removeTodosCl();
    float getPercentAvaria();
    float getTemperaturaMax(); 
    float getPercentagemAviso();
    void incrVezesJogadas();
    virtual void removeCl(Cliente *Cl);
    void mostrar();
    int getNAvarias();
};
#endif


