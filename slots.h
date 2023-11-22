#include "maquina.h"
#include "cliente.h"

class slots : public maquina {
private:
    Cliente *C;
public:
    slots(int X, int Y);
    ~slots();
    string getTipo();
    void setCl(Cliente *utl);
    void removeCl();
    void incrementarTemp();
    Cliente* pesquisaCl(int numero);
    int contagemCl();
};


