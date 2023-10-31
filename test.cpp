// Exemplo de como parar um programa em C++ em Linux quando pressionar a tecla M
#include <iostream>
#include <termios.h>
using namespace std;

int main()
{
    cout << "Pressione M para sair do programa\n";
    char c;
    struct termios old, current;

    // Obtém os atributos atuais do terminal
    tcgetattr(0, &old);

    // Copia os atributos para uma nova estrutura
    current = old;

    // Desabilita o modo canônico e o eco
    current.c_lflag &= ~(ICANON | ECHO);

    // Define os novos atributos do terminal
    tcsetattr(0, TCSANOW, &current);

    do
    {
        c = getchar(); // lê uma tecla sem ecoá-la
    } while (c != 'M' && c != 'm'); // repete enquanto não for M ou m

    // Restaura os atributos originais do terminal
    tcsetattr(0, TCSANOW, &old);

    cout << "Programa encerrado\n";
    return 0;
}
