#include <iostream>
#include "casino.h"

casino::casino(string _nome){
    nome = _nome;
}

casino::~casino(){
    
}

// As configurações do Casino dadas em ficheiro XML, com todas as informações
bool casino::Load(const string &ficheiro){

}

// Adicionar Utilizadores
bool casino::Add(Cliente *ut){
    ListaCl->push_back(ut);
}

// Adicionar Máquina 
bool casino::Add(maquina *m){
    ListaMq->push_back(m);
}

// Listar o estado atual do Casino 
void casino::Listar(ostream &f = std::cout){

}

// Desligar uma dada máquina, dado o seu ID
void casino::Desligar(int id_maq){
    for (auto it = ListaMq->begin(); it != ListaMq->end(); ++it){
        maquina *mQ = *it;
        if (mQ->compareId(id_maq) == 1){
            mQ->desligarMq();
        }
    }
}

// Saber o estado de uma dada Máquina, dado o seu ID
estado casino::Get_Estado(int id_maq){
    estado e;
    for (auto it = ListaMq->begin(); it != ListaMq->end(); ++it){
        maquina *mQ = *it;
        if (mQ->compareId(id_maq) == 1){
            e = mQ->getEstado();
            break;
        }
    }

    return e;
}

// Calcular a memória total ocupada pela estrutura de dados
int casino::Memoria_Total(){
    return sizeof(this);
}

// Listar e devolver todas as máquinas de um dado Tipo
list<maquina *>* casino::Listar_Tipo(string Tipo, ostream &f = std::cout){
    list<maquina *>* listaR;
    for (auto it = ListaMq->begin(); it != ListaMq->end(); ++it){
        maquina *mQ = *it;
        string mqTipo = mQ->getTipo();
        if (mqTipo.compare(Tipo) == 1){
            listaR->push_back(mQ);
            mQ->exportMQ(f);
        }
    }

    return listaR;
}

// Quais as Maquinas que mais avariam, deve devolver uma lista (ordenada) da que mais avaria para a mais fiável
list<string>* casino::Ranking_Dos_Fracos(){
    list<string>* listaR;
    for (auto it = ListaMq->begin(); it != ListaMq->end(); ++it){
        maquina *mQ = *it;
        string id = to_string(mQ->getID());
        listaR->push_back(id);
    }
    
    for (auto it = listaR->begin(); it != listaR->end(); ++it){
        string idIT = *it;
        int id1 = stoi(idIT);
        for (auto it2 = it; it2 != listaR->end(); ++it2){
            string idIT2 = *it2;
            int id2 = stoi(idIT2);
            if (id1 < id2){
                swap(*it2,*it);
            }
        }
    }

    return listaR;
}

// Quais máquinas mais usadas (que mais trabalham), deve devolver uma lista (ordenada)
list<maquina *>* casino::Ranking_Das_Mais_Trabalhadores(){
    list<maquina *>* listaR = ListaMq;
    for (auto it = listaR->begin(); it != listaR->end(); ++it){
        maquina *mQ1 = *it;
        for (auto it2 = it; it2 != listaR->end(); ++it2){
            maquina *mQ2 = *it2;
            if (mQ1->compareNUsos(mQ2) > 0){
                swap(*it2,*it);
            }
        }
    }

    return listaR;
}

// Quais os jogadores que mais TEMPO passaram no casino a jogar, deve devolver uma lista (ordenada)
list<Cliente *>* casino::Jogadores_Mais_Frequentes(){

}

// Quais os jogadores que mais PRÉMIOS ganharam no casino, deve devolver uma lista (ordenada)
list<Cliente *>* casino::Jogadores_Mais_Ganhos(){
    
}

// Enviar um relatório em XML, do estado do Casino; O relatório deverá ter a informação do estado atual de cada máquina nesse dia
void casino::Relatorio(string fich_xml){

}

// Quando uma máquina tem um prémio, devem ser aumentada a probabilidade de ganho das outras máquinas
// que estão em redor dela, à distância máxima de R. O método deve devolver (por parâmetro) a lista das
// máquinas onde foi feita a alteração da probabilidade de ganhar
void casino::SubirProbabilidadeVizinhas(maquina *M_ganhou, float R,list<maquina *> &lmvizinhas){
    
}

// Listar todas as máquinas onde a probabilidade de ganhar é superior a X.
void casino::Listar(float X, ostream &f = std::cout){
    for (auto it = ListaMq.begin(); it != ListaMq.end(); ++it){
        maquina *mQ = *it;
        float percent = mQ->getPercentGanhar();
        if (percent > X){
            mQ->exportMQ(f);
        }
    }
}

// O Casino tem um método Run, que coloca todo o processo em funcionamento! O Simulador deve estar
// sempre a correr e quando se pretende introduzir alterações, deve-se carregar numa tecla ‘M’ de modo a
// aparecer um menu (nesse instante o simulador deve estar parado, até a opção ser executada!) 
void casino::Run(bool Debug = true){

}
