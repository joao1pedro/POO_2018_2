#include <iostream>
#include <vector>
#include <sstream>
using namespace std;

class Nota{
    string titulo;
    string texto;
public:
    Nota(string titulo, string texto){
        this->titulo = titulo;
        this->texto = texto;
    }

    string getTitulo(){
        return titulo;
    }

    string getTexto(){
        return texto;
    }

    void setTitulo(string titulo){
        this->titulo = titulo;
    }

    void setTexto(string texto){
        this->texto = texto;
    }
};

class Usuario{
    string user;
    string password;
    vector<Nota> anotacoes;
public:
    Usuario(string user = "", string password = ""){
        this->user = user;
        this->password = password;
    }

    string getUser(){
        return user;
    }

    bool changePassword(string old, string _new){
        if(this->password == old){
            this->password = _new;
            return true;
        }
        return false;
    }

    bool addNote(Nota note){
        for(auto e : anotacoes){
            if(e.getTitulo() == note.getTitulo()){
                return false;
            }
        }
        anotacoes.push_back(note);
        return true;
    }

    bool rmNote(string titulo){
        for(int i = 0; i < (int) this->anotacoes.size(); i++){
            if(anotacoes[i].getTitulo() == titulo){
                anotacoes.erase(anotacoes.begin()+i);
                return true;
            }
        }
        return false;
    }

    bool verifyPassword(string password){
        return this->password == password;
    }

    string toString(){
        stringstream ss;
        ss << user << endl;
        for(auto e : anotacoes){
            ss << "[ " << e.getTitulo() << ":" << e.getTexto() << " ]" << endl;
        }
        return ss.str();
    }
};

class Sistema{
    vector<Usuario> usuarios;
public:
    Sistema(){

    }

    bool addUser(string login, string password){
        for(auto usuario : usuarios){
            if(usuario.getUser() == login)
                return false;
        }
        usuarios.push_back(Usuario(login, password));
        return true;
    }

    Usuario* getUser(string login, string password){
        for(auto& usuario : usuarios){
            if(usuario.getUser() == login && usuario.verifyPassword(password))
                return &usuario;
        }
        return nullptr;
    }

    string showUser(){
        stringstream ss;
        ss << "Usuários:" << endl;
        ss << "[ ";
        for(auto usuario : usuarios){
            ss << usuario.getUser() << " : ";
        }
        ss << " ]" << endl;
        return ss.str();
    }
};

class GerenciadorDeLogin{
    Usuario *current;
    //Usuario &getUse;
public:
};

class Controller{
    Sistema sist;
public:
    Controller(){

    }

    void shell(Sistema& sistema){
        string op;

        Usuario* usuario = nullptr;
        while(op != "end"){
            cin >> op;
            if(op == "help"){
                cout << "addUser _username _password\n"
                    << "changePass _oldPass _newPass\n"
                    << "addNote _titulo _texto\n"
                    << "rmNote _titulo\n"
                    << "showUsers\n"
                    << "login _username _password\n"
                    << "logout\n"
                    << "show\n";
            }
            else if(op == "addUser"){
                string nome, senha;
                cin >> nome >> senha;
                if(sist.addUser(nome, senha)){
                    cout << "success" << endl;
                }
                else{
                    cout << "fail: ja existe um usuario com este nome" << endl;
                }
            }
            else if(op == "showUsers"){
                cout << sist.showUser();
            }
            
            else if(op == "show"){
                if(usuario == nullptr){
                    cout << "fail: nao ha usuario logado" << endl;
                }
                else{
                    cout << usuario->toString() << endl;
                }
            }
            else if(op == "addNote"){
                string titulo, texto;
                cin >> titulo;
                getline(cin, texto);
                if(usuario){
                    if(usuario->addNote(Nota(titulo, texto)))
                        cout << "success" << endl;
                    else
                        cout << "fail: ja existe uma anotacao com este titulo" << endl;
                }
                else
                    cout << "fail: usuario nao esta logado" << endl;
            }
            else if(op == "rmNote"){
                string titulo;
                cin >> titulo;

                if(usuario == nullptr){
                    cout << "fail: nao ha usuario logado" << endl;
                }
                else{
                    if(usuario->rmNote(titulo))
                        cout << "success" << endl;
                    else
                        cout << "fail: anotacao nao existe" << endl;
                }
            }
            else if(op == "login"){
                string user, password;
                cin >> user >> password;
                usuario = sist.getUser(user, password);

                if(usuario == nullptr)
                    cout << "fail: falha de autenticacao" << endl;
                else
                    cout << "success" << endl;
            }


            else if(op == "logout"){
                if(usuario != nullptr){
                    usuario = nullptr;
                    cout << "success" << endl;
                }
                else{
                    cout << "fail: nao ha usuario logado" << endl;
                }
            }

            else if(op == "changePass"){
                string old, _new;
                cin >> old >> _new;
                if(usuario == nullptr)
                    cout << "fail: nao ha ninguem logado" << endl;
                else{ 
                    if(usuario->changePassword(old, _new))
                        cout << "success" << endl;
                    else
                        cout << "fail: senha invalida" << endl;
                    }
            }
            else{
                cout << "fail: comando invalido" << endl;
            }
        }
    }
};

int main(){
    Sistema sist;
    Controller c;
    c.shell(sist);
    return 0;
}