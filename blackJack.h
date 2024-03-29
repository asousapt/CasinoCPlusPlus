#include <list>
#include "maquina.h"
#include "cliente.h"

class blackJack : public maquina {
private:
    list<Cliente *>* Jogadores;
public:
    blackJack(int X, int Y);
    ~blackJack();
    string getTipo();
    void addCl(Cliente *utl);
    void removeTodosCl();
    void incrementarTemp();
    Cliente* pesquisaCl(int numero);
    int contagemCl();
    list<Cliente *>* getCl();
    void removeCl(Cliente *Cl);
};