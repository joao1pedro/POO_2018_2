#include <iostream>
#include <vector>
#include <sstream>
using namespace std;

struct Passageiro{
    string id;
    int idade;

    Passageiro(string id = "fulano", int idade = 0){
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
    int qtdPref;
    vector<Passageiro *> cadeiras;

    Topic(int qtd = 0) : cadeiras(qtd, nullptr)
    {
    }

    ~Topic(){
        for (Passageiro *pass : cadeiras)
            delete (pass);
    }

    bool inPass(string id, int idade){
        int qtd = cadeiras.size();
        int ind;

        for(int i = 0; i < (int) cadeiras.size(); i++){
                if((cadeiras[i] != nullptr) && (cadeiras[i]->id == id)){
                    cout << "fail: voce ja esta na topic" << endl;
                    return false;
                }
            }
        if(idade >= 60){
            for(int i = 0; i < qtdPref; i++){
                if(cadeiras[i] == nullptr)
                    ind = i; 
            }
            cadeiras[ind] = new Passageiro(id, idade);
            return true;
        }
        else if(idade < 60){
            for(int i = qtd; i >= qtdPref; i--){
                if(cadeiras[i] == nullptr)
                    ind = i; 
            }
            cadeiras[ind] = new Passageiro(id, idade);
            return true;
        }
        return false;
        
    }

    bool outPass(string idPass){
        for (int i = 0; i < (int)cadeiras.size(); i++){
            if (cadeiras[i] != nullptr && cadeiras[i]->id == idPass){
                delete(cadeiras[i]);
                cadeiras[i] = nullptr;
                return true;
            }
            else{
               cout << "fail: " << idPass << " nao esta na topic" << endl;
                return false; 
            }
        }
        return false;
    }

    string toString(){
        stringstream ss;
        ss << "[ ";
        for(int i = 0; i < (int) cadeiras.size(); i++){
            ss << (i < qtdPref ? '@' : '=');
            ss << (cadeiras[i] != nullptr ? cadeiras[i]->toString() : " ");
            ss << "  ";
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
            topic.qtdPref = qtdPref;
            out << "Topic criada com " << qtd << " cadeiras e " << qtdPref << " cadeiras preferenciais";
        }
        else if (op == "in"){
            string id;
            int idade;
            ui >> id >> idade;
            if (topic.inPass(id, idade)){
                out << "done";
            }
        }
        else if (op == "out"){
            string idPass;
            ui >> idPass;
            if (topic.outPass(idPass))
                out << "done";
        }
        else if (op == "clear"){
            system("clear");
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