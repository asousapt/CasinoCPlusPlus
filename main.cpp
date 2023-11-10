#include <iostream>
#include <fstream>
#include <map>
#include "XmlReader.h"
#include "uteis.h"
using namespace std;

int main(){
    //string nomeFicheiro = "casino.xml";
    string nomeFicheiro = "casino.xml";
    Uteis util = Uteis();
    string textoXml = util.loadFileToString(nomeFicheiro);
    XmlReader xmlObj;
    
    xmlObj.parseXML(textoXml, nullptr);
    
    
    
    //  cout << xmlObj.temFilhos() << endl ;
    xmlObj.showlista();
    //xmlObj.mostraDados();

    
}