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

    bool inPass(Passageiro *passageiro, int ind){
        int qtd = cadeiras.size();
        if((ind < 0) || (ind >= qtd)){
            cout << "fail: topic lotada" << endl;
            return false;
        } 
        if(cadeiras[ind] != nullptr){ 
            cout << "fail: essa cadeira ja esta ocupada" << endl; 
            return false;
        }
        for(int i = 0; i < (int) cadeiras.size(); i++){
            if((cadeiras[i] != nullptr) && (cadeiras[i]->id == passageiro->id)){
                cout << "fail: voce ja esta na topic" << endl;
                return false;
            }
        }
        cadeiras[ind] = passageiro;
        return true;
        
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

    string toString(){
        stringstream ss;
        ss << "[ ";
        for(Passageiro* passageiro : cadeiras){
            if(passageiro != nullptr)
                ss << passageiro->toString() << " ";
            else{
                ss << "-" << "  ";
            }
        }
        ss << "]";
        return ss.str();
    }
};

struct Controller{
    Topic topic;
    int ind = 0;

    string shell(string line){
        stringstream ui(line);
        stringstream out;
        string op;
        ui >> op;
        int qtdPref = 0, qtd;

        if(op == "help")
            out << "new _ _; show; in _; out _";
        else if (op == "show")
            out << topic.toString();
        else if (op == "new"){
            ui >> qtd >> qtdPref;
            topic = Topic(qtd);
            out << "Topic criada com " << qtd << " cadeiras e " << qtdPref << " cadeiras preferenciais";
        }
        else if (op == "in"){
            string id, idade;
            ui >> id >> idade;
            if (topic.inPass(new Passageiro(id, idade), ind)){
                ind++;
                out << "done";
            }
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