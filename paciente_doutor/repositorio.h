#pragma once
#include <iostream>
#include <map>
#include <algorithm>
#include <vector>
using namespace std;

template <typename T>
class Repositorio{
    map <string, T> data;
    string _typename;
public:
    Repositorio(string _typename = ""){
        this->_typename = _typename;
    }

    void add(string key, T elem){
        if(data.count(key) != 0)
            throw string("fail: " + key + " ja existe");
        data[key] = elem;
    }

    void rm(string key){
        if(data.count(key) == 0)
            throw string("fail: " + key + " nao existe");
        data.erase(key);
    }

    bool exists(string key){
        return data.count(key) != 0;
    }

    T* get(string key){
        if(!exists(key))
            throw string("fail: " + key + " nao existe");
        return &data[key];
    }

    vector<T> getValues(){
        vector<T> vp;
        for(auto pair : data)
            vp.push_back(pair.second);
        return vp;
    }

};