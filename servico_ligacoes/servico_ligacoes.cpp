#include <iostream>
#include <map>
#include <algorithm>
#include <vector>
#include <sstream>
using namespace std;

class Fone{
public:
    string id, numero;
    Fone(string id ="", string numero = ""){
        this->id = id;
        this->numero = numero;
    }

    static bool validar(string numero){
        string nmb = "1234567890()-";
        for(auto e : numero){
            if(nmb.find(e) == string::npos)
                return false;
        }
        return true;
    }
};

class Contato{
    string idCont;
    vector <Fone> telefones;
    bool favorito{false};
public:
    Contato(string idCont = ""){
        this->idCont = idCont;
    }
    string getId(){
        return idCont;
    }
    void addFone(Fone nmb){
        if(Fone::validar(nmb.numero))
            throw string("telefone: " + nmb.numero + " tem formato invalido");
        telefones.push_back(nmb);
    }
    void rmFone(size_t id){
        if(id < 0 || id >= (int) telefones.size())
            throw string("id " + to_string(id) + " nao existe");
        telefones.erase(telefones.begin() + id);
    }
    vector<Fone> getFones(){
        vector<Fone> vp;
        for(auto e : vp)
            vp.push_back(e);
        return vp;
    }
    string toString(){
        string ss;
        if(favorito)
            ss += " @ ";
        else
            ss += " - ";
        ss += idCont;
        int i = 0;
        for(auto e : getFones()){
            ss  += "[ " + to_string(i++) + ":" + e.id + ":" + e.numero;
        }
    }
};

class Agenda{

};

