#include <iostream>
#include <list>
#include <unistd.h>
#include "menu.h"

class casino;

using namespace std;

int menuPrincipal(casino *C){
    int op = -1;
    while (op != 0) {

        system("clear");
        cout << "\n---------- MENU PRINCIPAL ---------\n";
        cout << "1 - Utilizadores\n";
        cout << "2 - Máquinas\n";
        cout << "3 - Casino\n";
        cout << "4 - Terminar Simulação\n";
        cout << "0 - Voltar a Simulação\n";
        cin >> op;
        cin.clear();
        system("clear");

        switch(op){
            case 1:
                MenuUsers(C);
                break;
            case 2:
                MenuMaquinas(C);
                break;
            case 3:
                MenuCasino(C);
                break;
            case 4:
                return 0;
                break;
            case 0:
                break;
            default: 
                cout << "Opção Inválida\n";
                break;
        }
    }
    return 1;
}

void MenuUsers(casino *C){
    int op = -1;
    while (op != 0) {

        cout << "\n---------- MENU UTILIZADORES ---------\n";
        cout << "1 - Pesquisar e Mostrar Utilizador\n";
        cout << "2 - Utilizadores mais Frequentes\n";
        cout << "3 - Utilizadores com Mais Ganhos\n";
        cout << "0 - Voltar\n";
        cin >> op;
        cin.clear();
        system ("clear");

        switch(op){
            case 1:
            {
                bool noCasino = false;
                int numCl = 0;
            
                cout << "Numero Cliente: ";
                cin >> numCl;
                Cliente* Cl = C->getCl(numCl);
                if (!Cl){
                    cout << "Cliente não existe\n";
                }else{
                    Cl = C->getClCasino(numCl);
                    if (!Cl){
                        noCasino = false;
                        Cl = C->getCl(numCl);
                    }

                    Cl->exportCl();
                    if (noCasino){
                        cout << "Encontra no casino no máquina:\n";
                        maquina *MQ = C->getMaquinaPorCliente(Cl);
                        MQ->exportMQ();

                    }else{
                        cout << "Não se encontra no casino\n";
                    }

                    cout << "Ganhou " << Cl->getNVezesGanhou() << " vezes\n";
                    cout << "Jogou " << Cl->getNJogadas() << " vezes\n";
                    cout << "Saldo: " << Cl->getSaldo() << " €. Com " << Cl->getApostaPendente() << " numa aposta.\n";
                }
                
                break;
            }
            case 2:
            {
                list<Cliente *>* LC = C->Jogadores_Mais_Frequentes();
                system("clear");
                cout << "### UTILIZADORES MAIS FREQUENTES ###" << endl;

                for (auto it = LC->begin(); it != LC->end(); ++it){
                    (*it)->exportCl();
                }
                cout << "### UTILIZADORES MAIS FREQUENTES ###\n" << endl;
                break;
            }
            case 3:
            {
                list<Cliente *>* LC = C->Jogadores_Mais_Ganhos();
                system("clear");

                cout << "### UTILIZADORES MAIS GANHADORES ###" << endl;
                for (auto it = LC->begin(); it != LC->end(); ++it){
                    (*it)->exportCl();
                }
                cout << "### UTILIZADORES MAIS GANHADORES ###\n" << endl;
                break;
            }
            case 0:
                break;
            default: 
                cout << "Opção Inválida\n";
                break;
        }
        //system ("clear");
    }
}

void MenuMaquinas(casino *C){
    int op = -1;
    while (op != 0) {
        cout << "\n---------- MENU MÁQUINAS ---------\n";
        cout << "1 - Pesquisar e Mostrar Máquina\n";
        cout << "2 - Máquinas mais Usadas\n";
        cout << "3 - Mostrar Máquinas por Tipo\n";
        cout << "4 - Máquinas que Avariaram Mais\n";
        cout << "5 - Mostrar Estado da Máquina\n";
        cout << "6 - Mudar o Estado da Máquina\n";
        cout << "0 - Voltar\n";
        cin >> op;
        cin.clear();
        system ("clear");

        switch(op){
            case 1:
            {
                int numMq;
                cout << "Numero Máquina: ";
                cin >> numMq;
                
                maquina *Mq = C->getMaquina(numMq);
                if (Mq){
                    Mq->exportMQ();
                }

                break;
            }
            case 2:
            {
                list<maquina *>* LM = C->Ranking_Das_Mais_Trabalhadores();

                cout << "### MAQUINAS MAIS UTILIZADAS ###" << endl;
                for (auto it = LM->begin(); it != LM->end(); ++it){
                    (*it)->exportMQ();
                }
                cout << "### MAQUINAS MAIS UTILIZADAS ###\n" << endl;
                break;
            }
            case 3:
            {
                string tipo;
                int op2 = 0;
                cout << "---------- TIPO ---------\n";
                cout << "1 - SLOTS\n";
                cout << "2 - ROLETA\n";
                cout << "3 - CRAPS\n";
                cout << "4 - BLACKJACK\n";
                cout << "0 - Voltar\n";
                cin >> op2;
                switch (op2){
                    case 1:
                        tipo = "SLOTS";
                        break;
                    case 2:
                        tipo = "ROLETA";
                        break;
                    case 3:
                        tipo = "CRAPS";
                        break;
                    case 4:
                        tipo = "BLACKJACK";
                        break;
                    case 0:
                        break;
                    default:
                        op2 = 0;
                        cout << "Tipo Inválido\n";
                        break;
                }

                if (op2 > 0){
                    list<maquina *>* LM = C->Listar_Tipo(tipo);
                }
                break;
            }
            case 4:
            {
                list<string>* LMs = C->Ranking_Dos_Fracos();
                break;
            }
            case 5:
            {
                int numMq;
                cout << "Numero Máquina: ";
                cin >> numMq;

                maquina *Mq = C->getMaquina(numMq);
                if (Mq){
                    estado e = C->Get_Estado(numMq);
                    cout << "Estado da maquina ["<<numMq<<"]: ";
                    switch(e){
                        case 1:
                            cout << "ON\n";
                            break;
                        case 0:
                            cout << "OFF\n";
                            break;
                        case 2:
                            cout << "AVARIADA\n";
                            break;
                    }
                }else{
                    cout << "Maquina não existe\n";
                }
                break;
            }
            case 6: 
            {
                estado e;
                int numMq;
                cout << "Numero Máquina: ";
                cin >> numMq;

                int op2 = 0;
                cout << "---------- ESTADOS ---------\n";
                cout << "1 - ON\n";
                cout << "2 - OFF\n";
                cout << "3 - AVARIADO\n";
                cout << "0 - Voltar\n";
                cin >> op2;
                switch (op2){
                    case 1:
                        e = ON;
                        break;
                    case 2:
                        e = OFF;
                        break;
                    case 3:
                        e = AVARIADA;
                        break;
                    case 0:
                        break;
                    default:
                        op2 = 0;
                        cout << "Estado Inválido\n";
                        break;
                }

                if (op2 > 0){
                    C->alterarEstadoMaquina(numMq,e);
                }

                break;
            }
            case 0:
                break;
            default: 
                cout << "Opção Inválida\n";
                break;
        }
        //system ("clear");
    }
}

void MenuCasino(casino *C){
    int op = -1;
    while (op != 0) {
        cout << "\n---------- MENU CASINO ---------\n";
        cout << "1 - Exportar\n";
        cout << "2 - Saber Estado\n";
        cout << "3 - Contagem de Jogadores no Casino\n";
        cout << "4 - Tamanho do Casino\n";
        cout << "0 - Voltar\n";
        cin >> op;
        cin.clear();
        system ("clear");

        switch(op){
            case 1:
                C->ExportCasino();
            case 2:
                C->Listar();
                break;
            case 3:
                cout << "O casino tem " << C->contagemClNoCasino() << " jogadores presentes.\n";
                break; 
            case 4:
                cout << "O tamanho: " << C->Memoria_Total() << ".\n";
                break;     
            case 0:
                break;
            default: 
                cout << "Opção Inválida\n";
                break;
        }
       //system ("clear");
    }
}
