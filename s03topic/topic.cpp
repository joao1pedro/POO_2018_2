#include <iostream>
#include <vector>
#include <sstream>
using namespace std;

struct Passageiro{
    string id;
    string idade;

    Passageiro(string id = "fulano", string idade = "0"){
        this->id = id;
        this ->idade = idade;
    }

    string toString(){
        stringstream ss;
        ss << this->id << ":" << this->idade;
        return ss.str();
    }
};

struct Topic{
    vector <Passageiro*> cadeiras;

    Topic(int capMax = 0, int qtdPref = 0):
        cadeiras(capMax, nullptr)
    {
    }

    ~Topic(){
        for(Passageiro * pass : cadeiras)
            delete(pass);
    }

    string toString(){
        stringstream ss;
        ss << "[ ";
        for(Passageiro* passageiro : cadeiras){
            if(passageiro != nullptr)
                ss << passageiro->toString() << " ";
            ss << "-" << "  ";
        }
        ss << "]";
        return ss.str();
    }
};

int main()
{
    Topic topic;
    string op;

    while(true){
        cin >> op;
        if(op == "show")
            cout << topic.toString() << endl;
        else if(op == "new"){
            int capMax, qtdPref;
            cin >> capMax >> qtdPref;
            topic = Topic(capMax, qtdPref);
        }
    }
    
    return 0;
}

