#include <iostream>
#include "casino.h"

casino::casino(string _nome, time_t _hora_abertura,time_t _hora_fecho){
    nome = _nome;
    hora_abertura = _hora_abertura;
    hora_fecho = _hora_fecho;
}

casino::~casino(){
    
}