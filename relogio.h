#include <iostream>
#include <ctime>
using namespace std;

class relogio{
private:
    time_t InicioReal; //Hora Inicio do computador 
    int incr; //Incremento do relogio
    time_t InicioSim; //Hora Inicio da Simulacao
public:
    relogio();
    relogio(int salto, time_t hora_abertura);
    ~relogio();
    void verHoraAtual();
    time_t getHoraAtual();
    void WaitSegundos(int s);
    void Wait(int s);
};



