#ifndef FONE_H
#define FONE_H

#include <iostream>
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

#endif //FONE_H