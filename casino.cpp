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
    ClNoCasino = new list<Cliente*>;
    ListaMq = new list<maquina*>;
}

casino::~casino(){
    delete ListaCl;
    delete ClNoCasino;
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

// Entrada de um Cliente no Casino
bool casino::AddUserCasino(Cliente *ut){
    ClNoCasino->push_back(ut);
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

// Desligar uma dada máquina a partir do seu ID
void casino::Desligar(int id_maq){
    for (auto it = ListaMq->begin(); it != ListaMq->end(); ++it){
        maquina *mQ = *it;
        if (mQ->compareId(id_maq) == 1){
            mQ->desligarMq();
        }
    }
}

// Saber o estado de uma dada Máquina a partir do seu ID
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

// Devolver uma lista (ordenada) das maquinas que mais avariáram para a mais fiável
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

// Devolver uma lista (ordenada) das máquinas mais usadas para as menos usadas
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

// Devolver uma lista (ordenada) com os jogadores que passaram mais tempo no casino a jogar
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

// Devolver uma lista (ordenada) dos jogadores que ganharam mais
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

// Enviar um relatório em XML, do estado do Casino; Exporta a informação do estado atual de cada máquina nesse dia
void casino::Relatorio(string fich_xml){

}

// Subir a probabilidade da ganho das maquinas vizinhas de uma determinada distancia 
void casino::SubirProbabilidadeVizinhas(maquina *M_ganhou, float distancia,list<maquina *>* &lmvizinhas){
    int y2,y1 = M_ganhou->getPosY();
    int x2,x1 = M_ganhou->getPosX();

    for (auto it = lmvizinhas->begin(); it != lmvizinhas->end(); ++it){
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

// Mostra todas as máquinas onde a probabilidade de ganhar é superior a X.
void casino::Listar(float prob, ostream &f){
    for (auto it = ListaMq->begin(); it != ListaMq->end(); ++it){
        maquina *mQ = *it;
        float percent = mQ->getPercentGanhar();
        if (percent > prob){
            mQ->exportMQ(f);
        }
    }
}

// Função da simulação com e relogio e operações a fazer, ao clicar na tecla 'M' mostra o menu com várias operações a fazer
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

//Determina o comprimento
void casino::setComprimento(int posX) {
    this->comprimento = posX;
}

//Determina a largura
void casino::setLargura(int posY) {
     this->largura = posY;
}

// Devolve o comprimento
int casino::getComprimento() {
    return this->comprimento;
}

// Devolve a largura
int casino::getLargura() {
     return this->largura;
}

// Procura e devolve uma maquina numa determinada posição
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

// Verifica se utilizador ganhou
void casino::checkGanhou(){
    for (auto it = ListaMq->begin(); it != ListaMq->end(); ++it){
        if ((*it)->ganhou()){
            SubirProbabilidadeVizinhas((*it),1,ListaMq);
        }
    }
}

// Verifica se as maquinas avariáram
void casino::checkAvarias(){
    for (auto it = ListaMq->begin(); it != ListaMq->end(); ++it){
        if ((*it)->avaria()){
            (*it)->removeCl();

            estado e = AVARIADA;
            (*it)->setEstado(e);
        }
    }
}

// Verifica e aumenta a temperatura da máquina
void casino::checkTemp(){
    for (auto it = ListaMq->begin(); it != ListaMq->end(); ++it){
        (*it)->incrementarTemp();
        (*it)->checkTemp();
    }
}

// Devolve uma máquina random
maquina* casino::randomMaquina(){
    Uteis U;
    int icr = 1,valor = U.valorRand(1,ListaMq->size());

    for (auto it = ListaMq->begin(); it != ListaMq->end(); ++it){
        if (icr == valor){
            return (*it);
        }
        icr++;
    }
}

// Associa um utilizador à máquina
void casino::AssociarUsersMaquina(Cliente *utl){
    maquina* MQ;
    estado e;

    while(e != 1){
        MQ = randomMaquina();
        e = Get_Estado(MQ->id);
    }
    MQ->addCl(utl);
}

// Devolve um cliente random
Cliente* casino::randomCl(){
    Uteis U;
    int icr = 1,valor = U.valorRand(1,ListaCl->size());
    
    for (auto it = ListaCl->begin(); it != ListaCl->end(); ++it){
        if (icr == valor){
            return (*it);
        }
        icr++;
    }
    return nullptr;
}

Cliente* casino::getClCasino(int numero){
    for (auto it = ClNoCasino->begin(); it != ClNoCasino->end(); ++it){
        if ((*it)->getNumero() == numero){
            return (*it);
        }
    }
    return nullptr;
}

void casino::AddUsersCasinoBatch(){
    Uteis U;
    Cliente* Cl,*ClTemp;
    
    int valor = U.valorRand(1,10);

    for(int i = 1; i <= valor; i++){
        Cl = randomCl();
        ClTemp = getClCasino(Cl->getNumero());

        while(ClTemp){
            Cl = randomCl();
            ClTemp = getClCasino(Cl->getNumero());
        }
        AddUserCasino(Cl);
    }
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