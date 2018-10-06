#include <iostream>
#include <map>
#include <sstream>
#include <vector>
using namespace std;

class Professor{
public:
    string nome;
    string siape;
public:
    Professor(string nome = "", string siape = ""):
        nome(nome), siape(siape)
        {
        }
    string toString(){
        return siape + ":" + nome;
    }
};

class Aluno{
public:
    string matricula;
    string curso;
    string nome;
public:
    Aluno(string matricula = "", string curso = "", string nome = ""):
        matricula(matricula), curso(curso), nome(nome)
    {
    }

    string toString(){
        return matricula + ":" + curso + ":" + nome;
    }
};

class Disciplina{
    string codigo;
    string curso;
    string nome;
public:
    Disciplina(string codigo = "", string curso = "", string nome = ""):
        codigo(codigo), curso(curso), nome(nome)
    {
    } 

    string toString(){
        return codigo + ":" + nome;
    }
};

template<typename T>
struct Repositorio{
    map<string, T> data;

    void add(string key, T elem){
        if(!exists(key))
            data[key] = elem;
        else
            throw "fail: chave ja existe";
    }
    
    bool exists(string key){
        return data.find(key) != data.end();
    }

    string get(string key){
        auto it = data.find(key);
        if(it != data.end())
            return it->second.toString();
        else
            throw "fail: chave nao existe";
    }

    void rm(string key){
        if(!exists(key))
            throw "fail: chave nao existe";
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
            ss << "  " <<  it.second.toString() << endl;
        }
        return ss.str();
    }
};

class Controller{
public:
    Repositorio <Aluno> alunos;
    Repositorio <Disciplina> disciplinas;
    Repositorio <Professor> professores;

    string shell(string line){
        stringstream ui(line);
        stringstream out;
        string op;
        ui >> op;
        try{
            if(op == "help"){
                out << "addAlu _matriccula _curso _nome"
                    << " addPro _siape _nome"
                    << " addDis _codigo _nome"
                    << " getAlu _matricula"
                    << " getPro _siape"
                    << " getDis _codigo"
                    << " showAlu"
                    << " showPro"
                    << " showDisc"
                    << " rmAlu _matricula"
                    << " rmPro _siape"
                    << " rmDis _codigo"
                    << " clear"
                    << " end" << endl;
            }else if(op == "addAlu"){
                string matricula, curso, nome;
                ui >> matricula >> curso;
                getline(ui, nome);
                alunos.add(matricula, Aluno(matricula, curso, nome));
            }
            else if(op == "addDis"){
                string codigo, nome;
                ui >> codigo;
                getline(ui, nome);
                disciplinas.add(codigo, Disciplina(codigo, nome));
            }
            else if(op == "addPro"){
                string siape, nome;
                ui >> siape;
                getline(ui, nome);
                professores.add(siape, Professor(nome, siape));
            }
            else if(op == "showAlu"){
                out << alunos.showAll();
            }
            else if(op == "showPro"){
                out << professores.showAll();
            }
            else if(op == "showDisc"){
                out << disciplinas.showAll();
            }
            else if(op == "getAlu"){
                string key;
                ui >> key;
                out << alunos.get(key);
            }
            else if(op == "getDis"){
                string key;
                ui >> key;
                out << disciplinas.get(key);
            }
            else if(op == "getPro"){
                string key;
                ui >> key;
                out << professores.get(key);
            }
            else if(op == "rmAlu"){
                string key;
                ui >> key;
                alunos.rm(key);
            }
            else if(op == "rmDis"){
                string key;
                ui >> key;
                disciplinas.rm(key);
            }
            else if(op == "rmPro"){
                string key;
                ui >> key;
                professores.rm(key);
            }
        }
        catch(const char* e){
            cout << e << endl;
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

int main()
{
    Controller c;
    c.ui();
    return 0;
}

