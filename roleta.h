#include <list>
#include "maquina.h"
#include "cliente.h"

class roleta : public maquina {
private:
    list<Cliente *>* Jogadores;
public:
    roleta(int X, int Y);
    ~roleta();
    string getTipo();
    void addCl(Cliente *utl);
    void removeCl();
    void incrementarTemp();
    Cliente* pesquisaCl(int numero);
    int contagemCl();
    list<Cliente *>* getCl();
};