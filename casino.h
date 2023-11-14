#include <iostream>
#include <list>
#include <ctime>
#include "cliente.h"
#include "maquina.h"
using namespace std;

class casino{
private:
    string nome;
    time_t hora_abertura;
    time_t hora_fecho;
    list<Cliente *>* ListaCl;
    list<maquina *>* ListaMq;
public:
    casino(string _nome);
    ~casino();
    bool Load(const string &ficheiro);
    bool Add(Cliente *ut);
    bool Add(maquina *m);
    void Listar(ostream &f = std::cout);
    void Desligar(int id_maq);
    estado Get_Estado(int id_maq);
    int Memoria_Total();
    list<maquina *>* Listar_Tipo(string Tipo, ostream &f = std::cout);
    list<string>* Ranking_Dos_Fracos();
    list<maquina *>* Ranking_Das_Mais_Trabalhadores();
    list<Cliente *>* Jogadores_Mais_Frequentes();
    list<Cliente *>* Jogadores_Mais_Ganhos();
    void Relatorio(string fich_xml);
    void SubirProbabilidadeVizinhas(maquina *M_ganhou, float R,list<maquina *> &lmvizinhas);
    void Listar(float X, ostream &f = std::cout);
    void Run(bool Debug = true);
};

