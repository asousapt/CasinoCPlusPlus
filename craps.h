#include <list>
#include "maquina.h"
#include "cliente.h"

class craps : public maquina {
private:
    list<Cliente *>* Jogadores;
public:
    craps(int X, int Y);
    ~craps();
    string getTipo();
    void addCl(Cliente *utl);
    void removeCl();
    void incrementarTemp();
    Cliente* pesquisaCl(int numero);
    int contagemCl();
    list<Cliente *>* getCl();
};