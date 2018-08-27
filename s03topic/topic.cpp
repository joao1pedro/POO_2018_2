#include <iostream>
#include <vector>
#include <sstream>
using namespace std;

struct Passageiro{
    string id;
    string idade;

    Passageiro(string id = "fulano", string idade = "0"){
        this->id = id;
        this->idade = idade;
    }
    string toString(){
        stringstream ss;
        ss << this->id << ":" << this->idade;
        return ss.str();
    }
};

struct Topic{
    vector<Passageiro *> cadeiras;

    Topic(int qtd = 0) : cadeiras(qtd, nullptr)
    {
    }

    ~Topic(){
        for (Passageiro *pass : cadeiras)
            delete (pass);
    }

    bool inPass(Passageiro *passageiro){
        for (int i = 0; i < (int)cadeiras.size(); i++){
            if (cadeiras[i] == nullptr){
                cadeiras[i] = passageiro;
                return true;
            }
            else if (cadeiras[i]->id == passageiro->id){
                cout << "fail: o passageiro ja esta na topic" << endl;
                return false;
            }
        }
        return false;
    }

    bool outPass(string idPass){
        for (int i = 0; i < (int)cadeiras.size(); i++){
            if (cadeiras[i] == nullptr){
                cout << "fail: " << idPass << " nao esta na topic" << endl;
                return false;
            }
            else if (idPass == cadeiras[i]->id){
                cadeiras[i] = nullptr;
                return true;
            }
        }
        return false;
    }

    string toString(int qtdPref){
        stringstream ss;
        int aux = qtdPref;
        ss << "[ ";
        for (Passageiro *passageiro : cadeiras){
            if (passageiro != nullptr)
                ss << passageiro->toString() << " ";
            for (int i = 0; i < qtdPref; i++){
                if (aux > 0)
                    ss << "@" << "  ";
                aux--;
            }
            ss << "-" << "  ";
        }
        ss << "]";
        return ss.str();
    }
};

struct Controller{
    Topic topic;

    string shell(string line){
        stringstream ui(line);
        stringstream out;
        string op;
        ui >> op;
        int qtdPref = 0;

        if(op == "help")
            out << "new _ _; show; in _; out _";
        else if (op == "show")
            out << topic.toString(qtdPref);
        else if (op == "new"){
            int qtd;
            ui >> qtd >> qtdPref;
            topic = Topic(qtd);
            out << "Topic criada com " << qtd << " cadeiras e " << qtdPref << " cadeiras preferenciais";
        }
        else if (op == "in"){
            string id, idade;
            ui >> id >> idade;
            if (topic.inPass(new Passageiro(id, idade)))
                out << "done";
        }
        else if (op == "out"){
            string idPass;
            ui >> idPass;
            if (topic.outPass(idPass))
                out << "done";
        }
        return out.str();
    }

    void io(){
        string line;
        while(true){
            getline(cin, line);
            if(line == "end")
                return;
            //cout << line << endl;
            cout << "  " << shell(line) << endl;
        }
    }
};

int main(){
    Controller c;
    c.io();
    return 0;
}