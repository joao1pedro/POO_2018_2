#include <iostream>
#include <map>
#include <sstream>
using namespace std;

class Professor{
public:
    string nome;
    string siape;
    Professor(string nome = "", string siape = ""):
        nome(nome), siape(siape)
        {
        }
};

class Aluno{
public:
    string matricula;
    string curso;
    string nome;

    Aluno(string matricula = "", string curso = "", string nome = ""):
        matricula(matricula), curso(curso), nome(nome)
    {
    }
};

class Disciplina{
    string codigo;
    string curso;
    string nome;

    Disciplina(string codigo = "", string curso = "", string nome = ""):
        codigo(codigo), curso(curso), nome(nome)
    {
    } 
};

template<typename T>
struct Repositorio{
    map<string, T> data;

    void add(string key, T elem){
        if(!exists(key))
            data[key] = elem;
        else
            throw "chave duplicada";
    }
    
    bool exists(string key){
        return data.find(key) != data.end();
    }

    T& get(string key){
        auto it = data.find(key);
        if(it != data.end())
            return it->second;
        else
            throw "chave nao existe";
    }

    void rm(string key){
        if(!exists(key))
            throw "chave nao existe";
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
};

class Controller{

};
