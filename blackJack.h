#include <list>
#include "maquina.h"
#include "cliente.h"

class blackJack : public maquina {
private:
    list<Cliente *>* Jogadores;
public:
    blackJack(int X, int Y);
    ~blackJack();
    string getTipo() override;
    void addCl(Cliente *utl);
};