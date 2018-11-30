#include <iostream>
#include <sstream>
#include <vector>
#include <map>

using namespace std;

class Entry {
    bool favorited{false};
public:
    //virtual ~Entry() = 0;
    virtual string getId() = 0;
    virtual void setFavorited(bool value) = 0;
    virtual bool isFavorited() = 0;
    virtual string toString() = 0;
};


class Fone {
public:
    string id;
    string number;

    Fone(string id = "", string number = ""){
        this->id = id;
        this->number = number;
    }

    static bool validate(string number) {
        string data = "1234567890()- ";
        for(auto c : number)
            if(data.find(c) == string::npos)
                return false;
        return true;
    }

};

class Contato : public Entry{
    string name;
    vector<Fone> fones;
    bool favorited{false};
public:
    Contato(string name = ""){
        this->name = name;
    }

    string getId(){
        return name;
    }

    void addFone(Fone fone){
        if(!Fone::validate(fone.number))
            throw string("fone " + fone.number + " invalido");
        fones.push_back(fone);
    }

    void rmFone(size_t indice){
        if(indice < 0 || indice >= fones.size())
            throw string("indice " + to_string(indice) + " nao existe");
        fones.erase(fones.begin() + indice);
    }

    vector<Fone> getFones(){
        vector<Fone> resp;
        for(auto fone: fones)
            resp.push_back(fone);
        return resp;
    }

    string toString(){
        string saida;
        if(favorited)
            saida = " @ ";
        else
            saida = " - ";
        saida += this->name + " C ";
        int i = 0;
        for(auto fone : getFones())
            saida += "[" + to_string(i++) + ":" + fone.id + ":" + fone.number + "]";
        return saida;
    }

    bool isFavorited(){
        return favorited;
    }

    void setFavorited(bool value){
        favorited = value;
    }

};

class Agenda {
    map<string, Entry*> m_entries;
    map<string, Entry*> m_favorites;

public:
    void addEntry(Entry * entry){
        m_entries.insert(make_pair(entry->getId(), entry));
    }
    void rmEntry(string id){
        m_entries.erase(id);
    }
    void favorite(string idEntry){
        if(m_entries.find(idEntry) != m_entries.end()){
            m_entries.at(idEntry)->setFavorited(true);
            m_favorites.insert(make_pair(idEntry, m_entries.at(idEntry)));
        }
        else
            throw string("fail: entrada nao existe");
    }
    void unfavorite(string idEntry){
        if(m_entries.find(idEntry) != m_entries.end()){
            m_entries.at(idEntry)->setFavorited(false);
            m_favorites.erase(idEntry);
        }
        else
            throw string("fail: entrada nao existe");
    }
    vector<Entry*> getFavorited(){
        vector <Entry*> fav;
        for(auto pair : m_favorites)
            fav.push_back(pair.second);
        return fav;
    }
    Entry * getEntry(string id){
        if(m_entries.find(id) != m_entries.end())
            return m_entries.at(id);
        else
            throw string("fail: entrada nao existe");
    }
    vector<Entry*> getEntries(){
        vector<Entry*> entradas;
        for(auto pair : m_entries)
            entradas.push_back(pair.second);
        return entradas;
    }
    /* vector<Entry*> search(string pattern){

    } */
    string toString(){
        stringstream ss;
        for(auto elem : m_entries)
            ss << elem.second->toString() << endl;
        return ss.str();
    }
};

class Note : public Entry { 
    string id;
    vector<string> itens;
public:
    Note(string id = "")
        :id(id)
    {}
    string getId(){
        return id;
    }
    void addItem(string item){
        itens.push_back(item);
    }

    void rmItem(int indice){
        itens.erase(itens.begin()+indice);
    }

    string toString(){
        string saida = toString() + " N [ ";
        for(auto item : itens){
            saida += item + " ";
        }
        return saida + "]";
    }

    bool isFavorited(){
        return false;
    }

    void setFavorited(bool value){
        return;
    }
};

class AgendaMaster : public Agenda{
public:
    AgendaMaster(){

    }
    Contato * getContato(string id){
        if(Contato* cont = dynamic_cast <Contato*>(getEntry(id)))
            return cont;
        return nullptr;
    }
    Note * getNote(string id){
        if(Note* note = dynamic_cast <Note*>(getEntry(id)))
            return note;
        return nullptr;
    }
}; 

class Controller {

    AgendaMaster agenda;
public:

    void shell(string line){
        stringstream ss(line);
        string op;
        ss >> op;

        if(op == "addContato"){
            string name, id_number;
            ss >> name;
            agenda.addEntry(new Contato(name));
            while(ss >> id_number){
                string id, fone;
                stringstream ssfone(id_number);
                getline(ssfone, id, ':');
                ssfone >> fone;
            }

            Contato *cont = agenda.getContato(name);
            cont->addFone(Fone(id_number));
        }
        else if(op == "rmFone"){
            string name;
            int indice;
            ss >> name >> indice;

            Contato *cont = agenda.getContato(name);
            cont->rmFone(indice);
        }
        else if(op == "rmContato"){
            string name;
            ss >> name;
            agenda.rmEntry(name);
        }
        else if(op == "agenda"){
            cout << agenda.toString();
        }
        else if(op == "search"){
            string pattern;
            ss >> pattern;
            auto resp = agenda.getEntry(pattern);
            ss << resp->toString() << endl;
        }
        else if(op == "fav"){
            string name;
            ss >> name;
            agenda.favorite(name);
            cout << " done \n";
        }
        else if(op == "desfav"){
            string name;
            ss >> name;
            agenda.unfavorite(name);
            cout << " done \n";
        }
        else if(op == "showFav"){
            for(auto elem : agenda.getFavorited())
                cout << elem->toString() << endl;
        }
        else if(op == "addNote"){
            string name;
            ss >> name;
            agenda.addEntry(new Note(name));
        }
        else if(op == "rmNote"){
            string name;
            ss >> name;
            agenda.rmEntry(name);
        }
        else if(op == "addItem"){
            string name, note, texto;
            ss >> name;

            while(ss >> texto){
                note = note + texto + " ";
            }

            Note* _note = agenda.getNote(name);
            _note->addItem(note);
        }
        else if(op == "clear"){
            system("clear");
        }
        else if(op == "rmItem"){
            string name;
            int indice;
            ss >> name >> indice;

            Note *_note = agenda.getNote(name);
            _note->rmItem(indice);
        }
        else
            cout << "comando invalido" << endl;
    }


    void exec() {
        string line = "";
        while(true){
            getline(cin, line);
            cout << "$" << line << endl;
            if(line == "end")
                return;
            try {
                shell(line);
            } catch(const string& e) {
                cout << e << endl;
            }
        }
    }
};

int main()
{
    Controller controller;
    controller.exec();
    return 0;
}