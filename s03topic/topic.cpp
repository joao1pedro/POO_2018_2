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
    vector<Passageiro*> cadeiras;

    Topic(int qtd = 0):
        cadeiras(qtd, nullptr)
    {
    }

    ~Topic(){
        for(Passageiro * pass : cadeiras)
            delete(pass);
    }

    bool inPass(Passageiro * passageiro) {
        for(int i = 0; i < (int) cadeiras.size(); i++){
            if(cadeiras[i] == nullptr){
                cadeiras[i] = passageiro;
                return true;
            }
            else if(cadeiras[i]->id == passageiro->id){
                cout << "fail: o passageiro ja esta na topic" << endl;
                return false;
            }
        }
        return false;
    }

    bool outPass(string idPass){
        for(int i =0; i< (int) cadeiras.size(); i++){
            if(idPass == cadeiras[i]->id){
                cadeiras[i] = nullptr;
                return true;
            }
        }
        return false;
    }

    string toString(){
        stringstream ss;
        ss << "[ ";
        for(Passageiro * passageiro : cadeiras){
            if(passageiro != nullptr)
                ss << passageiro->toString() << " ";
            ss << "-" << "  ";
        }
        ss << "]";
        return ss.str();
    }
};

int main(){
    Topic topic;
    string op;
    while(true){
        cin >> op;
        if(op == "show"){
            cout << topic.toString() << endl;
        }
        else if(op == "new"){
            int qtd;
            cin >> qtd;
            topic = Topic(qtd);
            cout << "Topic criada com " << qtd << " cadeiras" << endl;
        }
        else if(op == "in"){
            string id, idade;
            cin >> id >> idade;
            if(topic.inPass(new Passageiro(id, idade)))
                cout << "done" << endl;
        }
        else if(op == "out"){
            string idPass;
            cin >> idPass;
            if(topic.outPass(idPass))
                cout << "done" << endl;
        }
    }
}