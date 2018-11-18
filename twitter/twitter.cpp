#include <iostream>
#include <sstream>
#include <map>
#include <algorithm>
#include <list>
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
        if(data.cout(key) == 0)
            throw string("fail: " + key + " nao existe");
        data.erase(key);
    }

    bool exists(string key){
        return data.count(key) != 0;
    }

    T& get(string key){
        if(!exists(key))
            throw string("fail: " + key + " nao existe");
        return data[key];
    }

    vector<T> getValues(){
        vector<T> vp;
        for(auto pair : data)
            vp.push_back(pair.second);
        return vp;
    }

};

class Tweet{
    int idTweet;
    string username;
    string msg;
    list<string> likes;
public:
    Tweet(int idTweet = 0, string username = "", string msg = ""){
        this->idTweet = idTweet;
        this->username = username;
        this->msg  = msg;
    }

    void like(string username){
        for(auto elem : likes)
            if(elem == username){
                throw string("fail: " + username + " nao pode curtir novamente");
            }
        likes.push_back(username);
    }

    string toString(){
        stringstream ss;
        ss << "id: " + to_string(idTweet) << 
        " username: " << username << 
        " mensagem: " << msg;
        if((int)likes.size() > 0){
            ss << "{ ";
            for(auto elem : likes)
                ss << elem << " ";
            ss << " }";
        }
        return ss.str();
    }

    string getUsername(){
        return username;
    }

    int getIdTweet(){
        return idTweet;
    }

    string getMsg(){
        return msg;
    }

};

class User{
    string username;
    list<User*> seguidores;
    list<User*> seguindo;
    list<Tweet*> meusTweets;
    list<Tweet*> timeline;
    int unreadCount;
    static int nextTw;
public:
    User(string username = ""){
        this->username = username;
    }

    string getUser(){
        return username;
    }

    void follow(User *user){
        for(auto elem : seguindo){
            if(elem->username == user->getUser())
                throw string("fail: voce nao pode seguir " + username + " novamente");
        }
            seguindo.push_back(user);
            user->seguindo.push_back(this);
    }

    void twittar(Tweet *t){
        meusTweets.push_front(t);
        for(User *user : seguidores){
            user->unreadCount += 1;
            user->timeline.push_front(t);
        }
    }

    list<Tweet*> unread(){
        list<Tweet*> listUnread;
        auto it = timeline.begin();
        for(int i = 0; i < unreadCount; i++, it++)
            listUnread.push_back(*it);
        unreadCount = 0;
        return listUnread;
    }

    list<Tweet*> getTimeline(){
        unreadCount = 0;
        return timeline;
    }

    list <Tweet*> getMyTw(){
        return meusTweets;
    }
};

class Controller{
    Repositorio<User> repUser;
    Repositorio<Tweet> repTweet;
    int nextID;
public:
    Controller():
        repUser(), repTweet(){

        }
    
    string laUser(){
        vector<User> laUser = repUser.getValues();
            stringstream ss;
            ss << "[ ";
            for(auto e : laUser)
                ss << e.getUser() << " ";
            ss << " ]";
        return ss.str();
    }

    string showTimeline(string key){
        list<Tweet*> timeline = repUser.get(key).getTimeline();
            stringstream ss;
            ss << "timeline: " << key << endl;
            for(auto e : timeline)
                ss << e->toString() << endl;
            return ss.str();
    }

    string showMyTweets(string key){
        list<Tweet*> tw = repUser.get(key).getMyTw();
            stringstream ss;
            for(auto e :  tw)
                ss << e->toString() << endl;
        return ss.str();
    }
    
    string shell(string line){
        stringstream ui(line);
        stringstream out;
        string op;
        ui >> op;
        if(op == "help"){
            out << "nwuser _name" << endl
            << "lauser" << endl
            << "seguir _user _otherUser" << endl
            << "twittar _user _text" << endl
            << "timeline _user" << endl
            << "myTweets _user" << endl
            << "unread _user" << endl
            << "like _user _idTw" << endl
            << "clear" << endl
            << "end" << endl;
        }else if(op == "nwuser"){
            string key;
            ui >> key;
            repUser.add(key, User(key));
            out << "success\n";
        }else if(op == "lauser"){
            out << laUser() << endl;
        }else if(op == "seguir"){
            string key;
            string otherUser;
            ui >> key >> otherUser;
            repUser.get(key).follow(&repUser.get(otherUser));
            out << "success\n";
        }else if(op == "timeline"){
            string key;
            ui >> key;
            out << showTimeline(key) << endl;
        }else if(op == "myTweets"){
            string key;
            ui >> key;
            out << showMyTweets(key) << endl;
        }else if(op == "like"){
            string key;
            int idT;
            ui >> key >> idT;
            repTweet.get(key).like(key);
            out << "success\n";
        }else if(op == "twittar"){
            string texto;
            string user;
            int id = nextID;
            nextID +=1;
            repTweet.add(to_string(id), Tweet(id, user, texto));
        }else if(op == "clear"){
            system("clear");
        }
        /* else if(op == "unread"){
            string key;
            ui >> key;
        } */
        else{
            out << "fail: comando invalido";
        }
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
            }
        }
    }
};

int main(){
    Controller c;
    c.ui();
    return 0;
}
