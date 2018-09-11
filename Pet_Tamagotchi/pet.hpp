#ifndef PET_H
#define PET_H

#include <iostream>
#include <sstream>
using namespace std;

class Pet{
private:
    string nome;
    int energyMax, hungryMax, cleanMax; 
    int energy, hungry, clean;   
    int age; // {0};
    int diamond; // {0};
    bool alive {true};


public:
    Pet(string nome = "pet", int energyMax = 0, int hungryMax = 0, int cleanMax = 0);
    
    string getNome();  //declaracao
    void setNome(string nome){
        this->nome = nome;
    }
    int getEnergyMax(){
        return energyMax;
    }
    int getHungryMax(){
        return hungryMax;
    }
    int getCleanMax(){
        return cleanMax;
    }
    int getAge();

    string toString(){
        stringstream ss;
        ss << "N:" << nome << ", " 
           << "E:" << energy << "/" << energyMax << ", "
           << "H:" << hungry << "/" << hungryMax << ", "
           << "C:" << clean  << "/" << cleanMax  << ", "
           << "D:" << diamond << ", A:" << age;
        return ss.str();
    }

    void setEnergy(int value){
        if(value <= 0){
            this->alive = false;
            value = 0;
        }else if(value > energyMax){
            value = energyMax;
        }else
            energy = value;
    }

    bool testAlive(){
        if(alive)
            return true;
        cout << "fail: pet esta morto" << endl;
        return false;
    }

    void setHungry(int value){
        if(value <= 0){
            this->alive = false;
            value = 0;
        }else if(value > hungryMax){
            value = hungryMax;
        }else
            hungry = value;
    }

    void setClean(int value){
        if(value <= 0){
            this->alive = false;
            value = 0;
        }else if(value > cleanMax){
            value = cleanMax;
        }else
            clean = value;
    }

    void setAge(int value){
            age = age + value;
    }

    void setDiamond(int value){
            diamond = diamond + value;
    }

    void play(){
        if(!testAlive())
            return;
        setHungry(hungry-1);
        setEnergy(energy-2); //energy
        setClean(clean-3); // hungry
        setAge(1); // age
        setDiamond(1); // diamound
    }

    void eatPet(){
        if(!testAlive())
            return;
        setHungry(hungry+4);
        setEnergy(energy-1); //energy
        setClean(clean-2); // hungry
        setAge(1); // age
    }

    void sleepPet(){
        if(!testAlive())
            return;
        if((energyMax - energy) > 5){
            setHungry(hungry-1);
            setEnergy(energyMax);
            setAge(1);
        }
        else {
            cout << "fail: nao esta com sono" << endl;
        }
    }

    void cleanPet(){
        setHungry(hungry-1);
        setEnergy(energy-3); 
        setClean(cleanMax); 
        setAge(2);
    }

    void updateNome(string nome){
        this->nome = nome;
    }
};

struct Controller{
    Pet p;
    string shell(string line){
        stringstream ui(line);
        stringstream out;
        string op;
        ui >> op;

        if(op == "show"){
            out << p.toString();
        }
        else if(op == "help"){
            out << "show; init _energy _hungry _clean; play; eat; sleep; clean; name _newName";
        }
        else if(op == "init"){
            int energyInit = 0, hungryInit = 0, cleanInit = 0;
            string ident;
            ui >> ident >> energyInit >> hungryInit >> cleanInit;
            p = Pet(ident, energyInit, hungryInit, cleanInit);
        }
        else if(op == "play"){
            p.play();
        }
        else if(op == "eat"){
            p.eatPet();
        }
        else if(op == "sleep"){
            p.sleepPet();
        }
        else if(op == "clean"){
            p.cleanPet();
        }
        else if(op == "name"){
            string nome;
            cin >> nome;
            p.updateNome(nome);
        }
        return out.str();
    }

    void io(){
        string line;
        while(true){
            getline(cin, line);
            if(line == "end")
                break;
            cout << shell(line) << endl;
        }
    }
};

#endif