#include "maquina.h"
#include "cliente.h"

class slots : public maquina {
private:
    Cliente *C;
public:
    slots();
    ~slots();
    string getTipo();
};


