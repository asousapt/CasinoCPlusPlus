#ifndef XMLREADER_H
#define XMLREADER_H
#include <iostream>
#include <sstream>
#include <map>
#include <list>

using namespace std;

class XmlReader {
    private: 
        std::string nome;
        std::map<std::string, std::string> dados; 
        list<XmlReader*> filhos;
        XmlReader* anterior;
    public: 
        XmlReader();
        ~XmlReader();
        XmlReader(string nome, XmlReader* anterior);
        string getNome();
        void setNome(string nome);
        void parseXML(string textoXml, XmlReader* parent);
        XmlReader* getAnterior();
        void getTag(const string& linha, string &tag, string &valor, bool &dados, bool &abertura, bool &fecho);
        void adicionarDados(string chave, string valor, XmlReader * parent);
        int temDados();
        map<string, string>* getDados();
        int temFilhos();
        void setParent(XmlReader* _parent);
        XmlReader* getParent();
        void addFilho(XmlReader* filho);
        void showlista();
        void mostraDados();
};

#endif