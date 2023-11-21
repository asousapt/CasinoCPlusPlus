#include <iostream>
#include <fstream>
#include <map>
#include <ctime>
#include <cstdlib> 
#include "XmlReader.h"
#include "uteis.h"
#include "casino.h"
#include "maquina.h"

using namespace std;

int maquina::id = 0;

int main(){
    /** INICIO DO PROGRAMA **/
    srand(time(nullptr));

    /* Vamos pedir ao utilzador que indique um nome para o casino*/
    Uteis utils = Uteis();

    
    cout << "Bem-vindo ao Casino" << endl;
    cout << "#### --------- ####" << endl;
    string nomeCasino = utils.pedeValor("Por favor introduza um nome para o casino");

    // Faz a criação do objecto casino 
    casino cas = casino(nomeCasino);
    string nomeFicheiro = "casino.xml";

    // Faz o load dos dados para dentro do casino 
    if (cas.Load(nomeFicheiro) == false) {
        cout << "Erro ao carregar os dados do casino!" << endl;
    }

   cas.ExportCasino();
   
    
    //  cout << xmlObj.temFilhos() << endl ;
    //xmlObj.showlista();
    // xmlObj.mostraDados();

    

    return 0;
}