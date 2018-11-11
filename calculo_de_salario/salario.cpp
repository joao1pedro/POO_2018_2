#include <iostream>
#include <vector>
#include <algorithm>
#include <sstream>
#include <map>
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
    //virtual float calcBonus() = 0;
    virtual string toString() = 0;
    virtual void addDiaria() = 0;

    /* void setBonus(float bonus){
        this->bonus = bonus;
    } */
};

class Professor : public Funcionario{
public:
    char classe;

    Professor(string nome, char classe):
    Funcionario(nome, 2)
    {
        this->nome = nome;
        this->classe = classe;
    }

    virtual float calcSalario(char classe){
        float value;
        if(classe == 'A'){
            value = 3000;
        }
        else if(classe == 'B'){
            value = 5000;
        }
        else if(classe == 'C'){
            value = 7000;
        }
        else if(classe == 'D'){
            value = 9000;
        }
        else if(classe == 'E'){
            value = 11000;
        }else{
            throw "classe invalida";
        }
        return value;
    }

    /* void calcBonus(){
        
    } */

    virtual void addDiaria(){
        if(qtdDiarias > MaxDiarias){
            throw "fail: limite de diarias atingido";
        }
        MaxDiarias -=1;
        qtdDiarias +=1;
    }
};

class STA : public Funcionario{
public:
    int nivel;

    STA(string nome, int nivel):
    Funcionario(nome, 1)
    {
        this->nome = nome;
        this->nivel = nivel;
    }

    virtual float calcSalario(int nivel){
        float salario;
        salario = (3000 + (300*nivel));
        return salario;
    }

    virtual void addDiaria(){
        if(qtdDiarias > MaxDiarias){
            throw "fail: limite de diarias atingido";
        }
        MaxDiarias -=1;
        qtdDiarias +=1;
    }
};

class Terceirizado : public Funcionario{
public:
    int horasTrab;
    bool insalubre;

    Terceirizado(string nome, int horasTrab, bool insalubre):
    Funcionario(nome, 0)
    {
        this->nome = nome;
        this->horasTrab = horasTrab;
        this->insalubre = insalubre;   
    }

    virtual float calcSalario(int horasTrab, bool insalubre){
        float salario;
        if(insalubre)
            salario = ((4*horasTrab)+500);
        salario = 4*horasTrab;
        return salario;
    }

    virtual void addDiaria(){
        throw "fail: terceirizado nao pode receber diaria";
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

    string show(){
        stringstream ss;
        for(auto it : data){
            ss << "  " << it.second->toString() << endl;
        }
        return ss.str();
    }
};

class Controller{
    Repositorio <Funcionario*> rFunc;
public:
    string shell(string line){
        stringstream ui(line);
        stringstream out;
        string op;
        ui >> op;

        if(op == "help"){
            out << "addProf _nome _classe;\n"
                << "  " << "addSTA _nome _classe;\n"
                << "  " << "addTer _nome _horasTrab _salubridade;\n"
                << "  " << "show _nome;\n"
                << "  " << "rm _nome;\n"
                << "  " << "addDiaria _nome;\n" 
                << "  " << "setBonus _value;\n"
                << endl;
        }else if(op == "addProf"){
            string name;
            char classe;
            ui >> name >> classe;
            rFunc.add(name, new Professor(name, classe));
        }else if(op == "addSTA"){
            string name;
            int nivel;
            ui >> name >> nivel;
            //rFunc.add(name, new STA(name, nivel));
        }
        else if(op == "show"){
            string nome;
            ui >> nome;
            cout << rFunc.show() << endl;
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
            try{ 
            cout << "  " << shell(line) << endl;
            }catch(const char* e){
                cout << e << endl;
            }
        }
    }
};

int main()
{
        Controller c;
        c.ui();
        return 0;
}