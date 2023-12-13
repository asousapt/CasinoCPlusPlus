#include <iostream>
#include <sstream>
#include <fstream>
#include <chrono>
#include <random>
#include <cstdlib> 
#include "uteis.h"
#include <unistd.h>
#include <termios.h>
#include <fcntl.h>

// Funcao que carrega ficheiro para string passando apemas o nome do ficheiro
 string Uteis::loadFileToString(string nomeFicheiro) {
    string buffer;
    char c;

    ifstream in(nomeFicheiro );
    if ( !in ) {
        cout << nomeFicheiro << "Ficheiro não encontrado";   
        return "";
    }

    while ( in.get( c ) ) buffer += c;
    in.close();
    return buffer;
}

// Função que pede um valor ao utilizador passando a mensagem
string Uteis::pedeValor(string mensagem) {
    string valor =""; 
    while (valor.length() == 0)
    {
        cout << mensagem << endl;
        cin >> valor;
    }
    return valor;
}

string Uteis::getTimestamp() {
        // Get the current time
        std::time_t currentTime = std::time(nullptr);
        std::tm* localTime = std::localtime(&currentTime);

        // Format the timestamp as a string
        char buffer[20];
        std::strftime(buffer, sizeof(buffer), "%Y-%m-%d %H:%M:%S", localTime);

        return buffer;
    }


 int Uteis::valorRand(int min,int max){
    auto seed = std::chrono::high_resolution_clock::now().time_since_epoch().count();
    std::mt19937 gen(seed);
    std::uniform_int_distribution<int> distribution(min, max);
    return distribution(gen);
}

 string Uteis::retornaStrHoras(int hora, int minutos) {
    string horasTemp = "";
    string minutosTemp = "";
    
    if (hora < 10) {
        horasTemp = "0" + to_string(hora);
    } else {
        horasTemp = to_string(hora);
    }

    if (minutos < 10 ) {
        minutosTemp = "0" + to_string(minutos);
    } else {
        minutosTemp =  to_string(minutos);
    }
    
    return horasTemp + ":" + minutosTemp;
 }

int Uteis::diferencaHoras(time_t horaInicio, time_t horaFim) {
    std::tm *ltm = std::localtime(&horaInicio);
    int horas_Ini = (ltm->tm_hour *60) + ltm->tm_min;
    std::tm *ltm1 = std::localtime(&horaFim);
    int horas_fim = (ltm1->tm_hour *60) + ltm1->tm_min;
    return horas_Ini - horas_fim;
}

bool Uteis::TeclaPressionada() {
    struct termios oldt, newt;
    int ch;

    // Get the current terminal settings
    tcgetattr(STDIN_FILENO, &oldt);

    // Set the terminal to non-canonical mode
    newt = oldt;
    newt.c_lflag &= ~(ICANON | ECHO);
    tcsetattr(STDIN_FILENO, TCSANOW, &newt);

    // Set the file descriptor for standard input to non-blocking
    int flags = fcntl(STDIN_FILENO, F_GETFL, 0);
    fcntl(STDIN_FILENO, F_SETFL, flags | O_NONBLOCK);

    // Check if a key is pressed
    ch = getchar();

    // Restore the terminal settings
    tcsetattr(STDIN_FILENO, TCSANOW, &oldt);

    // Reset the file descriptor for standard input to blocking
    fcntl(STDIN_FILENO, F_SETFL, flags);

    return (ch == 'M' || ch == 'm');
}

bool Uteis::e_numero(const std::string& s){
    bool digito = true;

    auto it = s.begin();
    while (it != s.end()){
        if(!isdigit(*it) && digito == true){
            digito = false;
        }
        ++it;
    } 

    return digito;
}
