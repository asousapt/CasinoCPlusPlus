#include <iostream>
#include <sstream>
#include <fstream>
#include <cstdlib> 
#include "uteis.h"

// Funcao que carrega ficheiro para string passando apemas o nome do ficheiro
 string Uteis::loadFileToString(string nomeFicheiro) {
    string buffer;
    char c;

    ifstream in(nomeFicheiro );
    if ( !in ) {
        cout << nomeFicheiro << "Ficheiro não encontrado";   
        return "";
    }

    while ( in.get( c ) ) buffer += c;
    in.close();
    return buffer;
}

// Função que pede um valor ao utilizador passando a mensagem
string Uteis::pedeValor(string mensagem) {
    string valor =""; 
    while (valor.length() == 0)
    {
        cout << mensagem << endl;
        cin >> valor;
    }
    return valor;
}

int Uteis::valorRand(int min,int max){
    return min + std::rand() % (max - min + 1);
}

 string Uteis::retornaStrHoras(int hora, int minutos) {
    string horasTemp = "";
    string minutosTemp = "";
    
    if (hora < 10) {
        horasTemp = "0" + to_string(hora);
    } else {
        horasTemp = to_string(hora);
    }

    if (minutos < 10 ) {
        minutosTemp = "0" + to_string(minutos);
    } else {
        minutosTemp =  to_string(minutos);
    }
    
    return horasTemp + ":" + minutosTemp;
 }

