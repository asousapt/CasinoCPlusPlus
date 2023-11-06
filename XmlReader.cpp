#include <iostream>
#include <string>
#include <sstream>
#include <fstream>
#include "XmlReader.h"

XmlReader::XmlReader(string ficheiro) {
     string buffer;
   char c;

   ifstream in(ficheiro );
   if ( !in ) {
        cout << ficheiro << "Ficheiro não encontrado";   
        exit( 1 ); 
    }

   while ( in.get( c ) ) buffer += c;
   in.close();

    this->nomeFicheiro = ficheiro;
    this->textoCompleto = buffer;
    this->noClientes = getNoUnico("clienteslista");
}

string XmlReader::getNoUnico(string tagNo) {
std::size_t posicaoInicial = textoCompleto.find("<" + tagNo + ">"); 
if (posicaoInicial!=std::string::npos) {
    posicaoInicial += tagNo.length()+2;
    int posicaoFinal = textoCompleto.find("</" + tagNo + ">");
    return textoCompleto.substr(posicaoInicial, posicaoFinal-posicaoInicial);
}
return "";
}

    
list<Cliente*>* XmlReader::getListaClientes() {
   
}
// string getNode(string texto, string tagNo) {
//     std::size_t posicaoInicial = texto.find("<" + tagNo + ">"); 
//     if (posicaoInicial!=std::string::npos) {
//         posicaoInicial += tagNo.length()+2;
//         int posicaoFinal = texto.find("</" + tagNo + ">");
//         return texto.substr(posicaoInicial, posicaoFinal-posicaoInicial);
//     }
//     return "";
// }
