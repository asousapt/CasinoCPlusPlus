#include <list>
#include "maquina.h"
#include "cliente.h"

class craps : public maquina {
private:
    list<Cliente *>* Jogadores;
public:
    craps();
    ~craps();
    string getTipo();
};