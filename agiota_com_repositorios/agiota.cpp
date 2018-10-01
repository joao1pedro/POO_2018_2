#include <iostream>
#include <vector>
#include <sstream>
#include <algorithm>
#include <map>
using namespace std;

struct Cliente{
    string keyID;
    string id;
    float saldo;
    bool alive{true};
 
    Cliente(string keyID = "", string id = "", float saldo = 0):
        keyID(keyID), id(id), saldo(saldo)
    {
    }

    string toString(){
        stringstream ss;
        ss << this->keyID << ":" << this->id << ":" << this->saldo;
        return ss.str();
    }

    bool testAlive(){
        if(alive)
            return true;
        cout << "fail: cliente esta morto" << endl;
        return false;
    }
    
};

struct Movimentacao{
    string key;
    float value;
    Movimentacao(string key = "", float value = 0):
        key(key), value(value)
    {
    }
};

struct Agiota{
    float saldoAmigo;
    vector<Cliente> clientes;
    vector<Movimentacao> mov;

    Agiota(float saldoAmigo = 0):
        saldoAmigo(saldoAmigo)
    {
    }

    string toString(){
        stringstream ss;
        for(int i = 0; i < (int) clientes.size(); i++){
            ss << clientes[i].toString() << endl;
        }
        return ss.str();
    }

    string saldoAmigoT(){
        stringstream ss;
        ss << "Saldo amigo: " << this->saldoAmigo;
        return ss.str();
    }

    bool testAddTr(float value){
        if(value > saldoAmigo){
            cout << "fail: saldo do agiota eh insuficiente" << endl;
            return false;
        }
        else
            return true;
    }

     string toString_transferencias(){
        stringstream ss;
        for(int i = 0; i < (int) mov.size(); i++)
            ss << "id: "<< i <<"[ "<< mov[i].key << " "<< mov[i].value <<" ]";
        return ss.str();
    }

    string indiv_toString(string key){
        stringstream ss;
        for(int i = 0; i < (int) mov.size(); i++){
            if( key == mov[i].key)
                ss << "id:"<< i << " [ "<<mov[i].key << " " << mov[i].value <<" ]";
        }
        return ss.str();
    }

    bool pay(string key, float value){
        for(int i = 0; i < (int) clientes.size(); i++){
            if(clientes[i].keyID == key){
                if(value > clientes[i].saldo){
                    cout << "fail: pagamento maior que a divida nao eh aceitavel" << endl;
                    return false;
                }
                else{
                    clientes[i].saldo = clientes[i].saldo+value;
                    mov.push_back(Movimentacao(key, value));
                    saldoAmigo = saldoAmigo+value;
                    return true;
                }
            }
        }
        cout << "fail: devedor nao existe" << endl;
        return false;
    }

};

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
    
};

struct Controller{
    Cliente cliente;
    Agiota a;
    Repositorio<Cliente> rcli;
    Repositorio<Movimentacao> rmov;
    
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
                    for(auto& cli : rcli.getValues())
                    out << cli.toString();
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
                    rcli.add(key, Cliente(key, id, 0));
                }
                else if(op == "addTr"){
                    string key;
                    float value;
                    ui >> key >> value;
                    
                    if(a.testAddTr(value))
                        rmov.add(key, Movimentacao(key, value));
                }
                else if(op == "showTr"){
                    string key;
                    ui >> key;
                    out << a.toString_transferencias();
                }
                else if(op == "show"){
                    string key;
                    ui >> key;
                    out << a.indiv_toString(key);
                }
                else if(op == "kill"){
                    string key;
                    ui >> key;
                    rcli.rm(key);
                }
                else if(op == "consult"){
                    out << a.saldoAmigoT();
                }
                else if(op == "pay"){
                    string key;
                    float value;
                    ui >> key >> value;
                    if(a.pay(key, value))
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