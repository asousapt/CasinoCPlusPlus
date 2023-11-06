#include <iostream>
#include <fstream>
#include "XmlReader.h"
using namespace std;

int main(){
    string nomeFicheiro = "casino.xml";
    XmlReader xmlCasino = XmlReader(nomeFicheiro);
    string nomeCasino = xmlCasino.getNoUnico("horaAbertura");
    string horaAbertura = xmlCasino.getNoUnico("nome");
    string horafecho = xmlCasino.getNoUnico("horafecho");
    cout << xmlCasino.noClientes << endl;
    
}