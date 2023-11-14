#include <iostream>
#include <fstream>
#include <map>
#include <ctime>
#include "XmlReader.h"
#include "uteis.h"
#include "relogio.h"
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

    //Hora inicio do casino
    struct tm *tmp;
    tmp->tm_hour = 9;
    tmp->tm_min = 0;
    time_t inicio = mktime(tmp);

    //Hora Fim do casino
    tmp->tm_hour = 14;
    tmp->tm_min = 0;
    time_t fim = mktime(tmp);
    
    //Cria relogio 
    relogio *R = new relogio(120,inicio);
    
    //Cria hora de comparação 
    time_t horaRelogio = R->getHoraAtual();

    bool fechar = 0;

    while (fechar == 0) {
        //Conteudo Loop
        R->verHoraAtual();
        horaRelogio = R->getHoraAtual();

        R->Wait(2);
    }

    
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