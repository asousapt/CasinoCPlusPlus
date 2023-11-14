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



