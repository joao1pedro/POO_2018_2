#include <iostream>
#include <vector>
#include <sstream>

using namespace std;

struct Fone{
    string label;
    string fone;

    Fone(string label = "", string fone = "") :
        label(label), fone(fone)
    {
    }

    string toString(){
        stringstream ss;
        ss << this->label << ":" << this->fone;
        return ss.str();
    }

    static bool validate(string number){
        string valido = "()0123456789.";
        for(auto nmb : number){
            if(valido.find(nmb) == string::npos)
                return false; 
                /* find verifica a posicao da string encontrada
                se nao encontrar retorna -1 */
        }
        return true;
    }
};

class Contato{
private:
    string id;
    vector<Fone> fones;
public:
    Contato(string id = ""):
        id(id)
    {
    }

    bool add(Fone fone){
        fones.push_back(fone);
        return true;
    }

    bool rm(int ind){
        if(ind < 0 || ind >= (int) fones.size()){
            cout << "fail: indice invalido" << endl;
            return false;
        }
        fones.erase(fones.begin() + ind);
        return true;
    }

    string toString(){
        stringstream ss;
        ss << id << "=>";
        for(int i = 0; i < (int) fones.size(); i++)
            ss << "[" << i << ":" << fones[i].label << ":" << fones[i].fone << "]";
        return ss.str();
    }
};

struct Controller{
    Contato contato;

    string shell(string line){
        stringstream ui(line);
        stringstream out;
        string op;
        ui >> op;

        if(op == "help"){
            out << "show; init _; add _id_fone; end";
        }
        else if(op == "init"){
            string nome;
            ui >> nome;
            contato = Contato(nome);
            out << "success";
        }
        else if(op == "add"){
            string label;
            string fone;
            ui >> label >> fone;

            if(!Fone::validate(fone)){
                out << "fail: formato de telefone invalido";
            }
            else{
                contato.add(Fone(label, fone));
                out << "success";
            }
        }
        else if(op == "rm"){
            int indice;
            ui >> indice;
            if(contato.rm(indice)){
                out << "success";
            }
        }
        else if(op == "show"){
            out << contato.toString();
        }
        else if(op == "update"){
            string nome;
            ui >> nome;
            contato = Contato(nome);
            string telefone;
            while(ui >> telefone){
                stringstream ss(telefone);
                string label;
                string fone;

                getline(ss, label, ':');
                getline(ss, fone);

                if(Fone::validate(fone))
                    contato.add(Fone(label, fone));
            }
            out << "success";
        }
        else if(op == "clear"){
            system("clear");
        }
        return out.str();
    }

    void io(){
        string line;
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
    c.io();
    return 0;
}