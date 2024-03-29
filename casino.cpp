#include <iostream>
#include <cmath>
#include <ctime>
#include <sstream>
#include <string>
#include <chrono>
#include <thread>
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
#include <unistd.h>
#include <termios.h>
#include "menu.h"


casino::casino(string _nome){
    nome = _nome;
    ListaCl = new list<Cliente*>;
    ClNoCasino = new list<Cliente*>;
    ListaMq = new list<maquina*>; 
    XmlLog = new XmlReader("Log", nullptr);
    XmlReader * xml = new XmlReader("logdata", "Casino " + _nome + " criado com sucesso", XmlLog);
    XmlLog->addFilho(xml);
}

casino::~casino(){
    delete ListaCl;
    delete ClNoCasino;
    delete ListaMq;
    delete XmlLog;
}

// As configurações do Casino dadas em ficheiro XML, com todas as informações
bool casino::Load(const string &ficheiro){
    Uteis util = Uteis();
    
    XmlReader * xml = new XmlReader("logdata", "Load do ficheiro " + ficheiro + " no casino", XmlLog);
    XmlLog->addFilho(xml);

    // Carrega o ficheiro XML para dentro de uma string
    string textoXml = util.loadFileToString(ficheiro);

    //Faz a criação de um objecto do tipo XML reader que vai servir para fazer a nossa arvore XML
    XmlReader xmlObj = XmlReader();

    // Faz o parse do ficheiro e coloca os dados da árvore
    xmlObj.parseXML(textoXml, nullptr);
    string horaAbertura = xmlObj.extractDataFromMap("horaAbertura");
  
    string horafecho = xmlObj.extractDataFromMap("horafecho");
    int primeiroInicio = stoi(xmlObj.extractDataFromMap("primeiroInicio"));
    
    //faz set do tamanho da matriz
    int posX = stoi(xmlObj.extractDataFromMap("posicaoesX"));
    int posY = stoi(xmlObj.extractDataFromMap("posicaoesY"));

    std::tm ts = {};

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
               
                int min = 0;
                int max_comprimento = this->comprimento;
                int max_largura = this->largura;
                
                //Loop para encontrar uma posicao vazia
                int X,Y;
                
                if (primeiroInicio == 1) {
                    maquina* MQ = nullptr;
                    do { 
                        X = util.valorRand(min,max_comprimento);
                        Y = util.valorRand(min,max_largura);
                        MQ = getMaquinaPorPos(X,Y);
                    } while(MQ != nullptr);
                }
                else {
                    X = stoi(temp->extractDataFromMap("posX"));
                    Y = stoi(temp->extractDataFromMap("posY"));
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
                    if (this->Add(B) == false) {
                        cout << "Erro ao inserir maquina" << endl;
                        return false;
                    }
                }
            }
        }
    }

    XmlReader * xmlf = new XmlReader("logdata", "Importacao termninada com sucesso!", XmlLog);
    XmlLog->addFilho(xmlf);
    return true;
}

// Entrada de um Cliente no Casino
bool casino::AddUserCasino(Cliente *ut){
    ClNoCasino->push_back(ut);
    // faz log
    string mensagem = "O cliente " + to_string(ut->getNumero()) + " deu entrada no casino";
    XmlReader * xml = new XmlReader("logdata", mensagem, XmlLog);
    XmlLog->addFilho(xml);

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
            string mensagem = "A maquina com do tipo " + mQ->getTipo() + " na posicao " + to_string(mQ->getPosX()) + "," + to_string(mQ->getPosY()) + " foi desligada";
            XmlReader * xml = new XmlReader("logdata", mensagem, XmlLog);
            XmlLog->addFilho(xml);
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

// Mostrar e devolver todas as máquinas de um dado Tipo
list<maquina *>* casino::Listar_Tipo(string Tipo, ostream &f){
    list<maquina *>* listaR = new list<maquina*>;
    for (auto it = ListaMq->begin(); it != ListaMq->end(); ++it){
        maquina *mQ = (*it);
        string mqTipo = mQ->getTipo();

        if (mqTipo.compare(Tipo) == 0){
            listaR->push_back(mQ);
            mQ->exportMQ(f);
        }
    }

    list<maquina *>* listaR2 = listaR;
    delete(listaR);

    return listaR2;
}

// Devolver uma lista (ordenada) das maquinas que mais avariáram para a mais fiável
list<string>* casino::Ranking_Dos_Fracos(){
    list<maquina *>* listaMaq = ListaMq;
    for (auto it = listaMaq->begin(); it != listaMaq->end(); ++it){
        int nAva1 = (*it)->getNAvarias();
        for (auto it2 = it; it2 != listaMaq->end(); ++it2){
            int nAva2 = (*it2)->getNAvarias();

            if (nAva1 > nAva2){
                swap(*it2,*it);
            }
        }
    }

    list<string>* listaR = new list<string>;
    for (auto it3 = listaMaq->begin(); it3 != listaMaq->end(); ++it3){
        int ID = (*it3)->getID();
        listaR->push_back(to_string(ID));
        (*it3)->exportMQ();
    }
    
    list<string>* listaR2 = listaR;
    delete(listaR);

    return listaR2;
}

// Devolver uma lista (ordenada) das máquinas mais usadas para as menos usadas
list<maquina *>* casino::Ranking_Das_Mais_Trabalhadores(){
    list<maquina *>* listaR = ListaMq;
    for (auto it = listaR->begin(); it != listaR->end(); ++it){
        for (auto it2 = it; it2 != listaR->end(); ++it2){
            if ((*it2)->compareNUsos((*it)) > 0){
                swap(*it2,*it);
            }
        }
    }

    for (auto it3 = listaR->begin(); it3 != listaR->end(); ++it3){
        (*it3)->exportMQ();
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
        cout << "teste3\n";

    for (auto it3 = listaR->begin(); it3 != listaR->end(); ++it3){
        (*it3)->exportCl();
    }
    
    return listaR;
}

// Devolver uma lista (ordenada) dos jogadores que ganharam mais
list<Cliente *>* casino::Jogadores_Mais_Ganhos(){
    list<Cliente *>* listaR = ListaCl;
    for (auto it = listaR->begin(); it != listaR->end(); ++it){
        float saldo1 = (*it)->getSaldo();
        for (auto it2 = it; it2 != listaR->end(); ++it2){
            float saldo2 = (*it2)->getSaldo();

            if (saldo1 > saldo2){
                swap(*it2,*it);
            }
        }
    }

    for (auto it3 = listaR->begin(); it3 != listaR->end(); ++it3){
        (*it3)->exportCl();
    }
    
    return listaR;
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

            string mensagem = "A maquina " + (*it)->getTipo() + " na posicao " + to_string((*it)->getPosX()) + "," + to_string((*it)->getPosY()) + " foi incrementada a percentagem para " + to_string(percent);
            XmlReader * xml = new XmlReader("logdata", mensagem, XmlLog);
            XmlLog->addFilho(xml);

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
    Uteis ut = Uteis();
    cout << endl<< "Use a tecla M para parar a simulacao..." << endl;  
    relogio accelerated_clock(900);
    bool FazProcessos = false;
    int fechar = 1;
    
    do
    {
        auto accelerated_time = accelerated_clock.now();
        auto timeStruct = std::chrono::system_clock::to_time_t(accelerated_time);
        auto localTimeStruct = *std::localtime(&timeStruct);

        // Faz a verificacao da hora atual e decide o que fazer 
        if (verificaHoras(localTimeStruct)) {
            // o casino esta aberto
            FazProcessos = true;
            this->aberto = true;
            //std::cout << "Casino Aberto!\n";
        } else {
            //o casino esta fechado 
            FazProcessos = false;
            this->aberto = false;
            //std::cout << "Casino Fechado.\n";
        }

        // trata dos processos do casino 
        if (FazProcessos == true){
            //Adiciona utilizadores ao casino
            AddUsersCasinoBatch();
           //Adiciona utilizadores as maquinas do casino            
            AddUsersMaquinaBatch();
            //cout << "Adicionei users as maquinas \n";
            //listaJogagoresMaquinas();
            ApostasUsers();
            //cout << "fIZERAM APOSTAS \n";
            checkGanhou();
            //cout << "VERIFICOU GANHOS \n";
            checkAvarias();
            checkTemp();
            //cout << "SAIDA" << endl;
            saidaUsersMaquinas();
            saidaUersCasino();
        }else {
            // Tem de excluir toda a gente do casino
            // Tem de verificar se ha pessoas que ganharam apostas, atualizar os saldos

            checkGanhou();
            removerClientesMaquinas();
            removerClientesCasino();
        }
        std::cout << "Hora Atual: " << std::asctime(&localTimeStruct);
        cout << "Estao " << ClNoCasino->size() << " jogadores no casino\n";
        Listar();
        cout << endl;

        // Sleep de 2 segundos 
        std::this_thread::sleep_for(std::chrono::seconds(2));

        if (ut.TeclaPressionada()){
            fechar = menuPrincipal(this);
        }

        //usleep(10000); // Sleep for 10 milliseconds (requires #include <unistd.h>)

    } while (fechar == 1);    
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
    maquina* MQ ;
    
    for (auto it = this->ListaMq->begin(); it != this->ListaMq->end(); ++it){
        MQ = (*it);
        if (MQ->getPosY() == Y && MQ->getPosX() == X){
            return MQ;
        }
    }
    
    return nullptr;
}

// Verifica se utilizador ganhou
void casino::checkGanhou(){
    for (auto it = ListaMq->begin(); it != ListaMq->end(); ++it){
        if ((*it)->getEstado() == ON){
            list<Cliente *>* Lista = (*it)->getCl();
            
            for (auto it2 = Lista->begin(); it2 != Lista->end(); ++it2){
                if ((*it)->ganhou()){
                    float aposta = (*it2)->getApostaPendente();
                    aposta = aposta *2;
                    (*it2)->incrSaldo(aposta);
                    (*it2)->setApostaPendente(0);

                    SubirProbabilidadeVizinhas((*it),1,ListaMq);
                }else{
                    (*it2)->setApostaPendente(0);
                }
            }
        }
    }
}

// Verifica se as maquinas avariáram
void casino::checkAvarias(){
    for (auto it = ListaMq->begin(); it != ListaMq->end(); ++it){
        if ((*it)->getEstado() == ON){
            if ((*it)->avaria()){
                (*it)->removeTodosCl();

                estado e = AVARIADA;
                (*it)->setEstado(e);
            } else {
                estado estadoAct = (*it)->getEstado();
                if (estadoAct == AVARIADA) {
                    estado e = ON;
                    (*it)->setEstado(e);
                }
            }
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
    return nullptr;
}

// Associa um utilizador à máquina
bool casino::AssociarUsersMaquina(Cliente *utl){
    
    maquina* MQ = nullptr;
    estado e;
    do
    {
        MQ = maquinaLivre();
        if (!MQ) break;
        if (MQ->getTipo().compare("BLACKJACK") != 0 && MQ->contagemCl() < 5){
            e = Get_Estado(MQ->getID());
        }else{
            e = OFF;
        }
    } while (MQ == nullptr);
    
    //estado e;
    // while(e != 1){
    //     MQ = randomMaquina();
      
    // }
    
    if(MQ){
        MQ->addCl(utl);
        string mensagem = "O cliente " + to_string(utl->getNumero()) + " na maquina " + MQ->getTipo() + " na posicao " + to_string(MQ->getPosX()) + "," + to_string(MQ->getPosY());
        XmlReader * xml = new XmlReader("logdata", mensagem, XmlLog);
        XmlLog->addFilho(xml);
        return true;
    }else{
        return false;
    }
}

// Devolve a maquina onde o cliente esta a jogar
maquina* casino::getMaquinaPorCliente(Cliente *utl){
    maquina* MQ;
    for (auto it = ListaMq->begin(); it != ListaMq->end(); ++it){
        MQ = (*it);
        if(MQ->pesquisaCl(utl->getNumero()) != nullptr){
            return (*it);
        }
    }
    
    return nullptr;
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

Cliente* casino::randomClCasino(){
    Uteis U = Uteis();
    
       int icr = 1,valor = U.valorRand(1,ClNoCasino->size());
    
        for (auto it = ClNoCasino->begin(); it != ClNoCasino->end(); ++it){
            if (icr == valor){
                return (*it);
            }
            icr++;
        }
  
    return nullptr;
}

// Pesquisa e devolve um cliente no casino pelo numero
Cliente* casino::getClCasino(int numero){
    for (auto it = ClNoCasino->begin(); it != ClNoCasino->end(); ++it){
        if ((*it)->getNumero() == numero){
            return (*it);
        }
    }
    return nullptr;
}

// Pesquisa e devolve um cliente pelo numero
Cliente* casino::getCl(int numero){
    for (auto it = ListaCl->begin(); it != ListaCl->end(); ++it){
        if ((*it)->getNumero() == numero){
            return (*it);
        }
    }
    return nullptr;
}

// Adiciona vários clientes ao casino
void casino::AddUsersCasinoBatch(){
    Uteis U = Uteis();
    Cliente* Cl,*ClTemp;
    
    int numeroClientesTotal = ListaCl->size();
    int numeroClientesNoCasino = ClNoCasino->size();
    int valorMaximoAleatorio = numeroClientesTotal - numeroClientesNoCasino;

    int valor = U.valorRand(0, valorMaximoAleatorio);
    
    if (valor > 0) {
        for(int i = 1; i <= valor; i++){

          do
          {
            Cl = randomCl();
            if (!Cl) break;
            ClTemp = getClCasino(Cl->getNumero());
          } while (ClTemp != nullptr);
                      
            if (!Cl) break;
            AddUserCasino(Cl);
            // LOG
            string mensagem = "O cliente " + to_string(Cl->getNumero()) + " foi adicionado ao casino";
            XmlReader * xml = new XmlReader("logdata", mensagem, XmlLog);
            XmlLog->addFilho(xml);
        }
    }
}

// Adiciona vários clientes às maquinas
void casino::AddUsersMaquinaBatch(){
    Uteis U = Uteis();
    Cliente* Cl = nullptr;
    int valor = U.valorRand(0, this->nmrMaquinasActivas());
    
    if(ClNoCasino->size() < valor ) {
        valor = ClNoCasino->size();
    }
    //cout << ClNoCasino->size() << " Numero a associar de clientes as maquinas " << valor << endl;
    for(int i = 1; i <= valor; i++){
        do
        {
            Cl = clienteCasinoSemMaquina();
        } while (Cl == nullptr);
        //cout << "CLIENTE"<< Cl->getNome()<< endl;
        if(Cl){
            AssociarUsersMaquina(Cl);
        }
    }
}

// Faz as apostas dos Clientes nas maquinas
void casino::ApostasUsers(){
    for (auto it = ListaMq->begin(); it != ListaMq->end(); ++it){
        //cout << (*it)->getTipo()<< " || " << (*it)->getPosX() << ","<< (*it)->getPosY() << endl;
        if ((*it)->getEstado() == ON){
            list<Cliente *>* Lista = (*it)->getCl();
            
            for (auto it2 = Lista->begin(); it2 != Lista->end(); ++it2){
                (*it)->incrVezesJogadas();
                
                float aposta = (*it2)->percentSaldo();
                //cout << "cliente " << (*it2)->getNumero() << " SALDO: " << (*it2)->getSaldo() << " APOSTA " << aposta << endl;
                (*it2)->setApostaPendente(aposta);
                aposta = aposta * (-1);
                (*it2)->incrSaldo(aposta);
                (*it2)->incrJogadas();
            }
        }
    }
}

bool casino::ExportCasino() {
    string mensagem = "A iniciar exportacao dos dados do casinos";
    XmlReader * xml = new XmlReader("logdata", mensagem, XmlLog);
    XmlLog->addFilho(xml);

    Uteis ut = Uteis();
    // cria o objecto XML
    XmlReader xmlWR =  XmlReader("casino", nullptr);
    // Vai buscar a hora de abertura
    std::time_t abertura = this->hora_abertura;
    std::tm *ltm = std::localtime(&abertura);
    string hora_abertura = ut.retornaStrHoras(ltm->tm_hour, ltm->tm_min);
   
   // vai buscar a hora de fecho 
    std::time_t fecho = this->hora_fecho;
    ltm = std::localtime(&fecho);
    string hora_fecho = ut.retornaStrHoras(ltm->tm_hour, ltm->tm_min);

    xmlWR.adicionarDados("nome", this->nome, &xmlWR);
    xmlWR.adicionarDados("horaAbertura", hora_abertura, &xmlWR);
    xmlWR.adicionarDados("horafecho", hora_fecho, &xmlWR);
    xmlWR.adicionarDados("posicaoesX", to_string(this->comprimento), &xmlWR);
    xmlWR.adicionarDados("posicaoesY", to_string(this->largura), &xmlWR);
    xmlWR.adicionarDados("primeiroInicio", "0", &xmlWR);
    
    //Gera o no da lista de clientes
    XmlReader * filloClientes = new XmlReader("clienteslista", &xmlWR);
    xmlWR.addFilho(filloClientes);

    list<Cliente *> * lc = this->ListaCl;

    for (auto it = lc->begin(); it != lc->end(); ++it){
        Cliente * cl = (*it);
        XmlReader * objCl = new XmlReader("cliente", filloClientes);
        objCl->adicionarDados("numero", to_string(cl->getNumero()), objCl);
        objCl->adicionarDados("nome", cl->getNome(), objCl);
        objCl->adicionarDados("saldo", to_string(cl->getSaldo()), objCl);
        filloClientes->addFilho(objCl);
    }

    XmlReader * filloMaquinas = new XmlReader("maquinasLista", &xmlWR);
    xmlWR.addFilho(filloMaquinas);
    
    list<maquina *> * lm = this->ListaMq;
    for (auto it = lm->begin(); it != lm->end(); ++it){
        maquina * mq = (*it);
        XmlReader * objmq = new XmlReader("maquina", filloMaquinas);
        objmq->adicionarDados("tipo", mq->getTipo(), objmq);
        objmq->adicionarDados("posX", to_string(mq->getPosX()), objmq);
        objmq->adicionarDados("posY", to_string(mq->getPosY()), objmq);
        objmq->adicionarDados("percentAvaria", to_string(mq->getPercentAvaria()), objmq);
        objmq->adicionarDados("percentGanhar", to_string(mq->getPercentGanhar()), objmq);
        objmq->adicionarDados("temperaturaMax", to_string(mq->getTemperaturaMax()), objmq);
        objmq->adicionarDados("percentagemAviso", to_string(mq->getPercentagemAviso()), objmq);
        filloMaquinas->addFilho(objmq);
    }
    xmlWR.saveAsXML("casino2.xml");
    string mensagem2 = "Exportacao do casino feita com sucesso";
    XmlReader * xml2 = new XmlReader("logdata", mensagem, XmlLog);
    XmlLog->addFilho(xml2);

    return true;

}

// Verifica se os clientes tem saldo para continuar a jogar
void casino::VerificaUsersTemSaldo(){
    //itera sobre a lista de máquinas
    for (auto it = ListaMq->begin(); it != ListaMq->end(); ++it){
        maquina * Mq = (*it);
        // caso a maquina esteja ligada
        if ((*it)->getEstado() == ON){
            // carrega a lista de clientes 
            list<Cliente *>* Lista = (*it)->getCl();
            if (Lista->size() > 0) {
                //itera sobre a lista de clientes 
                for (auto it2 = Lista->begin(); it2 != Lista->end(); ) {
                    Cliente* cl = *it2;

                    if (cl->getApostaPendente() == 0 && cl->getSaldo() == 0) {
                        string mensagem = "O cliente " + to_string(cl->getNumero()) + " na maquina " + Mq->getTipo() + " na posicao " + to_string(Mq->getPosX()) + "," + to_string(Mq->getPosY()) + " saiu da maquina.";
                        XmlReader * xml = new XmlReader("logdata", mensagem, XmlLog);
                        XmlLog->addFilho(xml);
                        
                        auto nextIt = std::next(it2);
                        (*it)->removeCl(cl);
                        it2 = nextIt;
                    } else {
                        ++it2;
                    }
                }
            }
        }
    }
}

// Faz a saida de clientes das maquinas random
void casino::saidaUsersMaquinas(){
    int utilizadoresMaqAtuais = contagemUsersMaquinas();
    if (utilizadoresMaqAtuais > 0) {
        
        VerificaUsersTemSaldo();
        int utilizadoresSobraram = contagemUsersMaquinas();
        if (utilizadoresSobraram > 0) {
            Uteis U = Uteis();
            int jogadoresMaquinas = this->contagemUsersMaquinas();
            
            int valor = U.valorRand(1,jogadoresMaquinas);
            Cliente *Cl;
            maquina *Mq;

            for(int i = 1; i <= valor; i++){
                Cl = randomClMaquina();
                if (!Cl) break;
                Mq = getMaquinaPorCliente(Cl);
                Mq->removeCl(Cl);

                string mensagem = "O cliente " + to_string(Cl->getNumero()) + " na maquina " + Mq->getTipo() + " na posicao " + to_string(Mq->getPosX()) + "," + to_string(Mq->getPosY()) + " saiu da maquina.";
                XmlReader * xml = new XmlReader("logdata", mensagem, XmlLog);
                XmlLog->addFilho(xml);
            }
        }
    }
}

// Devolve uma Contagem de Clientes nas Máquinas
int casino::contagemUsersMaquinas(){
    int icr =0;
    for (auto it = ListaMq->begin(); it != ListaMq->end(); ++it){
        if ((*it)->getEstado() == ON){
            list<Cliente *>* Lista = (*it)->getCl();
            icr = icr + Lista->size();
        }
    }
    
    return icr;
}

// Devolve cliente na máquina random
Cliente* casino::randomClMaquina(){
    Uteis U;
    int icr = 1,valor = U.valorRand(1,contagemUsersMaquinas());

    for (auto it = ListaMq->begin(); it != ListaMq->end(); ++it){
        if ((*it)->getEstado() == ON){
            list<Cliente *>* Lista = (*it)->getCl();
            
            for (auto it2 = Lista->begin(); it2 != Lista->end(); ++it2){
                if (icr == valor){
                    return (*it2);
                }
                icr++;
            }
        }
    }

    return nullptr;
}

// Devolve maquina baseado no codigo
maquina* casino::getMaquina(int cod){
    for (auto it = ListaMq->begin(); it != ListaMq->end(); ++it){
        if ((*it)->compareId(cod) == 1){
            return (*it);
        }
    }

    return nullptr;
}

// Devolve estado casino
bool casino::getEstado(){
    return aberto;
}

// Devolve contagem de clientes no casino
int casino::contagemClNoCasino(){
    return ClNoCasino->size();
}

// funcao que lista maquinas do casino
void casino::listarMaquinas() {
    cout << "######################################" << endl;
    cout << "########## LISTA DE MAQUINAS #########" << endl;
    cout << endl;
    cout << std::left << setw(10) << "TIPO" << "\t\t" << "POS X" << "\t" << "POS Y" << "\t" << "ESTADO" << "\t" << "ID" << endl;
    for (auto it = ListaMq->begin(); it != ListaMq->end(); ++it){
        maquina* MQ = (*it);
        MQ->mostrar();
    }
    cout << endl;
    cout << "######################################" << endl;
}

// funcao que lista maquinas do casino
void casino::listarClientes() {
    cout << "######################################" << endl;
    cout << "########## LISTA DE CLIENTES #########" << endl;
    cout << endl;
    cout << "No"<< "\t" << "NOME" << left << setw(35) << "\t" << "SALDO" << endl;
    for (auto it = ListaCl->begin(); it != ListaCl->end(); ++it){
        Cliente* CL = (*it);
        CL->mostrar();
    }
    cout << endl;
    cout << "######################################" << endl;
}

void casino::saidaUersCasino() {
    Uteis util = Uteis();
    list<Cliente *>* lcc = ClNoCasino;
    

    int numeroAtualClientes = nmrClientesCasinoSemMaquina();
    int numeroRetirar = util.valorRand(0, numeroAtualClientes);
    //cout << "EStAO " << numeroAtualClientes << " saem " << numeroRetirar <<  endl;
    
    int i = 1;
    while (i <= numeroRetirar)
    {
        Cliente * cl = nullptr;
        do
        {
           cl = clienteCasinoSemMaquina(); 
          
        } while (cl == nullptr);
        
        if (cl != nullptr) { 
            //cout << "REMOVI O USER " << cl->getNumero() << endl;
            this->removeClCasino(cl);
        }
        i++;
    }
    //cout << "fiquei com -> " << ClNoCasino->size() << endl;
}

void casino::removeClCasino(Cliente* cliente) {
  
    for (auto it = ClNoCasino->begin(); it != ClNoCasino->end(); ++it){
        Cliente* CL = (*it);
        if (cliente->getNumero() == CL->getNumero()) {
            ClNoCasino->erase(it);
            return;
        }
    }
}

int casino::nmrMaquinasActivas() {
    int nmrMaquinasAct = 0;
    for (auto it = ListaMq->begin(); it != ListaMq->end(); ++it){
        maquina* mq = (*it); 
        estado est = mq->getEstado(); 
        if (est == 1) {
            nmrMaquinasAct++;
        }
    }
    return nmrMaquinasAct;
}

Cliente* casino::clienteCasinoSemMaquina() {
    Uteis ut = Uteis();
    Cliente * cl = nullptr;
   
    do
    {
        int valor = ut.valorRand(1, ClNoCasino->size());
        int incr = 1;
        for (auto it = ClNoCasino->begin(); it != ClNoCasino->end(); ++it) {
            if (incr == valor) {
                Cliente* cl = (*it);
                maquina* mq = getMaquinaPorCliente(cl);
        
                if (mq == nullptr) {
                    return cl;
                }
            }
            incr++;
        }
        if (todosSemSaldo() == true) {
            return nullptr;
        }
    } while (cl == nullptr);
        
        
    return nullptr;
}

void casino::listaJogagoresMaquinas() {
    for (auto it = ListaMq->begin(); it != ListaMq->end(); ++it){
        maquina * maq = (*it);
        maq->mostrar();
        list<Cliente* > * lc = maq->getCl();
         for (auto it2 = lc->begin(); it2 != lc->end(); ++it2){
            Cliente * cl = (*it2);
            cl->mostrar();
         }
    } 
}

int casino::nmrClientesCasinoSemMaquina() {
    int usersSemMaquina = 0;
    for (auto it = ClNoCasino->begin(); it != ClNoCasino->end(); ++it){
        if (getMaquinaPorCliente((*it)) == nullptr) {
            usersSemMaquina++;
        }
    } 
    return usersSemMaquina;
}

maquina* casino::maquinaLivre() {
    Uteis ut = Uteis();
    maquina * maq = nullptr;
    int maquinasLigadas = nmrMaquinasActivas();
    do
    {
        int valor = ut.valorRand(0,nmrMaquinasActivas());
        if (valor == 0) return nullptr;
        int incr = 1;
        for (auto it = ListaMq->begin(); it != ListaMq->end(); ++it) {
            if (valor == incr) {
                if ((*it)->getEstado() == ON) {
                    return (*it);
                }
            }
            incr++;
        }
    } while (maq == nullptr);
    
    return nullptr;
}

bool casino::todosSemSaldo() {
    int numeroClnoCasino = ClNoCasino->size();
    int clientesSemSaldo = 0;
    for (auto it = ClNoCasino->begin(); it != ClNoCasino->end(); ++it) {
       if((*it)->getSaldo() == 0) {
        clientesSemSaldo++;
       }
    }
    return numeroClnoCasino == clientesSemSaldo;
}

bool casino::exporLlog() {
    XmlReader * xmlLogger = XmlLog;
    return xmlLogger->saveAsXML("log.xml");
}

// retorna se deve fechar o casino ou nao 
bool casino::verificaHoras(const std::tm& timeStruct) {
    int horas_atuais = timeStruct.tm_hour;
    int minutos_atuais = timeStruct.tm_min;

    std::time_t abertura = this->hora_abertura;
    std::tm *ltm = std::localtime(&abertura);
    int hora_abertura_h = ltm->tm_hour;
    int hora_abertura_m = ltm->tm_min;

    std::time_t fecho = this->hora_fecho;
    std::tm *ltm1 = std::localtime(&fecho);
    int hora_fecho_h = ltm1->tm_hour;
    int hora_fecho_m = ltm1->tm_min;

    // Check if it is within the opening and closing hours
    if ((horas_atuais == hora_abertura_h && minutos_atuais >= hora_abertura_m) ||
        (horas_atuais > hora_abertura_h) ||
        (horas_atuais < hora_fecho_h) ||
        (horas_atuais == hora_fecho_h && minutos_atuais <= hora_fecho_m)) {
        return true;
    }

    return false;
}

void casino::alterarEstadoMaquina(int ID, estado e){
    maquina *MQ = getMaquina(ID);

    if (!MQ){
        cout << "Máquina não existe!\n";
    }

    MQ->setEstado(e);
}

void casino::removerClientesMaquinas(){
    for (auto it = ListaMq->begin(); it != ListaMq->end(); ++it) {
        (*it)->removeTodosCl();
    }
}

void casino::removerClientesCasino(){
    for (auto it = ClNoCasino->end(); it != ClNoCasino->begin(); --it) {
        ClNoCasino->pop_back();
    }
    if (ClNoCasino->size() > 0){
        ClNoCasino->pop_front();
    }
}

