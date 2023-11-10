#include <iostream>
#include <fstream>
#include <map>
#include "XmlReader.h"
#include "uteis.h"
using namespace std;

int main(){
    string nomeFicheiro = "casino.xml";
    Uteis util = Uteis();
    string testoXml = util.loadFileToString(nomeFicheiro);
    XmlReader xmlObj = XmlReader("", nullptr);
    std::istringstream iss(testoXml);
    xmlObj.parseXML(iss, &xmlObj, true);
map<string, string>* dado = xmlObj.getDados();
    
    for(auto it= dado->begin(); it != dado->end(); ++it) {
        cout << it->first << " - " << it->second << endl;
    }
    //  cout << xmlObj.temFilhos() << endl ;
     //xmlObj.showlista();
}