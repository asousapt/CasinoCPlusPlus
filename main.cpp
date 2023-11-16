#include <iostream>
#include <fstream>
#include <map>
#include <ctime>
#include "XmlReader.h"
#include "uteis.h"
#include "casino.h"
using namespace std;


int main(){
    /** INICIO DO PROGRAMA **/
    /* Vamos pedir ao utilzador que indique um nome para o casino*/
    Uteis utils = Uteis();

    
    cout << "Bem-vindo ao Casino" << endl;
    cout << "#### --------- ####" << endl;
    string nomeCasino = utils.pedeValor("Por valor introduza um nome para o casino");

    // Faz a criação do objecto casino 
    casino cas = casino(nomeCasino);
    string nomeFicheiro = "casino.xml";
    // Faz o load dos dados para dentro do casino 
    cas.Load(nomeFicheiro);


    
    //  cout << xmlObj.temFilhos() << endl ;
    //xmlObj.showlista();
    // xmlObj.mostraDados();

    

    return 0;
}