#include <iostream>
#include <fstream>
#include <map>
#include <ctime>
#include <cstdlib> 
#include "XmlReader.h"
#include "uteis.h"
#include "casino.h"
#include "maquina.h"
#include <unistd.h>
#include <ncurses.h>
#include <termios.h>

using namespace std;

int maquina::nSeq = 0;

int main(){
    Uteis ut = Uteis();
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
    //cas.listarMaquinas();
    //cas.listarClientes();
    cout << "Use a tecla M para parar a simulacao" << endl;
    
    cout << "Pressione M para sair do programa\n";


    while (true) {
        if (ut.TeclaPressionada())
        {
            cout << "Tecla pressionada. Programa encerrado\n";
            break;
        }

        cas.Run(false);

        usleep(10000); // Sleep for 10 milliseconds (requires #include <unistd.h>)
    }

    // Abre o menu do programa

        
  
    
    //cas.exporLlog();
   //cas.ExportCasino();
   
    
    //  cout << xmlObj.temFilhos() << endl ;
    //xmlObj.showlista();
    // xmlObj.mostraDados();

    

    return 0;
}