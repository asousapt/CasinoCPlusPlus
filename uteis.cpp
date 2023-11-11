#include <iostream>
#include <sstream>
#include <fstream>
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


