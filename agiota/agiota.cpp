#include <iostream>
#include <vector>
#include <sstream>
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

    bool add(string key, string id){
        for(int i = 0; i < (int) clientes.size(); i++){
            if(clientes[i].keyID == key){
                cout << "fail: cliente " << key << " ja existe" << endl;
                return false;
            }
        }
        clientes.push_back(Cliente(key, id, 0));
        return true;
    }

    bool emprestimo(string key, float value){
        if(value > saldoAmigo){
            cout << "fail: saldo do agiota eh insuficiente" << endl;
            return false;
        }
        for(int i = 0; i < (int) clientes.size(); i++){
            if(clientes[i].keyID == key){
                clientes[i].saldo = clientes[i].saldo+value;
                saldoAmigo = saldoAmigo-value;
                mov.push_back(Movimentacao(key, value));
                return true;
            }
        }
        cout << "fail: cliente nao existe" << endl;
        return false;
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
    bool kill(string key){
        for(int i = 0; i < (int) clientes.size(); i++){
            if(clientes[i].keyID == key){
                clientes.erase(clientes.begin() + i);
                for(int j = 0; j < (int) mov.size(); j++){
                    if(mov[j].key == key)
                        mov.erase(mov.begin() + j);
                }
                cout << "success: " << key << " foi morto";
                clientes[i].alive = false;
                return true;
            }
        }
        return false;
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

struct Controller{
    Cliente cliente;
    Agiota a;
    
    string shell(string line){
        stringstream ui(line);
        stringstream out;
        string op;
        ui >> op;

        if(op == "help"){
            out << "showCli; showTr; show _cliChave; addCli _cliChave _nomeCliente; addTr _cliChave _value; kill _cliChave; consult;clear;";
        }
        else if(op == "showCli"){
            out << a.toString();
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
            if(a.add(key, id))
                out << "success";
        }
        else if(op == "addTr"){
            string key;
            float value;
            ui >> key >> value;
            if(a.emprestimo(key, value))
                out << "success";
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
            a.kill(key);
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