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
    int comprimento;
    int largura;
    list<Cliente *>* ListaCl;
    list<Cliente *>* ClNoCasino;
    list<maquina *>* ListaMq;
    bool aberto = 0;
public:
    casino(string _nome);
    ~casino();
    bool Load(const string &ficheiro);
    bool AddUserCasino(Cliente *ut);
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
    void SubirProbabilidadeVizinhas(maquina *M_ganhou, float R,list<maquina *>* &lmvizinhas);
    void Listar(float X, ostream &f = std::cout);
    void Run(bool Debug = true);
    bool VerificarHoras(time_t horas);
    void setComprimento(int posX);
    void setLargura(int posY);
    int getComprimento();
    int getLargura();
    maquina* getMaquinaPorPos(int X, int Y);
    void checkGanhou();
    void checkAvarias();
    void checkTemp();
    maquina* randomMaquina();
    bool AssociarUsersMaquina(Cliente *utl);
    maquina* getMaquinaPorCliente(Cliente *utl);
    Cliente* randomCl();
    Cliente* randomClCasino();
    Cliente* getClCasino(int numero);
    Cliente* getCl(int numero);
    void AddUsersCasinoBatch();
    void AddUsersMaquinaBatch();
    void ApostasUsers();
    bool ExportCasino();
    void VerificaUsersTemSaldo();
    void saidaUsersMaquinas();
    int contagemUsersMaquinas();
    Cliente* randomClMaquina();
    maquina* getMaquina(int cod);
    bool getEstado();
    int contagemClNoCasino();
};

