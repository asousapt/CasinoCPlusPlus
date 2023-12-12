#include <iostream>
#include <list>
#include "menu.h"

class casino;

using namespace std;


int menuPrincipal(casino *C){
    cout << "---------- MENU PRINCIPAL ---------\n";
    cout << "1 - Utilizadores\n";
    cout << "2 - Máquinas\n";
    cout << "3 - Casino\n";
    cout << "4 - Terminar Simulação\n";
    cout << "0 - Voltar a Simulação\n";

    int op;
    cin >> op;
    while (op != 0) {
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
        system ("clear");
    }
    return 1;
}

void MenuUsers(casino *C){
    cout << "---------- MENU UTILIZADORES ---------\n";
    cout << "1 - Pesquisar e Mostrar Utilizador\n";
    cout << "2 - Utilizadores mais Frequentes\n";
    cout << "3 - Utilizadores com Mais Ganhos\n";
    cout << "0 - Voltar\n";

    int op;
    cin >> op;
    while (op != 0) {
        switch(op){
            case 1:
            {
                bool noCasino = true;
                int numCl = 0;
                
                cout << "Numero Cliente: ";
                cin >> numCl;

                Cliente *Cl = C->getClCasino(numCl);
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
                break;
            }
            case 2:
            {
                list<Cliente *>* LC = C->Jogadores_Mais_Frequentes();

                for (auto it = LC->begin(); it != LC->end(); ++it){
                    (*it)->exportCl();
                }
                break;
            }
            case 3:
            {
                list<Cliente *>* LC = C->Jogadores_Mais_Ganhos();

                for (auto it = LC->begin(); it != LC->end(); ++it){
                    (*it)->exportCl();
                }
                break;
            }
            case 0:
                break;
            default: 
                cout << "Opção Inválida\n";
                break;
        }
        system ("clear");
    }
}

void MenuMaquinas(casino *C){
    cout << "---------- MENU MÁQUINAS ---------\n";
    cout << "1 - Pesquisar e Mostrar Máquina\n";
    cout << "2 - Máquinas mais Usadas\n";
    cout << "3 - Mostrar Máquinas por Tipo\n";
    cout << "4 - Máquinas que Avariaram Mais\n";
    cout << "5 - Mostrar Estado da Máquina\n";
    cout << "6 - Mudar o Estado da Máquina\n";
    cout << "0 - Voltar\n";

    int op;
    cin >> op;
    while (op != 0) {
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

                for (auto it = LM->begin(); it != LM->end(); ++it){
                    (*it)->exportMQ();
                }
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
                        tipo = "slots";
                        break;
                    case 2:
                        tipo = "roleta";
                        break;
                    case 3:
                        tipo = "craps";
                        break;
                    case 4:
                        tipo = "blackjack";
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

                    for (auto it = LM->begin(); it != LM->end(); ++it){
                        (*it)->exportMQ();
                    }
                }
                break;
            }
            case 4:
            {
                list<string>* LMs = C->Ranking_Dos_Fracos();

                for (auto its = LMs->begin(); its != LMs->end(); ++its){
                    string cod = (*its);

                    maquina *MQ = C->getMaquina(stoi(cod));
                    if (MQ){
                        MQ->exportMQ();
                    }
                }
                break;
            }
            case 5:
            {
                int numMq;
                cout << "Numero Máquina: ";
                cin >> numMq;

                maquina *Mq = C->getMaquina(numMq);
                if (Mq){
                    C->Get_Estado(numMq);
                }
                break;
            }
            case 6: 
            {
                estado e;
                int numMq;
                cout << "Numero Máquina: ";
                cin >> numMq;

                maquina *MQ = C->getMaquinaPorID(numMq);

                if (!MQ){
                    cout << "Máquina não existe!\n";
                    break;
                }

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
                    MQ->setEstado(e);
                    delete(MQ);
                }

                break;
            }
            case 0:
                break;
            default: 
                cout << "Opção Inválida\n";
                break;
        }
        system ("clear");
    }
}

void MenuCasino(casino *C){
    cout << "---------- MENU CASINO ---------\n";
    cout << "1 - Exportar\n";
    cout << "2 - Saber Estado\n";
    cout << "3 - Contagem de Jogadores no Casino\n";
    cout << "0 - Voltar\n";

    int op;
    cin >> op;
    while (op != 0) {
        switch(op){
            case 1:
                C->ExportCasino();
            case 2:
                C->Listar();
                break;
            case 3:
                cout << "O casino tem " << C->contagemClNoCasino() << " jogadores presentes.\n";
                break;            
            case 0:
                break;
            default: 
                cout << "Opção Inválida\n";
                break;
        }
        system ("clear");
    }
}
