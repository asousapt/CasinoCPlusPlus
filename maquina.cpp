#include <iostream>
#include <string>
#include "maquina.h"

maquina::maquina(){
    
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

void maquina::exportMQ(ostream &f = std::cout){
    f <<  "ID: [" << id << "]  Tipo: [Maquina]  Estado [" << estadoMaq << endl;
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

