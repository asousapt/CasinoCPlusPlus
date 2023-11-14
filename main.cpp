#include <iostream>
#include <fstream>
#include <map>
#include <ctime>
#include "XmlReader.h"
#include "uteis.h"
using namespace std;

void verHora(time_t hora){
    struct tm *tmp = localtime(&hora);

    cout << tmp->tm_hour << "h " << tmp->tm_min << "m\n";
}

int main(){
    // string nomeFicheiro = "casino.xml";
    string nomeFicheiro = "casino.xml";
    Uteis util = Uteis();
    string textoXml = util.loadFileToString(nomeFicheiro);
    XmlReader xmlObj = XmlReader();
    
    xmlObj.parseXML(textoXml, nullptr);

    
    //  cout << xmlObj.temFilhos() << endl ;
    xmlObj.showlista();
    // xmlObj.mostraDados();

    // vai buscar blocos de repeticao no XML agregados no nó principal
    XmlReader* listaClientes = xmlObj.getNodeBlockByTagName("clienteslista");
    if (listaClientes != nullptr) { 
        list<XmlReader*> filhos = listaClientes->getFilhos();
        if (!filhos.empty()) { 
            for (auto it = filhos.begin(); it != filhos.end(); ++it) {
                XmlReader* temp = (*it);
                // basta passar a key do map e é extraido o valor           
                cout << temp->extractDataFromMap("numero")  << " -> " << temp->extractDataFromMap("nome") << endl;
            }
        }
    }    

    return 0;
}