#ifndef AGENDA_H
#define AGENDA_H

#include <iostream>
#include <map>
#include <unordered_map>
#include <vector>
#include <sstream>
#include "contato.h"
using namespace std;

class Agenda{
    map<string, Contato> contatos;
    map<string, Contato*> favoritos;
    unordered_map<string, Contato*> historico;
public:
    void addContato(Contato cont){
        string name = cont.getId();
        if(contatos.count(name) == 1)
            throw string("contato " + name + " ja existe");
        contatos[name] = cont;
    }
    void rmContato(string id){
        contatos.erase(id);
    }
    Contato* getContato(string id){
        if(contatos.count(id))
            return &contatos[id];
        throw string("fail: contato " + id + " nao existe");
    }
    vector<Contato> getContatos(){
        vector<Contato> vp;
        for(auto& pair : contatos)
            vp.push_back(pair.second);
        return vp;
    }
    vector<Contato> search(string id){
        vector<Contato> vp;
        for(auto& pair : contatos)
            if(pair.second.toString().find(id) != string::npos)
                vp.push_back(pair.second);
        return vp;
    }
    string toString(){
        string saida = "";
        for(auto contato : getContatos())
            saida += contato.toString() + "\n";
        return saida;
    }
    bool addFavoritos(string id){
        if(contatos.find(id) != contatos.end()){
            contatos.at(id).setFavoritos(true);
            favoritos.insert(make_pair(id, &contatos.at(id)));
            return true;
        }
        return false;
    }
    bool rmFavoritos(string id){
        if(contatos.find(id) != contatos.end()){
            contatos.at(id).setFavoritos(false);
            favoritos.erase(id);
            return true;
        }
        return false;
    }
    vector<Contato*> getFavoritos(){
        vector<Contato*> fav;
        for(auto elemento : favoritos){
            fav.push_back(elemento.second);
        }
        return fav;
    }
    void addHistorico(string id){
        int aux = 0;
        if(contatos.find(id) != contatos.end()){
            aux = contatos.at(id).getLigacoes();
            historico.erase(id);
            historico.insert(make_pair(id, &contatos.at(id)));
            historico.at(id)->setLigacoesToHistorico(aux);
        }
        else
            throw string("fail: " + id + " nao existe nos contatos");
    }
    vector<Contato*> getHistorico(){
        vector<Contato*> hist;
        for(auto elemento : historico){
            hist.push_back(elemento.second);
        }
        return hist;
    }
    bool exists(string k){
        return contatos.count(k) != 0;
    }
    void incrementarLigacao(string k){
        if(exists(k)){
            contatos.at(k).setLigacoes();
        }
    }
    void speedList(){
        std::map<string,Contato>::iterator maior;
        maior = contatos.begin();
        for(auto it = (maior++); it != contatos.end(); it++){
            if(it->second.getLigacoes() > maior->second.getLigacoes())
                maior = it;
        }
        cout << maior->second.toString() << endl;
    }
};

#endif //AGENDA