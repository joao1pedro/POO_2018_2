#include <iostream>
#include <vector>
#include <map>
#include <algorithm>
#include <sstream>
using namespace std;

class Emb{ 
public:
    virtual string getId() = 0;
    virtual string toString() = 0;
    virtual ~Emb(){};
};

class Pass: public Emb {
    string id;
public:
    Pass(string id = ""):
        id(id){}
    virtual ~Pass(){
    }
    virtual string getId(){
        return id;
    }
    virtual string toString(){
        return id;
    }
};

class Carga: public Emb {
    string id;
    float peso;
public:
    Carga(string id = "",  float peso = 0){
        this->id = id;
        this->peso = peso;
    }
    virtual ~Carga(){

    }
    virtual float getPeso(){
        return peso;
    }
    virtual string getId(){
        return id;
    }
    virtual string toString(){
        return id;
    }
};

class Vagao{ //contratos
public:
    virtual bool embarcar(Emb * emb) = 0;
    virtual ~Vagao(){};
    virtual bool desembar(string idPass) = 0;
    virtual bool exists(string idPass) = 0;
    virtual string toString() = 0;
};

class VagaoCarga : public Vagao {
    float capacidade;
    map<string, Carga*> elementos;
public:
    VagaoCarga(float capacidade = 0){
        this->capacidade = capacidade;
    }
    ~VagaoCarga(){
        for(auto pair : elementos){
            delete pair.second;
        }
    }
    virtual bool embarcar(Emb* emb){
        if(Carga* carga = dynamic_cast<Carga*>(emb)){
            if(capacidade >= carga->getPeso()){
                elementos[carga->getId()] = carga;
                capacidade = (capacidade-carga->getPeso());
                return true;
            }
        }
        return false;
    }
    virtual bool desembar(string id){
        if(exists(id)){
            auto it = elementos.find(id);
            capacidade = (capacidade+it->second->getPeso());
            delete it->second;
            elementos.erase(it);
            return true;
        }
        return false;
    }
    virtual bool exists(string id){
        if(elementos.count(id) > 0){
            return true;
        }
        return false;
    }
    virtual string toString(){
        stringstream ss;
        ss << "{ ";
        for(auto pair : elementos){
            ss << pair.second->toString() << " ";
        }
        ss <<  capacidade << " }";
        return ss.str();
    }
};

class VagaoPessoas : public Vagao {
    vector<Pass*> passageiros;
public:
    VagaoPessoas(int capacidade):
        passageiros(capacidade, nullptr)
    {}
    ~VagaoPessoas(){
        for(size_t i = 0; i < passageiros.size(); i++){
            if(passageiros[i] != nullptr)
                delete passageiros[i];
        }
    }

    virtual bool embarcar(Emb * emb){
        if(Pass * pass = dynamic_cast<Pass*>(emb)){
            for(size_t i = 0; i < passageiros.size(); i++){
                if(passageiros[i] == nullptr){
                    passageiros[i] = pass;
                    return true;
                }
            }
        }
        return false;
    }
    virtual bool desembar(string idPass){
        for(auto *&pass : passageiros){
            if(pass != nullptr && pass->getId() == idPass){
                pass = nullptr;
                delete pass;
                return true;
            }
        }
        return false;
    }
    virtual bool exists(string idPass){
        for(auto *&pass : passageiros){
            if(pass != nullptr && pass->getId() == idPass)
                return true;
        }
        return false;
    }

    virtual string toString(){
        stringstream ss;
        ss << "[ ";
        for(auto* pass : passageiros){
            if(pass == nullptr)
                ss << "- ";
            else
                ss << pass->toString() << " ";
        }
        ss << "]";
        return ss.str();
    }
};

class Trem{
    vector<Vagao*> vagoes;
    int forca;
public:
    Trem(int forca = 0){
        this->forca = forca;
    }
    ~Trem(){
        for(auto * vagao : vagoes)
            delete vagao;
    }
    bool addVagao(Vagao * vagao){
        if((int) vagoes.size() < forca){
            vagoes.push_back(vagao);
            return true;
        }
        return false;
    }

    bool embarcar(Emb * emb){
        for(auto* vagao : vagoes){
            if(vagao->embarcar(emb))
                return true;
        }
        return false;
    }
    bool desembar(string idPass){
        for(auto* vagao : vagoes){
            if(vagao->desembar(idPass))
                return true;
        }
        return false;
    }
    bool exists(string name){
        for(auto* vagao : vagoes){
            if(vagao->exists(name))
            return true;
        }
        return false;
    }
    string toString(){
        stringstream ss;
        ss << "Trem: ";
        for(auto * vagao : vagoes)
            ss << vagao->toString() << " ";
        return ss.str();
    }
};

template<class T>
T read(stringstream& ss){
    T t;
    ss >> t;
    return t;
}

class Controller{
    Trem trem;
public:
    Controller(){}

    void shell(string line){
        stringstream ss(line);
        string op;
        ss >> op;
        if(op == "init"){ //_forca
            trem = Trem(read<int>(ss));
        }else if(op == "addvp"){
            Vagao * vagao = new VagaoPessoas(read<int>(ss));
            if(!trem.addVagao(vagao))
                delete vagao;
        }else if(op == "embp"){//nome
            Pass * pass = new Pass(read<string>(ss));
            if(!trem.embarcar(pass))
                delete pass;
        }else if(op == "show"){
            cout << trem.toString() << endl;
        }else if(op == "desembp"){
            string name;
            ss >> name;
            if(!trem.desembar(name))
                throw string("fail: passageiro " + name + " nao existe");
            cout << "done\n";
        }else if(op == "addvc"){
            Vagao * vagao = new VagaoCarga(read<float>(ss));
            if(!trem.addVagao(vagao))
                delete vagao;
        }else if(op == "embc"){
            Carga * carga = new Carga(read<string>(ss));
            if(!trem.embarcar(carga))
                delete carga;
        }
        else
            cout << "fail: comando invalido" << endl;
    }

    void exec(){
        string line;
        while(true){
            getline(cin, line);
            cout << "$" << line << endl;
            if(line == "end")
                return;
            try{
                shell(line);
            }catch(const char* e){
                cout << e << endl;
            }catch(string e){
                cout << e << endl;
            }
        }
    }
};

int main(){
    Controller cont;
    cont.exec();
}
/*
init 3
addvp 2
addvp 3
addvp 1
addvp 4
embp davi
embp rui
embp rufus
embp ioda
embp grievous
embp tim_maia
embp zeca









*/