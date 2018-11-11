#include <iostream>
#include <vector>
#include <sstream>
#include <algorithm>
#include <map>
using namespace std;

template<typename T>
struct Repositorio{
    map<string, T> data;

    void add(string key, T elem){
        if(!exists(key)){
            data[key] = elem;
            cout << "success";
        }
        else
            throw "cliente ja existe";
    }

    bool exists(string key){
        return data.find(key) != data.end();
    }

    void rm(string key){
        if(!exists(key))
            throw "chave nao existe";
        else{
            data.erase(key);
        cout << "success";
        }
    }

    T& get(string key){
        auto it = data.find(key);
        if(it != data.end())
            return it->second;
        else
            throw "chave nao existe";
    }

    vector<T> getValues(){
        vector<T> vp;
        for(auto& par: data)
            vp.push_back(par.second);
        return vp;
    }

    vector<string> getKeys(){
        vector<string> vp;
        for(auto& par: data)
            vp.push_back(par.first);
        return vp;
    }

    string show(){
        stringstream ss;
        for(auto it : data){
            ss << "  " <<  it.second.toString() << endl;
        }
        return ss.str();
    }
};

class Cliente{
public:
    string keyID;
    string id;
    float saldoDevedor;
    bool alive{true};
 
    Cliente(string keyID = "", string id = "", float saldoDevedor = 0):
        keyID(keyID), id(id), saldoDevedor(saldoDevedor)
    {
    }

    string toString(){
        stringstream ss;
        ss << keyID << ":" << id << ":" << saldoDevedor << endl;
        return ss.str();
    }

    float getSaldo(){
        return saldoDevedor;
    }

    void setSaldo(int value){
        this->saldoDevedor = value;
    }
};

class Transacao{
public:
    
    string key;
    float value;
    int indice;

    Transacao(string key = "", float value = 0, int indice = 0):
        key(key), value(value), indice(indice)
    {
    }

    string getName(){
        return key;
    }

    float getValue(){
        return value;
    }

    string toString(){
        stringstream ss;
        ss << "Ind: " << indice << "[ " << key << value << " ]";
        return ss.str();
    }
};

class Agiota{
public:
    Repositorio<Cliente> repCli;
    Repositorio<Transacao> repTr;
    float saldoAmigo;

    Agiota(float saldoAmigo = 0):
        saldoAmigo(saldoAmigo)
    {
    }

    void setSaldoAmigo(float value){
        this->saldoAmigo = value;
    }

    string saldoAmigoT(){
        stringstream ss;
        ss << "Saldo amigo: " << this->saldoAmigo;
        return ss.str();
    }

    void addCli(string key, string name){
        repCli.add(key, Cliente(key, name));
    }

    string showCli(string key){
        float saldo;
        stringstream ss;
        for(auto& it : repTr.data){
            auto transacao = it.second;
            if(transacao.getName() == key)
                ss << " " << transacao.toString() << endl;
        }
        auto cli = repCli.get(key);
        saldo = cli.getSaldo();
        ss << "  saldo: " << saldo;
    
        return ss.str();
    }

    void addTr(string key, float value){
        if(this->saldoAmigo < value || this->saldoAmigo <= 0){
            throw "fail: saldo insuficiente";
        }
        Cliente& cliente = repCli.get(key);
        cliente.saldoDevedor += value;
        setSaldoAmigo(this->saldoAmigo-value);
        addTr(key, value);
    }

    void kill(string key){
        repCli.rm(key);
        for(auto it : repTr.data){
            if(it.second.getName() == key)
                repTr.rm(it.first);
        }
    }

    void pay(string key, float value){
        Cliente& cliente = repCli.get(key);
        if(cliente.saldoDevedor < value)
            throw "fail: nao posso receber mais do que emprestei";
        cliente.saldoDevedor -= value;
        setSaldoAmigo(this->saldoAmigo = this->saldoAmigo+value);
        addTr(key, value);
    }
};



struct Controller{
    Agiota a;
    
    string shell(string line){
        stringstream ui(line);
        stringstream out;
        string op;
        ui >> op;
 
        try{ 
                if(op == "help"){
                    out << "showCli; showTr; show _cliChave; addCli _cliChave _nomeCliente; addTr _cliChave _value; kill _cliChave; consult;clear;";
                }
                else if(op == "showCli"){
                    string key;
                    ui >> key;
                    out << a.showCli(key);
                }
                else if(op == "init"){
                    float value;
                    ui >> value;
                    a = Agiota(value);
                    out << "success";
                }
                else if(op == "addCli"){
                    string id, key;
                    ui >> key;
                    getline(ui, id);
                    a.addCli(key, id);
                }
                else if(op == "addTr"){
                    string key;
                    float value;
                    ui >> key >> value;
                    
                    a.addTr(key, value);
                }
                else if(op == "showTr"){
                    string key;
                    ui >> key;
                    out << a.repTr.show();
                }
                else if(op == "show"){
                    out << a.repCli.show();
                }
                else if(op == "kill"){
                    string key;
                    ui >> key;
                    a.repCli.rm(key);
                }
                else if(op == "consult"){
                    out << a.saldoAmigoT();
                }
                else if(op == "pay"){
                    string key;
                    float value;
                    ui >> key >> value;
                    a.pay(key, value);
                    out << "success";
                }
                else if(op == "clear"){
                    system("clear");
                }
        }
        catch(const char* e){
            cout << e << endl;
        }
        return out.str();
    }

    void ui(){
        string line;
        stringstream ss;
    
        while(true){
            getline(cin, line);
            if(line == "end")
                break;
            //cout << line << endl;
            cout << "  " << shell(line) << endl;
        }
    }
};

int main(){
    Controller c;
    c.ui();
    return 0;
}