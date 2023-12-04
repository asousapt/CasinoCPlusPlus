#include <iostream>
#include "casino.h"

void menuPrincipal(casino *C){
    cout << "---------- MENU PRINCIPAL ---------\n";
    cout << "1 - Utilizadores\n";
    cout << "2 - Máquinas\n";
    cout << "3 - Casino\n";
    cout << "0 - Terminar Simulação\n";

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
            case 0:
                break;
            default: 
                cout << "Opção Inválida\n";
                break;
        }
        system ("clear");
    }
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
            
            case 2:
            
            case 3:
                
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
    cout << "1 - Utilizadores\n";
    cout << "2 - Máquinas\n";
    cout << "3 - Casino\n";
    cout << "0 - Voltar\n";

    int op;
    cin >> op;
    while (op != 0) {
        switch(op){
            case 1:
            
            case 2:
            
            case 3:
            
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
    cout << "---------- MENU PRINCIPAL ---------\n";
    cout << "1 - Utilizadores\n";
    cout << "2 - Máquinas\n";
    cout << "3 - Casino\n";
    cout << "0 - Terminar Simulação\n";

    int op;
    cin >> op;
    while (op != 0) {
        switch(op){
            case 1:
            
            case 2:
            
            case 3:
            
            case 0:
                break;
            default: 
                cout << "Opção Inválida\n";
                break;
        }
        system ("clear");
    }
}
