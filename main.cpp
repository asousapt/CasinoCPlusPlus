#include <iostream>
#include <fstream>
#include <map>
#include <ctime>
#include "XmlReader.h"
#include "uteis.h"
#include "relogio.h"
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

   
    
    


    //Hora inicio do casino
    // struct tm *tmp;
    // tmp->tm_hour = 9;
    // tmp->tm_min = 0;
    // time_t inicio = mktime(tmp);

    // //Hora Fim do casino
    // tmp->tm_hour = 14;
    // tmp->tm_min = 0;
    // time_t fim = mktime(tmp);
    
    // //Cria relogio 
    // relogio *R = new relogio(120,inicio);
    
    // //Cria hora de comparação 
    // time_t horaRelogio = R->getHoraAtual();

    // while (difftime(horaRelogio,fim) < 0) {
    //     //Conteudo Loop
    //     R->verHoraAtual();
    //     horaRelogio = R->getHoraAtual();

    //     R->Wait(2);
    // }

    
    //  cout << xmlObj.temFilhos() << endl ;
    //xmlObj.showlista();
    // xmlObj.mostraDados();

    

    return 0;
}