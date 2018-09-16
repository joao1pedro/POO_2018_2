#include <iostream>
#include <vector>
#include <sstream>
#include <iomanip>
using namespace std;

struct Operacao{
    string descricao;
    float valor, saldo;

    Operacao(string descricao = "", float valor = 0, float saldo = 0):
        descricao(descricao), valor(valor), saldo(saldo)
    {
    }
};

struct Conta{
    int nextId, numero;
    float saldo;
    vector<Operacao> extrato;

    Conta(int numero = 0, int saldo = 0):
        numero(numero), saldo(saldo)
    {
        extrato.push_back(Operacao("abertura", 0, 0));
    }

    string toString(){
        stringstream ss;
        ss << "conta:" << this->numero << " saldo:" << this->saldo;
        return ss.str(); 
    }

    bool deposito(int value){
        if(value > 0){
            saldo = saldo+value;
            extrato.push_back(Operacao("deposito", value, saldo));
            return true;
        }
        return false;
    }

    bool saque(int value){
        if(saldo < value){
            cout << "fail: saldo insuficiente" << endl;
            return false;
        }
        saldo = saldo-value;
        extrato.push_back(Operacao("saque", -value, saldo));
        return true;
    }

    bool tarifa(int value){
        saldo = saldo-value;
        extrato.push_back(Operacao("tarifa", -value, saldo));
        return true;
    }

    string extratoToString(){
        stringstream ss;
        for(int i = 0; i < (int) extrato.size(); i++){
            ss << setw(3) << i << ":";
            ss << setw(9) << extrato[i].descricao << ":";
            ss << setw(5) << extrato[i].valor << ":";
            ss << setw(5) << extrato[i].saldo << endl;
        }
        return ss.str();
    }

    string extratoN(int value){
        stringstream ss;
        for(int i = (int) extrato.size(); value > 0; i--, value--){
            ss << setw(3) << i << ":";
            ss << setw(9) << extrato[i].descricao << ":";
            ss << setw(5) << extrato[i].valor << ":";
            ss << setw(5) << extrato[i].saldo << endl;
        }
        return ss.str();
    }

    bool extornar(int ind){
        for(int i = 0; i < (int) extrato.size(); i++){
            if(ind == i){
                if(extrato[i].descricao == "tarifa"){
                    saldo = saldo+extrato[i].valor;
                    extrato.push_back(Operacao("deposito", extrato[i].valor, saldo));
                    cout << "success: indice " << ind << " extornado" << endl;
                    return true;
                }
                else{
                    cout << "fail: indice " << ind << " nao eh tarifa" << endl;
                    return false;
                }
            }
        }
        cout << "fail: indice " << ind << " invalido" << endl;
        return false;
    }
};

struct Controller{
    Conta conta;
    string shell(string line){
        stringstream ui(line);
        stringstream out;
        string op;
        ui >> op;
        if(op == "help"){
            out << "show; deposito _value; saque _value; extrato; extratoN _N; extornar; tarifa;";
        }
        else if(op == "show"){
            out << conta.toString(); 
        }
        else if(op == "init"){
            int number;
            ui >> number;
            conta = Conta(number, 0);
            out << "success";
        }
        else if(op == "deposito"){
            float value;
            ui >> value;
            if(conta.deposito(value))
                out << "success";
        }
        else if(op == "saque"){
            float value;
            ui >> value;
            if(conta.saque(value))
                out << "success";
        }
        else if(op == "tarifa"){
            float value;
            ui >> value;
            conta.tarifa(value);
            out << "success";
        }
        else if(op == "extrato"){
            out << conta.extratoToString();
        }
        else if(op == "extratoN"){
            int value;
            ui >> value;
            out << conta.extratoN(value);
        }
        else if(op == "extornar"){
            int ind;
            ui >> ind;
            conta = conta.extornar(ind);
        }
        return out.str();
    }

    void ui(){
        string line;
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