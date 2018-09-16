#include <iostream>
#include <vector>
#include <sstream>
using namespace std;

class Cliente{
private:
    string keyID;
    string id;
    int saldo;
    bool alive{true};

public: 
    Cliente(string keyID = "", string id = "", int saldo = 0):
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

struct Agiota{
    int saldoAmigo;
    vector<Cliente> clientes;

    Agiota(int saldoAmigo = 0):
        saldoAmigo(saldoAmigo)
    {
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
            out << "show cli; add _cliChave _nomeCliente; add tr _value; kill _cliChave; clear";
        }
        else if(op == "showcli"){
            out << cliente.toString();
        }
        else if(op == "init"){
            int value;
            ui >> value;
            a = Agiota(value);
            out << "credito Agiota criado com " << value;
        }
        else if(op.compare("add cli")){
            //out << 55;
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
            cout << "  " << shell(line) << endl;
        }
    }
};

int main(){
    Controller c;
    c.ui();

    return 0;
}