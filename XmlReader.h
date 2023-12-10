#ifndef XMLREADER_H
#define XMLREADER_H
#include <iostream>
#include <sstream>
#include <map>
#include <list>

using namespace std;
class casino;

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
        XmlReader(string nome, string mensagem, XmlReader *anterior);
        string getNome();
        void setNome(string nome);
        void parseXML(string textoXml, XmlReader* parent);
        XmlReader* getAnterior();
        void getTag(const string& linha, string &tag, string &valor, bool &dados, bool &abertura, bool &fecho);
        void adicionarDados(string chave, string valor, XmlReader * parent);
        list<XmlReader*> getFilhos();
        int temDados();
        map<string, string>* getDados();
        int temFilhos();
        void setParent(XmlReader* _parent);
        XmlReader* getParent();
        void addFilho(XmlReader* filho);
        void showlista();
        void mostraDados();
        XmlReader* getNodeBlockByTagName(string tagName); 
        string extractDataFromMap(string key);
        bool saveAsXML(string nomeFicheiro);
        string writeOpening(string tag, int tabs);
        string writeClosing(string tag, int tabs);
        string writeData(string tag, string valor, int tabs);
        string Tabulacoes(int N);
        void writeXMLRecursive(std::ofstream& outputFile, XmlReader* no);

};

#endif