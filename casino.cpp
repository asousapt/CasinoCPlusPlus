#include <iostream>
#include <cmath>
#include <ctime>
#include <sstream>
#include <iomanip>
#include "casino.h"
#include "uteis.h"
#include "relogio.h"
#include "XmlReader.h"
#include "cliente.h"
#include "slots.h"
#include "roleta.h"
#include "craps.h"
#include "blackJack.h"


casino::casino(string _nome){
    nome = _nome;
    ListaCl = new list<Cliente*>;
    ListaMq = new list<maquina*>;
}

casino::~casino(){
    delete ListaCl;
    delete ListaMq;
}

// As configurações do Casino dadas em ficheiro XML, com todas as informações
bool casino::Load(const string &ficheiro){
    Uteis util = Uteis();

    // Carrega o ficheiro XML para dentro de uma string
    string textoXml = util.loadFileToString(ficheiro);

    //Faz a criação de um objecto do tipo XML reader que vai servir para fazer a nossa arvore XML
    XmlReader xmlObj = XmlReader();

    // Faz o parse do ficheiro e coloca os dados da árvore
    xmlObj.parseXML(textoXml, nullptr);
    string horaAbertura = xmlObj.extractDataFromMap("horaAbertura");
    string horafecho = xmlObj.extractDataFromMap("horafecho");
    
    //faz set do tamanho da matriz
    int posX = stoi(xmlObj.extractDataFromMap("posicaoesX"));
    int posY = stoi(xmlObj.extractDataFromMap("posicaoesY"));

    struct tm ts;

    //Parse string para time_t da hora de abertura
    istringstream ha(horaAbertura);
    ha >> get_time(&ts, "%H:%M");
    if (ha.fail()) {
        cerr << "Erro a transformar as horas" << endl;
        return 1; 
    }
    time_t abertura = std::mktime(&ts);

    //Parse string para time_t da hora de fecho
    istringstream hf(horafecho);
    hf >> get_time(&ts, "%H:%M");
    if (hf.fail()) {
        cerr << "Erro a transformar as horas" << endl;
        return 1; 
    }
    time_t fecho = std::mktime(&ts);

    //set as variaveis do casino
    this->hora_abertura = abertura;
    this->hora_fecho = fecho;
    this->comprimento = posX;
    this->largura = posY;
   
    // Vamos carregar o bloco de clientes 
    XmlReader* listaClientes = xmlObj.getNodeBlockByTagName("clienteslista");
    if (listaClientes != nullptr) { 
        list<XmlReader*> filhos = listaClientes->getFilhos();
        if (!filhos.empty()) { 
            for (auto it = filhos.begin(); it != filhos.end(); ++it) {
                XmlReader* temp = (*it);
                Cliente* cl = new Cliente(
                    stoi(temp->extractDataFromMap("numero")), 
                    temp->extractDataFromMap("nome"), 
                    stoi(temp->extractDataFromMap("saldo"))
                    );
                    
                //cl->exportCl();
                if (this->Add(cl) == false) {
                    cout << "Erro ao inserir o cliente " << temp->extractDataFromMap("numero") << " na lista" << endl;
                    return false;
                }
            }
        }
    }

    // Faz o import das maquinas para o objecto casino
    XmlReader* listaMaquinas = xmlObj.getNodeBlockByTagName("maquinasLista");
    if (listaMaquinas != nullptr) {
        list<XmlReader*> filhos = listaMaquinas->getFilhos();
        if (!filhos.empty()) { 
            for (auto it = filhos.begin(); it != filhos.end(); ++it) {
                XmlReader* temp = (*it);
                string tipo = temp->extractDataFromMap("tipo");

                int max,min = this->largura;
                if (min > this->comprimento){
                    min = this->comprimento;
                    max = this->largura;
                }else{
                    max = this->comprimento;
                }
                
                //Loop para encontrar uma posicao vazia
                int X,Y;
                maquina* MQ = 0;
                while(MQ != nullptr) {
                    X = util.valorRand(min,max);
                    Y = util.valorRand(min,max);
                    MQ = getMaquinaPorPos(X,Y);
                }

                if (tipo.compare("SLOTS") == 0) {
                    slots *S = new slots(X,Y);
                    if (this->Add(S) == false ) {
                        cout << "Erro ao inserir maquina" << endl;
                        return false;
                    }
                }else if(tipo.compare("ROLETA") == 0){
                    roleta *R = new roleta(X,Y);
                    if (this->Add(R) == false) {
                        cout << "Erro ao inserir maquina" << endl;
                        return false;
                    }
                }else if(tipo.compare("CRAPS") == 0){
                    craps *C = new craps(X,Y);
                    if (this->Add(C) == false) {
                        cout << "Erro ao inserir maquina" << endl;
                        return false;
                    }
                }else if(tipo.compare("BLACKJACK") == 0){
                    blackJack *B = new blackJack(X,Y);
                    if (this->Add(B)) {
                        cout << "Erro ao inserir maquina" << endl;
                        return false;
                    }
                }
            }
        }
    }
    return true;
}

// Adicionar Clientes à lista de clientes
bool casino::Add(Cliente *ut){
    ListaCl->push_back(ut);
    return true;
}

// Adicionar Máquinas 
bool casino::Add(maquina *m){
    ListaMq->push_back(m);
    return true;
}

// Listar o estado atual do Casino 
void casino::Listar(ostream &f){
    if (aberto){
        f <<"O casino encontra-se aberto!\n";
    }else {
        f << "O casino encontra-se fechado!\n";
    }
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
        if (mQ->compareId(id_maq) == true){
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
list<maquina *>* casino::Listar_Tipo(string Tipo, ostream &f){
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
        string id = to_string(mQ->id);
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
    list<Cliente *>* listaR = ListaCl;
    for (auto it = listaR->begin(); it != listaR->end(); ++it){
        int nJog1 = (*it)->getNJogadas();
        for (auto it2 = it; it2 != listaR->end(); ++it2){
            int nJog2 = (*it2)->getNJogadas();

            if (nJog1 > nJog2){
                swap(*it2,*it);
            }
        }
    }

    return listaR;
}

// Quais os jogadores que mais PRÉMIOS ganharam no casino, deve devolver uma lista (ordenada)
list<Cliente *>* casino::Jogadores_Mais_Ganhos(){
    list<Cliente *>* listaR = ListaCl;
    for (auto it = listaR->begin(); it != listaR->end(); ++it){
        int nVezes1 = (*it)->getNVezesGanhou();
        for (auto it2 = it; it2 != listaR->end(); ++it2){
            int nVezes2 = (*it2)->getNVezesGanhou();

            if (nVezes1 > nVezes2){
                swap(*it2,*it);
            }
        }
    }

    return listaR;
}

// Enviar um relatório em XML, do estado do Casino; O relatório deverá ter a informação do estado atual de cada máquina nesse dia
void casino::Relatorio(string fich_xml){

}

// Quando uma máquina tem um prémio, devem ser aumentada a probabilidade de ganho das outras máquinas
// que estão em redor dela, à distância máxima de R. O método deve devolver (por parâmetro) a lista das
// máquinas onde foi feita a alteração da probabilidade de ganhar
void casino::SubirProbabilidadeVizinhas(maquina *M_ganhou, float distancia,list<maquina *> &lmvizinhas){
    int y2,y1 = M_ganhou->getPosY();
    int x2,x1 = M_ganhou->getPosX();

    for (auto it = lmvizinhas.begin(); it != lmvizinhas.end(); ++it){
        y2 = (*it)->getPosY();
        x2 = (*it)->getPosX();

        float Xs = x2-x1;
        float Ys = y2-y1;
        if (Xs < 0) Xs = Xs * (-1);
        if (Ys < 0) Ys = Ys * (-1);
        Xs = Xs*Xs;
        Ys = Ys*Ys;
        float debaixoRaiz = Xs+Ys;
        float distanciaMaqs = sqrt(debaixoRaiz);
        if (distanciaMaqs <= distancia){
            float percent = (*it)->getPercentGanhar();
            percent = percent+2;
            (*it)->setPercentagemGanhar(percent);

            (*it)->AvisarPercentGanhar();
        }
    }
}

// Listar todas as máquinas onde a probabilidade de ganhar é superior a X.
void casino::Listar(float prob, ostream &f){
    for (auto it = ListaMq->begin(); it != ListaMq->end(); ++it){
        maquina *mQ = *it;
        float percent = mQ->getPercentGanhar();
        if (percent > prob){
            mQ->exportMQ(f);
        }
    }
}

// O Casino tem um método Run, que coloca todo o processo em funcionamento! O Simulador deve estar
// sempre a correr e quando se pretende introduzir alterações, deve-se carregar numa tecla ‘M’ de modo a
// aparecer um menu (nesse instante o simulador deve estar parado, até a opção ser executada!) 
void casino::Run(bool Debug){
    time_t inicio;
    time_t fim;
    if (Debug){
        //Hora inicio do casino
        struct tm *tmp;
        tmp->tm_hour = 9;
        tmp->tm_min = 0;
        inicio = mktime(tmp);
        
        //Hora Fim do casino
        tmp->tm_hour = 14;
        tmp->tm_min = 0;
        fim = mktime(tmp);
    }else{
        inicio = hora_abertura;
        fim = hora_fecho;
    }
    
    //Cria relogio 
    relogio *R = new relogio(120,inicio);
    
    //Cria hora de comparação 
    time_t horaRelogio = R->getHoraAtual();

    bool encerrar = 0;
    while (encerrar == 0) {
        //Conteudo Loop
        bool FazProcessos = VerificarHoras(horaRelogio);

        R->verHoraAtual();
        horaRelogio = R->getHoraAtual();

        R->Wait(2);
    }
}

// Verifica se o casino esta aberto
bool casino::VerificarHoras(time_t horas){
    double diffFecho = difftime(hora_fecho, horas);
    double diffAbrir = difftime(horas,hora_abertura);

    if(diffFecho > 0 && diffAbrir > 0){
        if (diffFecho <= 30){
            cout << "Falta "<<diffFecho<<" minutos para fechar o casino!\n";
        }

        aberto = 1;
        return 1;
    }else if (diffAbrir < 0){
        double diff = diffAbrir*(-1);

        diff = diff/60;
        if (diff <= 30){
            cout << "Falta "<<diff<<" minutos para abrir o casino!\n";
        }

        aberto = 0;
        return 0;
    }else{
        aberto = 0;
        return 0;
    }

}

 void casino::setComprimento(int posX) {
    this->comprimento = posX;
 }

void casino::setLargura(int posY) {
     this->largura = posY;
}

int casino::getComprimento() {
    return this->comprimento;
}

int casino::getLargura() {
     return this->largura;
}

maquina* casino::getMaquinaPorPos(int X, int Y){
    maquina* MQ = nullptr;
    for (auto it = ListaMq->begin(); it != ListaMq->end(); ++it){
        MQ = (*it);
        if (MQ->getPosY() == Y && MQ->getPosX() == X){
            return MQ;
        }
    }
    return MQ;
}

void casino::checkGanhou(){
    for (auto it = ListaMq->begin(); it != ListaMq->end(); ++it){
        if ((*it)->ganhou()){
            //this->SubirProbabilidadeVizinhas((*it),1,ListaMq);
        }
    }
}

void casino::checkAvarias(){
    for (auto it = ListaMq->begin(); it != ListaMq->end(); ++it){
        if ((*it)->avaria()){
            //(*it)->removerUsers();

            estado e = AVARIADA;
            (*it)->setEstado(e);
        }
    }
}

maquina* casino::randomMaquina(){
    Uteis U;
    int icr = 1,valor = U.valorRand(0,ListaMq->size());

    for (auto it = ListaMq->begin(); it != ListaMq->end(); ++it){
        if (icr == valor){
            return (*it);
        }
        icr++;
    }

}

void casino::AssociarUsersMaquina(Cliente *utl){
    maquina* MQ;
    estado e;

    while(e > 0){
        MQ = randomMaquina();
        e = Get_Estado(MQ->id);
    }
    //MQ->addCl();
}

bool casino::ExportCasino() {
    // cria o objecto XML
    XmlReader xmlWR =  XmlReader(this->nome, nullptr);
     std::time_t abertura = this->hora_abertura;
    std::tm * ptm = std::localtime(&abertura);
    char buffer[32];
    // Format: Mo, 15.06.2009 20:20:00
    std::strftime(buffer, 32, "%H:%M", ptm); 
    cout << buffer << endl;
    return true;

}