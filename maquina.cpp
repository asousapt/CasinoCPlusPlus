#include <iostream>
#include <string>
#include "maquina.h"

maquina::maquina(int X, int Y, float percGanhar, float percAvaria, float tempMax, float tempAtual, float percAviso){
    id = id+1;
    estadoMaq = ON;
    percentGanhar = percGanhar;
    percentAvaria = percAvaria;
    temperaturaMax = tempMax;
    temperaturaAtual = tempAtual;
    percentagemAviso = percAviso;
    posX = X;
    posY = Y;
}

maquina::~maquina(){

}

void maquina::desligarMq(){
    estadoMaq = OFF;
}

bool maquina::compareId(int num){
    if (id == num){
        return 1; // True
    } else {
        return 0; // False
    }
}

estado maquina::getEstado(){
    return estadoMaq;
}

void maquina::exportMQ(ostream &f){
    f <<  "ID: [" << id << "]  Tipo: ["<< this->getTipo() << "]  Estado [" << estadoMaq << "]\n";
}

int maquina::compareNUsos(maquina *MQ){
    return nUsos-(MQ->nUsos);
}

float maquina::getPercentGanhar(){
    return percentGanhar;
}

void maquina::setPercentagemGanhar(float percent){
    percentGanhar = percent;
}

int maquina::getPosY(){
    return posY;
}

int maquina::getPosX(){
    return posX;
}

string maquina::getTipo() {
    return "Maquina";
}

