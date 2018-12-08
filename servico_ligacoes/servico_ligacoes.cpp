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

    static bool validar(string number) {
        string data = "1234567890()-";
        for(auto elemento : number)
            if(data.find(elemento) == string::npos)
                return false;
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
            saida += "[" + to_string(i++) + ":" + fone.id + ":" + fone.numero + "]";
        return saida;
    }
};

class Agenda{
    map<string, Contato> contatos;
    map<string, Contato*> favoritos;
    map<string, Contato*> historico;
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
        if(contatos.find(id) != contatos.end())
            historico.insert(make_pair(id, &contatos.at(id)));
        else
            throw string("fail");
    }
    vector<Contato*> getHistorico(){
        vector<Contato*> hist;
        for(auto elemento : historico){
            hist.push_back(elemento.second);
        }
        return hist;
    }
};

class Controller {
    Agenda agenda;
public:
    string shell(string line){
        stringstream ss(line);
        string op;
        ss >> op;

        if(op == "addContato"){
            string name, id_number;
            ss >> name;
            Contato cont(name);
            while(ss >> id_number){
                string id, fone;
                stringstream ssfone(id_number);
                getline(ssfone, id, ':');
                ssfone >> fone;
                cont.addFone(Fone(id, fone));
            }
            agenda.addContato(cont);
        }
        else if(op == "rmFone"){
            string name;
            int indice;
            ss >> name >> indice;
            agenda.getContato(name)->rmFone(indice);
        }
        else if(op == "rmContato"){
            string name;
            ss >> name;
            agenda.rmContato(name);
        }
        else if(op == "agenda"){
            cout << agenda.toString();
        }
        else if(op == "search"){
            string pattern;
            ss >> pattern;
            auto resp = agenda.search(pattern);
            for(auto contato : resp)
                cout << contato.toString() << endl;
        }
        else if(op == "fav"){
            string name;
            ss >> name;
            if(agenda.addFavoritos(name))
                cout << " done \n";
            else
                cout << "fail : contato nao existe\n";
        }
        else if(op == "desfav"){
            string name;
            ss >> name;
            if(agenda.rmFavoritos(name))
                cout << " done \n";
            else
                cout << "fail : contato nao existe\n";
        }
        else if(op == "update"){
            string name, id_number, aux;
            ss >> name;
            aux = name;
            agenda.rmContato(name);
            Contato cont(aux);
            while(ss >> id_number){
                string id, fone;
                stringstream ssfone(id_number);
                getline(ssfone, id, ':');
                ssfone >> fone;
                cont.addFone(Fone(id, fone));
            }
            agenda.addContato(cont);
        }
        else if(op == "showFavoritos"){
            for(auto elem : agenda.getFavoritos())
                cout << elem->toString() << endl;
        }else if(op == "ligar"){
            string nmb;
            ss >> nmb;
            agenda.addHistorico(nmb);
        }
        else if(op == "historico"){
            for(auto elem : agenda.getHistorico())
                cout << elem->toString() << endl;
        }
        else
            cout << "comando invalido" << endl;
        return ss.str();
    }

    void ui() {
        string line = "";
        while(true){
            getline(cin, line);
            if(line == "end")
                return;
            try {
                shell(line);
            }catch(const string& e){
                cout << e << endl;
            }catch (const char* e){
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