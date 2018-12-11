#ifndef CONTATO_H
#define CONTATO_H

#include <iostream>
#include <vector>
#include "fone.h"
using namespace std;

class Contato{
    string idCont;
    vector <Fone> telefones;
    bool favorito{false};
    int ligacoes{0};
public:
    Contato(string idCont = ""){
        this->idCont = idCont;
    }
    int getLigacoes(){
        return this->ligacoes;
    }
    void setLigacoes(){
        this->ligacoes = ligacoes+1;
    }
    void setLigacoesToHistorico(int value){
            this->ligacoes = value;
    }
    string getId(){
        return idCont;
    }
    bool getFavoritos(){
        return favorito;
    }
    void setFavoritos(bool value){
        this->favorito = value;
    }
    void addFone(Fone fone){
        if(!Fone::validar(fone.numero))
            throw string("fail: telefone " + fone.numero + " eh invalido");
        telefones.push_back(fone);
    }
    void rmFone(size_t id){
        if(id < 0 || id >= telefones.size())
            throw string("id " + to_string(id) + " nao existe");
        telefones.erase(telefones.begin() + id);
    }
    vector<Fone> getFones(){
        vector<Fone> vp;
        for(auto e : telefones)
            vp.push_back(e);
        return vp;
    }
    string toString(){
        string saida;
        if(favorito)
            saida = " @ ";
        else
            saida = " - ";
        saida += this->idCont + " C ";
        int i = 0;
        for(auto fone : getFones())
            saida += "{ ligacoes " + to_string(getLigacoes()) + "}" + "[" + to_string(i++) + ":" + fone.id + ":" + fone.numero + "]";
        return saida;
    }
};

#endif //CONTATO_H