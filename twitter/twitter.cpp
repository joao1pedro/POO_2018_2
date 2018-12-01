#include <iostream>
#include <vector>
#include <sstream>
#include <algorithm>
#include <map>
using namespace std;

template <typename T>
class Repositorio{
    map<string, T> data;
public:
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

    vector<T*> getValues(){
        vector<T*> vp;
        for(auto pair : data)
            vp.push_back(pair.second);
        return vp;
    }

    string toString(){
        stringstream ss;
        for(auto pair : data)
            ss << pair.second.toString();
        return ss.str();
    }
};

class Tweet{
    int idTw;
    string username, msg;
    vector <string> likes;
public:
    Tweet(int idTw = 0, string username = "", string msg = ""){
        this->idTw = idTw;
        this->username = username;
        this->msg = msg;
    }

    void darLike(string username){
        auto it = find(likes.begin(), likes.end(), username);
        if(it == likes.end())
            likes.push_back(username);
        else
            likes.erase(it);
    }

    string toString(){
        stringstream ss;
        ss << to_string(idTw) << ": " << username << ": " << msg << endl;
        ss << "{";
        for(auto it = likes.begin(); it != likes.end(); it++){
            if(it != likes.end()-1)
                ss << (*it) << " ";
            else
                ss << (*it);
        }
        ss << "}" << endl;
        return ss.str();
    }

};

class User{
    string username;
    int naoLidos = 0;
    vector <Tweet*> timeline;
    vector <Tweet*> _myTweets;
    vector <User*> seguidores;
    vector <User*> seguindo;
public:
    User(string username  = ""){
        this->username = username;
    }

    void seguir(User* other){
        seguindo.push_back(other);
        other->seguidores.push_back(this); //
    }

    string getUnread(){
        stringstream ss;
        if(naoLidos == 0)
            throw string("fail: nao ha novos tweets");
        for(int i = 1; i <= naoLidos; i++)
            ss << timeline[(int)timeline.size()-i]->toString();
        naoLidos = 0;
        return ss.str();
    }

    string getTimeline(){
        stringstream ss;
        if(timeline.size() == 0)
            throw string("fail: nao ha tweets");
        for(auto it = timeline.end()-1; it >= timeline.begin(); it--)
            ss << (*it)->toString() << endl;
        naoLidos = 0;
        return ss.str();
    }

    string following(){
        stringstream ss;
        for(auto it = seguindo.begin(); it != seguindo.end(); it++){
            if(it != seguindo.end()-1) 
                ss << (*it)->username + " ";
            else 
                ss << (*it)->username;
        }
        return ss.str();
    }

    string followers(){
        stringstream ss;
        for(auto it = seguidores.begin(); it != seguidores.end(); it++){
            if(it != seguidores.end()-1) 
                ss << (*it)->username + " ";
            else 
                ss << (*it)->username;
        }
        return ss.str();
    }

    string toString(){
        stringstream ss;
        ss << username << endl;
        ss << " seguindo [" << following() << "]" << endl;
        ss << " seguidores [" << followers() << "]" << endl;
        return ss.str();
    }

    string myTweets(){
        stringstream ss;
        if(_myTweets.size() == 0)
            throw string("fail: nao ha tweets");
        for(auto it = _myTweets.end()-1; it >= _myTweets.begin(); it--)
            ss << (*it)->toString() << endl;
        return ss.str();
    }

    void refreshTimeline(Tweet* tw){
        _myTweets.push_back(tw);
        for(auto follow : seguidores){
            follow->timeline.push_back(tw);
            follow->naoLidos++;
        }
    }

};

class TweetGenerator{
    int nextId = 0;
    Repositorio<Tweet> *r_tw;
public:
    TweetGenerator(Repositorio<Tweet> *r_tw){
        this->r_tw = r_tw;
    }
    Tweet* create(string user, string msg){
        r_tw->add(to_string(nextId), Tweet(nextId, user, msg));
        nextId++;
        return r_tw->get(to_string(nextId-1));
    }
};

class Controller{
    Repositorio<User> *r_user;
    Repositorio<Tweet> *r_tw;
    TweetGenerator *twg;
public:
    Controller(){
        this->r_user = new Repositorio<User>;
        this->r_tw = new Repositorio<Tweet>;
        this->twg = new TweetGenerator(r_tw);
    }

    string shell(string line){
        stringstream ss(line);
        stringstream out;
        string op;
        ss >> op;

        if(op == "nwuser"){
            string name;
            ss >> name;
            r_user->add(name, User(name));
        }
        else if(op == "lauser"){
            out << r_user->toString();
        }
        else if(op == "seguir"){
            string name, other;
            ss >> name >> other;
            r_user->get(name)->seguir(r_user->get(other));
        }
        else if(op == "twittar"){
            string username, msg;
            ss >> username;
            getline(ss, msg);
            auto it = twg->create(username, msg);
            r_user->get(username)->refreshTimeline(it);
        }
        else if(op == "timeline"){
            string name;
            ss >> name;
            out << r_user->get(name)->getTimeline();
        }
        else if(op == "unread"){
            string name;
            ss >> name;
            out << r_user->get(name)->getUnread();
        }
        else if(op == "myTweets"){
            string name;
            ss >> name;
            out << r_user->get(name)->myTweets();
        }
        else if(op == "like"){
            string name, id;
            ss >> name >> id;
            r_tw->get(id)->darLike(name);
        }else if(op == "clear"){
            system("clear");
        }
        else
            out << "fail: comando invalido" << endl;
        return out.str();
    }

    void ui(){
        string line;
        while(true){
            getline(cin, line);
            if(line == "end")
                break;
            try{
                cout << shell(line);
            }catch(string e){
                cout << e << endl;
            }catch(const char* e){
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
