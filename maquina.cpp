#include <iostream>
#include <iomanip>
#include <string>
#include "maquina.h"
#include "uteis.h"

maquina::maquina(int X, int Y, float percGanhar, float percAvaria, float tempMax, float tempAtual, float percAviso){
    nSeq++;

    id = nSeq;
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

void maquina::setEstado(estado stt){
    estadoMaq = stt;
    string estadoStr;
    switch (stt)
    {
    case 1:
        estadoStr = "ON";
        break;
    case 0:
        estadoStr = "OFF";
        break;
    case 2:
        estadoStr = "AVARIADA";
        break;
    }
    cout << "Maquina ["<< id <<"] estado mudado para ["<< estadoStr <<"]\n";
}

void maquina::exportMQ(ostream &f){
    string estadoStr;
    estado est = this->getEstado();
    switch (est){
        case 1:
            estadoStr = "ON";
            break;
        case 0:
            estadoStr = "OFF";
            break;
        case 2:
            estadoStr = "AVARIADA";
            break;
    }
    f <<  "ID: [" << id << "]  Tipo: ["<< this->getTipo() << "]  Estado [" << estadoStr << "]\n";
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

int maquina::getID(){
    return id;
}

string maquina::getTipo() {
    return "Maquina";
}

bool maquina::ganhou(){
    Uteis U = Uteis();

    int valor = U.valorRand(0,100);
    //cout << "PERC GANHAR MAQ " << percentGanhar << " valor " << valor << endl;
    if (valor <= percentGanhar){
        return true;
    }else{
        return false;
    }
}

bool maquina::avaria(){
    Uteis U;

    int valor = U.valorRand(0,100);
    //cout << "Percentagem: " << percentAvaria << " || Valor: " << valor << endl;
    if (valor <= percentAvaria){
        nAvarias = nAvarias + 1;
        return true;
    }else{
        return false;
    }
}

void maquina::reparar(){
    estado e = ON;
    this->setEstado(e);
}

void maquina::incrementarTemp(){

}

void maquina::adicionarTemp(int icr){
    temperaturaAtual = temperaturaAtual + icr;
}
    
bool maquina::checkTemp(){
    if (temperaturaAtual >= temperaturaMax) {
        cout << "A maquina Nº ["<< id <<"] ultrapassou a temperatura adequada!\n";
        return true;
    }else{
        return false;
    }
}

void maquina::AvisarPercentGanhar(){
    if (percentGanhar >= percentagemAviso){
        cout << "A maquina Nº ["<< id <<"] ultrapassou a percentagem adequada para ganhos!\n";
    }
}

void maquina::addCl(Cliente *utl){

}

void maquina::removeTodosCl(){
    
}

Cliente* maquina::pesquisaCl(int numero){
    return nullptr;
}

int maquina::contagemCl(){
    return 0;
}

list<Cliente *>* maquina::getCl(){
    list<Cliente *>* ListaRtn = new list<Cliente*>;
    return ListaRtn;
}

float maquina::getPercentAvaria() {
    return this->percentAvaria;
}

float maquina::getTemperaturaMax() {
    return this->temperaturaMax;
}

float maquina::getPercentagemAviso() {
    return this->percentagemAviso;
}

void maquina::incrVezesJogadas() {
    nUsos = nUsos+1;
}

void maquina::removeCl(Cliente *Cl){
    
}

//mostra unma maquina isolada
void maquina::mostrar() {
    string estadoStr;
    estado est = this->getEstado();
    switch (est)
    {
    case 1:
       estadoStr = "ON";
        break;
    case 0:
        estadoStr = "OFF";
        break;
    case 2:
       estadoStr = "AVARIADA";
        break;
    }
    cout << std::left << setw(10) << this->getTipo() << "\t\t" << to_string(this->posX) << "\t" << to_string(this->posY) << "\t" << estadoStr << "\t" << id << endl;
}


int maquina::getNAvarias(){
    return nAvarias;
}

