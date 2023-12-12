#ifndef UTEIS_H
#define UTEIS_H
#include <iostream>
#include <sstream>

using namespace std;

class Uteis {
    public: 
        Uteis() {};
        string loadFileToString(string nomeFicheiro);
        string pedeValor(string mensagem);
        int valorRand(int min,int max);
        string retornaStrHoras(int hora, int minutos);
        string getTimestamp();
        int diferencaHoras(time_t horaInicio, time_t horaFim);
};

#endif