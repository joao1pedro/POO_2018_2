#ifndef CONTROLLER_H
#define CONTROLLER_H

#include <iostream>
#include <sstream>
#include "fone.h"
#include "agenda.h"
#include "contato.h"
using namespace std;

class Controller {
    Agenda agenda;
public:
    string shell(string line){
        stringstream ss(line);
        string op;
        ss >> op;

        if(op == "help"){
            cout << "addContato nome numero" << endl
                << "rmFone id" << endl
                << "rmContato nome" << endl
                << "agenda" << endl
                << "search palavra" << endl
                << "fav nome" << endl
                << "desfav nome" << endl
                << "update nome numero" << endl
                << "showFavoritos" << endl
                << "historico" << endl
                << "ligar nome" << endl
                << "speedlist" << endl
                << "clean" << endl;
        }
        else if(op == "addContato"){
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
            agenda.incrementarLigacao(nmb);
        }
        else if(op == "historico"){
            for(auto elem : agenda.getHistorico())
                cout << elem->toString() << endl;
        }
        else if(op == "clean"){
            system("clear");
        }
        else if(op == "speedlist"){
            agenda.speedList();
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

#endif //CONTROLLER