#ifndef XMLREADER_H
#define XMLREADER_H
#include <iostream>
#include <string>
#include <list>

using namespace std;

class Cliente;

class XmlReader {
   public:
        string nomeFicheiro;
        string textoCompleto; 
        string noClientes;
        string noMaquinas;

    XmlReader() {};
    ~XmlReader() {};
    XmlReader(string ficheiro);
    string getNoUnico(string tagNo);
    list<Cliente*>* getListaClientes();
    //static string getNode(string texto, string tagNo);
    

};

#endif // XMLREADER_H