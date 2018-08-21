#include <iostream>
#include <sstream>
#include <vector>

using namespace std;

struct Cliente{
    string id;
    string fone;
    int *existe;
   // bool existe;

    Cliente(string id = "fulano", string fone = "0000", int *existe = nullptr){
        this->id = id;
        this->fone = fone;
        this->existe = existe;
    }

    string toString(){
        stringstream ss;

        if(this->existe == nullptr){
            ss << "-";
        }else {
            ss << this->id << ":" << this->fone;
        }
        return ss.str();
    }
};

struct Sala{
    vector<Cliente*> cadeiras;

    Sala(int qtd = 0){
        for(int i = 0; i < qtd; i++){
            cadeiras.push_back(new Cliente("", "", nullptr));
        }
    }

    string toString(){
        stringstream ss;

        ss << "[";
        for(Cliente *cliente : cadeiras)
            ss << cliente->toString() << " ";
        ss << "]";
        return ss.str();
        
    }

    bool reservar(Cliente *cliente, int ind){
        int qtd = cadeiras.size();

        if((ind < 0) || (ind >= qtd)){
            cout << "fail: essa cadeira nao existe" << endl;
            return false;
        }else if(cadeiras[ind]->existe != nullptr){
                cout << "fail: essa cadeira ja esta ocupada" << endl;
                return false;
        }
        for(int i = 0; i < qtd; i++){
            if((cadeiras[i]->existe != nullptr) && (cadeiras[i]->id == cliente->id)){
                cout << "fail: voce ja esta no cinema" << endl;
                return false;
            }
        }
        cadeiras[ind] = new Cliente;
        return true;
    }

    bool cancelar(string idPessoa){
        for(int i = 0; i < (int) cadeiras.size(); i++)
        {
            if((cadeiras[i]->existe) && (idPessoa == cadeiras[i]->id)){
                cadeiras[i]->id = "-";
                cadeiras[i]->fone = "";
                cadeiras[i]->existe = nullptr;
                return true;
            }
         } 
         cout << "fail: " << idPessoa << " nao esta no cinema" << endl;
         return false;
    }
    
};

int main(){
    Sala sala;
    string op;
while(true){
    cin >> op;
    if(op == "show"){
        cout << sala.toString() << endl;
    }
    else if(op == "init"){
        int qtd;
        cin >> qtd;
        sala = Sala(qtd);
        cout << "sala criada com " << qtd << " cadeiras" << endl;
    }
    else if(op == "reservar"){
        Cliente cliente;
        string id, fone;
        int ind;
        //int *existe;
        
        cin >> id >> fone >> ind;
        //if(sala.reservar(new (Cliente), ind))
        cliente.id = id;
        cliente.fone = fone;
        if((sala.reservar(&cliente, ind)))
            cout << "done" << endl;
    }
    else if(op == "cancelar"){
        string idPessoa;
        cin >> idPessoa;

        if(sala.cancelar(idPessoa))
            cout << "done" << endl;
    }
    else if(op == "help"){
        cout << "show; help; init _; reservar _nome _fone _cadeira; cancelar; _nome; limpar; sair";
    }
    else if(op == "limpar"){
        system("clear");
    }
    else if(op == "sair"){
        break;
    }
}
    return 0;
}
