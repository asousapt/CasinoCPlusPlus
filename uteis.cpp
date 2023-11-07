#include <iostream>
#include <sstream>
#include <fstream>
#include "uteis.h"

string Uteis::loadFileToString(string nomeFicheiro) {
    string buffer;
    char c;

    ifstream in(nomeFicheiro );
    if ( !in ) {
        cout << nomeFicheiro << "Ficheiro não encontrado";   
        exit(1);
    }

    while ( in.get( c ) ) buffer += c;
    in.close();
    return buffer;
}


