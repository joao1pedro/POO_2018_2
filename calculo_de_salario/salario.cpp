#include <iostream>
#include <map>
#include <sstream>
#include <algorithm>
#include <vector>

using namespace std;

template <typename T>
class Respositorio{
    map <string, T> data;
public:
    void add(string key, T t){
        if(exists(key))
            throw string("fail: " + key + " ja existe");
        data[key] = t;
    }

    void rm(string k){
        auto it = data.find(k);
        if(it == data.end())
            throw string("fail: " + k + " nao existe");
        data.erase(it);
    }

    T& get(string k){
        auto it = data.find(k);
        if(it == data.end())
            throw string("fail: " + k + " nao existe");
        return it->second;
    }

    bool exists(string k){
        return data.count(k) != 0;
    }

    string getValues(string k){
        if(!exists(k))
            throw string("fail: " + k + " nao existe");
        return data.find(k)->second->toString();
    }

    void addDiaria(string key){
        if(exists(key)){
            T funcionario = data.find(key)->second;
            funcionario->addDiaria();
        }
    }

    int qtdFunc(){
        int tam;
        tam = data.size();
        return tam;
    }

     vector<string> getKeys(){
        vector<string> vp;
        for(auto& par: data)
            vp.push_back(par.first);
        return vp;
    }
};

class Funcionario{
protected:
    string name;
    string _type;
    float bonus;
    int maxDi;
public:
    Funcionario(string name = "", string _type = "", float bonus = 0.0, int maxDi = 0){
        this->name = name;
        this->_type = _type;
        this->bonus = bonus;
        this->maxDi = maxDi;
    }

    virtual void addDiaria() = 0;
    virtual float calcSalario() = 0;
    virtual float calcSalario(int nivel) = 0;
    virtual float setBonus(float bonus) = 0;
    virtual string getName() = 0;
    virtual string toString() = 0;
};

class Professor : public Funcionario{
private:
    string classe;
    int diaria;
public:
    Professor(string name = "", string classe = "", int diaria = 0):
    Funcionario(name, "Professor", bonus, 2){
        this->classe = classe;
        this->maxDi = maxDi;
        this->diaria = diaria;
    }

    virtual void addDiaria(){
        if(this->diaria > this->maxDi)
            throw string("fail: limite de diarias atingido");
        maxDi -= 1;
        diaria +=1;
    }

    //A 3000 B 5000 C 7000 D 9000 E 11000
    virtual float calcSalario(){
        float salario;
        if(classe == "A"){
            salario = 3000;
        }else if(classe == "B"){
            salario = 5000;
        }else if(classe == "C"){
            salario = 7000;
        }else if(classe == "D"){
            salario = 9000;
        }
        else if(classe == "E"){
            salario = 11000;
        }
        return (salario+this->diaria);
    }

    virtual float calcSalario(int nivel){
        return 0;
    }

    virtual string getName(){
        return name;
    }

    virtual float setBonus(float value){
        this->bonus = value;
        return bonus;
    }

    string toString(){
        stringstream ss;
        ss << "tipo: " <<_type << " nome: " << name
        << " classe: " << classe<< " salario: " << to_string(calcSalario()) << endl;
        return ss.str();
    }

};

class STA : public Funcionario{
private:
    int nivel;
    int diaria;
public:
    STA(string name = "", int nivel = 0, int diaria = 0):
    Funcionario(name, "STA", bonus, 1){
        this->nivel = nivel;
        this->maxDi = maxDi;
        this->diaria = diaria;
    }

    virtual void addDiaria(){
        if(this->diaria > this->maxDi)
            throw string("fail: limite de diarias atingido");
        maxDi -= 1;
        diaria += 1;
    }

    virtual float calcSalario(){
        return 0;
    }

    virtual float calcSalario(int nivel){
        float salario;
        salario = (3000 + (300*nivel));
        return salario;
    }

    virtual string getName(){
        return name;
    }

    virtual float setBonus(float value){
        this->bonus = value;
        return bonus;
    }

    string toString(){
        stringstream ss;
        ss << "tipo: " <<_type << " nome: " << name
        << " nivel: " << nivel << " salario : " << to_string(calcSalario(nivel)) << endl;
        return ss.str();
    }

};

class Terceirizado : public Funcionario{
private:
    int horasT;
    bool insalube;
public:
    Terceirizado(string name = "", int horasT = 0, string check = ""):
    Funcionario(name, "Terceirizado", bonus , 0){
        this->horasT = horasT;
        if(check == "sim")
            this->insalube = true;
        else
            this->insalube = false;
    }

    virtual void addDiaria(){
        throw string("fail: Terceirizado nao recebe diaria");
    }

    virtual float calcSalario(){
        float salario;
        if(!insalube)
            salario = (horasT*4);
        else
            salario = (horasT*4 + 500);
        return salario;
    }

    virtual float calcSalario(int nivel){
        return 0;
    }

    virtual string getName(){
        return name;
    }

    virtual float setBonus(float value){
        this->bonus = value;
        return bonus;
    }

    string toString(){
        stringstream ss;
        ss << "tipo: " <<_type << " nome: " << name
        << " horas: " << horasT << " salario : " << to_string(calcSalario()) << endl;
        return ss.str();
    }
};

class Controller{
private:
    Respositorio <Funcionario*> rep;
public:
    string shell(string line){
        stringstream ui(line);
        stringstream out;
        string op;
        ui >> op;
        if(op == "help"){
            out << "addProf _nome _classe\n" 
            << "addSTA _nome _nivel\n" 
            << "addTer _nome _horasTrab _insalubre\n" 
            << "addDiaria _nome\n"             
            << "show _nome\n"
            << "rm _nome\n"
            << "clear\n"
            << "end\n";
        }
        else if(op == "addProf"){
            string key, classe;
            ui >> key >> classe;
            rep.add(key, new Professor(key, classe));
        }
        else if(op == "addTer"){
            string key, check;
            int horasTrab;
            ui >> key >> horasTrab >> check;
            rep.add(key, new Terceirizado(key, horasTrab, check));
        }else if(op == "addSTA"){
            string key;
            int nivel;
            ui >> key >> nivel;
            rep.add(key, new STA(key, nivel));
        }else if(op == "rm"){
            string key;
            ui >> key;
            rep.rm(key);
        }else if(op == "show"){
            string key;
            ui >> key;
            cout << rep.getValues(key);
        }else if(op == "addDiaria"){
            string key;
            ui >> key;
            rep.addDiaria(key);
        }else if(op == "clear"){
            system("clear");
        }
        /* else if(op == "addBonus"){
            float value;
            ui >> value;
            rep.addBonus(value);
        } */
        else{
            out << "fail: comando invalido\n";
        }
        return out.str();
    }

    void ui(){
        string line;
        while(true){
            getline(cin, line);
            if(line == "end")
                break;
            try{
                cout << shell(line);
            }catch(string e){
                cout << e << endl;
            }
        }
    }
};


int main(){
    Controller c;
    c.ui();
    return 0;
}
