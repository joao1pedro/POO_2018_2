#include <iostream>
#include <vector>
#include <algorithm>
#include <sstream>
using namespace std;

class Funcionario{
public:
    string nome;
    int MaxDiarias, qtdDiarias;
    float bonus;
    Funcionario(string nome = "", int MaxDiarias = 0){
        this->nome = nome;
        this->MaxDiarias = MaxDiarias;
    }

    virtual float calcSalario() = 0;
};

class Professor : public Funcionario{
public:
    char classe;

    Professor(string nome, char classe){
        this->nome = nome;
        this->classe = classe;
    }
};

class STA : public Funcionario{
public:
    int nivel;

    STA(string nome, int nivel){
        this->nome = nome;
        this->nivel = nivel;
    }
};

class Terceirizado : public Funcionario{
public:
    int horasTrab;
    bool insalubre;

    Terceirizado(string nome, int horasTrab, bool insalubre){
        this->nome = nome;
        this->horasTrab = horasTrab;
        this->insalubre = insalubre;   
    }
};

template<typename T>
struct Repositorio{
    map<string, T> data;

    void add(string key, T elem){
        if(!exists(key))
            data[key] = elem;
        else
            throw "fail: funcionario ja existe";
    }

    bool exists(string key){
        return data.find(key) != data.end();
    }

    string get(string key){
        auto it = data.find(key);
        if(it != data.end())
            return it->second.toString();
        else
            throw "fail: funcionario nao existe";
    }

    void rm(string key){
        if(!exists(key))
            throw "fail: funcionario nao existe";
        data.erase(key);
    }

    vector<T> getValues(){
        vector<T> vp;
        for(auto& par : data)
            vp.push_back(par.second);
        return vp;
    }

    vector<string> getKeys(){
        vector<string> vp;
        for(auto& par : data)
            vp.push_back(par.first);
        return vp;
    }

    string showAll(){
        stringstream ss;
        for(auto it : data){
            ss << "  " << it.second.toString() << endl;
        }
        return ss.str();
    }
};

class Controller{
public:
    string shell(string line){
        stringstream ui(line);
        stringstream out;
        string op;
        ui >> op;

        if(op == "help"){
            out << "addProf _nome _classe;\n"
                << "addSTA _nome _classe;\n"
                << "addTer _nome _horasTrab _salubridade;\n"
                << "show _nome;\n"
                << "rm _nome;\n"
                << "addDiaria _nome;\n" 
                << "setBonus _value;\n"
                << endl;
        }
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

int main()
{
    Controller c;
    c.ui();
    return 0;
}