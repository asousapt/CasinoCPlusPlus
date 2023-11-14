#include <iostream>
#include <ctime>
#include "relogio.h"
using namespace std;

relogio::relogio(){}

relogio::~relogio(){}

relogio::relogio(int salto, time_t hora_abertura){
    InicioReal = time(0);
    incr = salto;
    InicioSim = hora_abertura;
}

//Faz display da hora Simulada
void relogio::verHoraAtual(){
    time_t Dif = difftime(time(0), InicioReal);
    time_t Simulada = InicioSim + Dif * incr;
    
    struct tm *tmp = localtime(&Simulada);

    cout << tmp->tm_hour << "h " << tmp->tm_min << "m\n";
}

//Retorna a hora Simulada
time_t relogio::getHoraAtual(){
    time_t Dif = difftime(time(0), InicioReal);
    time_t Simulada = InicioSim + Dif * incr;
    return Simulada;
}

// Funcão de esperar em segundos
void relogio::WaitSegundos(int s){
    clock_t T0 = clock();
    clock_t T1 = T0 + s;
    while (clock() < T1);
}

// Funcão de esperar que transforma o enviado para segundos e chama a função anterior
void relogio::Wait(int s){
    WaitSegundos(s*CLOCKS_PER_SEC);
}
