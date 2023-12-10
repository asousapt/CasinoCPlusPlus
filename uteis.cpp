#include <iostream>
#include <sstream>
#include <fstream>
#include <chrono>
#include <random>
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

string Uteis::getTimestamp() {
        // Get the current time
        std::time_t currentTime = std::time(nullptr);
        std::tm* localTime = std::localtime(&currentTime);

        // Format the timestamp as a string
        char buffer[20];
        std::strftime(buffer, sizeof(buffer), "%Y-%m-%d %H:%M:%S", localTime);

        return buffer;
    }


 int Uteis::valorRand(int min,int max){
    auto seed = std::chrono::high_resolution_clock::now().time_since_epoch().count();
    std::mt19937 gen(seed);
    std::uniform_int_distribution<int> distribution(min, max);
    return distribution(gen);
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

