#include <list>
#include "maquina.h"
#include "cliente.h"

class blackJack : public maquina {
private:
    list<Cliente *>* Jogadores;
public:
    blackJack();
    ~blackJack();
    string getTipo();
};