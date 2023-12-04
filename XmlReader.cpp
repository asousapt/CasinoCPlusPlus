#include <iostream>
#include <string>
#include <sstream>
#include <fstream>
#include <stack>
#include "XmlReader.h"

XmlReader::XmlReader(){};

XmlReader::~XmlReader() {
    for(auto it = filhos.begin(); it != filhos.end(); ++it) {
        delete *it;
    };
};

XmlReader::XmlReader(string nome, XmlReader *anterior) {
    this->nome = nome;
    this->anterior = anterior;
};

// Obtém o atributo nome
string XmlReader::getNome() {
    return this->nome;
}

// faz set do atributo nome 
void XmlReader::setNome(string nome) {
    this->nome = nome;
} ;

// retorna um ponteiro para o objecto anterior
XmlReader* XmlReader::getAnterior() {
    return this->anterior;
};

// método que faz o parse do XML. Recebe o texto do XML carregado numa string e uma referencia para o parante
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

// Método recebe uma string, analisa a sua composição e retorna o valor da tag, valor e se é do tipo abertura, fecho ou dados
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

// Método que adiciona dados ao hashmap 
void XmlReader::adicionarDados(string chave, string valor, XmlReader * parent) {
    parent->dados[chave] = valor;
}

// Métoso que indica se o nó tem ou não dados
int XmlReader::temDados() {
    return this->dados.size();
 }

// retorna o hashmap do nosso objecto que contém os dados do nosso XML
map<string, string>* XmlReader::getDados() {
    return &this->dados;
}

// método que indica se o nó tem dependentes, isto é, elementos na lista
int XmlReader::temFilhos() {
    return filhos.size();
}

// Método para atribuir um parente ao nó corrente
void XmlReader::setParent(XmlReader* _parent) {
    this->anterior = _parent;
}

// Método para adicionar objectos à lista 
void XmlReader::addFilho(XmlReader* filho) {
    filhos.push_back(filho);
}

// mostra os dados de um mapa 
void XmlReader::mostraDados() {
    for (const auto& dado : this->dados) {
        cout << dado.first << " - " << dado.second << endl;
    }
}

// Mostra o conteudo dento da lista do objecto e se o objecto dentro da lista tem filhos
void XmlReader::showlista() {
    for (auto it = filhos.begin(); it != filhos.end(); ++it) {
        cout << (*it)->getNome() << " " << (*it)->temFilhos() << endl;
    }
}

// retorna uma objecto XMLReader* cpm um bloco de nós agrupados pelo tagName. Caso retorne nulo o bloco nao existe
XmlReader* XmlReader::getNodeBlockByTagName(string tagName) {
    for (auto it = filhos.begin(); it != filhos.end(); ++it) {
        int res = (*it)->getNome().compare(tagName);
        if (res == 0) {
            return (*it);
        }
    }
    return nullptr;
}

// Recebe a key do map e retorna o valor guardado. Caso seja uma string vazia a key nao existe
string XmlReader::extractDataFromMap(string key) {
    for (const auto& dado : this->dados) {
        int res = dado.first.compare(key);
        if (res == 0) {
            return dado.second;
        }
    }
    return "";
}

// Faz um return de uma lista de XMLReader
list<XmlReader*> XmlReader::getFilhos() {
    return this->filhos;
}

 bool XmlReader::saveAsXML(string nomeFicheiro) {
    std::stack<string> tags;
    //abre o ficheiro 
    std::ofstream outputFile(nomeFicheiro);

    // Garante que o ficheiro está aberto
    if (outputFile.is_open()) {         
        writeXMLRecursive(outputFile, this);
        outputFile.close();
    }
    return true;
 }

// funcao recursiva que trata de escrever o no filho

void XmlReader::writeXMLRecursive(std::ofstream& outputFile, XmlReader* no) {
        

        // Write opening tag
        outputFile << "<" << no->getNome() << ">" << endl;

        // Write attributes if any

        map<string,string>  *dados = no->getDados();
        for (const auto& dado : *dados) {
            outputFile << "<" << dado.first << ">" << dado.second << "</" << dado.first << ">" << endl;
        }

            // Recursively write children
            for (auto child : no->getFilhos()) {
                writeXMLRecursive(outputFile, child);
            }

            // Write closing tag
            outputFile << "</" << no->getNome() << ">" << std::endl;
        // }
    }