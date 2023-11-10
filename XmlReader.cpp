#include <iostream>
#include <string>
#include <sstream>
#include <fstream>
#include "XmlReader.h"

XmlReader::XmlReader(){}

XmlReader::~XmlReader() {};

XmlReader::XmlReader(string nome, XmlReader *anterior) {
    this->nome = nome;
    this->anterior = anterior;
    this->dados = std::map<std::string, std::string>();
};

string XmlReader::getNome() {
    return this->nome;
}

void XmlReader::setNome(string nome) {
    this->nome = nome;
} ;

XmlReader* XmlReader::getAnterior() {
    return this->anterior;
};

void XmlReader::parseXML(string textoXml, XmlReader* parent) {
    std::istringstream iss(textoXml);
    std::string linha;
    XmlReader* _parent = parent;
    int root = 0;

    while (std::getline(iss, linha)) {
        string tag = "";
        string valor = "";
        bool eDados = false; 
        bool eAbertura = false; 
        bool eFecho = false;
        XmlReader * ultimaLista = nullptr;

        getTag(linha, tag, valor, eDados, eAbertura, eFecho);
        
        if (root == 0) {
            if (eAbertura && tag.length() > 0) {
                this->setNome(tag);
                this->setParent(this);
                _parent = this;
            } else {
                cout << "O ficheiro XML nao contem raiz" << endl; 
                return;
            }
        } else {
            // No caso de nao ser raiz 
            if (eDados == true) {
                this->adicionarDados(tag, valor, _parent);
            }

           if (eAbertura == true) {
                XmlReader* novoNo = new XmlReader(tag, _parent);
                _parent->addFilho(novoNo);
                _parent = novoNo;
            }

            if (eFecho == true) {
                // Vai para o no anterior
                _parent = _parent->getAnterior();
            }
        }
       root++;
    };
};

// funcao vai buscar os dados todos verifica se é abertura, fecho, ou dados 
void XmlReader::getTag(const string& linha, string &tag, string &valor, bool &dados, bool &abertura, bool &fecho) {
    std::size_t posicaoInicial = linha.find("<",0);
    std::size_t posicaoFinal = linha.find(">",0);
    if (posicaoInicial == std::string::npos || posicaoFinal == std::string::npos || posicaoFinal <= posicaoInicial) {
        // caso nao seja uma linha valida
        tag = "";
        valor = "";
        dados = false;
        abertura = false; 
        fecho = false;
    }
    std::size_t posicaoInicial2 = linha.find("</", posicaoInicial+1);
    std::size_t posicaoInicial3 = linha.find("</", 0);

    // no caso de abertura de tag 
    if (posicaoInicial != std::string::npos && posicaoFinal != std::string::npos && posicaoInicial3 == std::string::npos) {
        tag = linha.substr(posicaoInicial+1, posicaoFinal-posicaoInicial-1);
        valor = "";
        dados = false; 
        abertura = true;;
        fecho = false;
    }

    // no caso de fecho de tag 
    if (posicaoInicial != std::string::npos && posicaoFinal != std::string::npos && posicaoInicial3 != std::string::npos and posicaoInicial3 == posicaoInicial) {
        tag = "";
        valor = "";
        dados = false; 
        abertura = false;;
        fecho = true;
    }
    
     // no caso de ler-mos atributos
    if (posicaoInicial != std::string::npos && posicaoFinal != std::string::npos && posicaoInicial2 != std::string::npos && posicaoInicial2 > posicaoFinal) {
        tag = linha.substr(posicaoInicial+1, posicaoFinal-posicaoInicial-1);
        valor = linha.substr(posicaoFinal+1, posicaoInicial2-posicaoFinal-1);
        dados = true; 
        abertura = false;
        fecho = false;
    }
};

void XmlReader::adicionarDados(string chave, string valor, XmlReader * parent) {
    parent->dados[chave] = valor;
}



int XmlReader::temDados() {
    return this->dados.size();
 }

 map<string, string>* XmlReader::getDados() {
    return &this->dados;
 }

 int XmlReader::temFilhos() {
    return filhos.size();
 }

 void XmlReader::setParent(XmlReader* _parent) {
    this->anterior = _parent;
 }

void XmlReader::addFilho(XmlReader* filho) {
    filhos.push_back(filho);
}



 XmlReader* XmlReader::getParent() {
    return this->anterior;
 }
 
void XmlReader::mostraDados() {
    for (const auto& dado : this->dados) {
        cout << dado.first << " - " << dado.second << endl;
    }
}

void XmlReader::showlista() {
    cout << endl;
    for (auto it = filhos.begin(); it != filhos.end(); ++it) {
        cout << (*it)->getNome() << " " << (*it)->temFilhos() << endl;
    }
}

