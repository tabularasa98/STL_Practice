#ifndef PASSSERVER_HPP
#define PASSSERVER_HPP
#include "passserver.h"

PassServer::PassServer(size_t size){
    HT = cop4530::HashTable<string, string>(size);
}       //default constructor

PassServer::~PassServer(){
    HT.clear();
}       //destructor

bool PassServer::load(const char *filename) {
    return(HT.load(filename));
}       //loads hash table from file

bool PassServer::addUser(std::pair<string, string> &kv) {
    return(HT.insert(pair<string, string>(kv.first, encrypt(kv.second))));
}       //adds a new user

bool PassServer::addUser(std::pair<string, string> &&kv) {
    return(HT.insert(pair<string, string>(move(kv.first), encrypt(move(kv.second)))));
}       //move version to add user

bool PassServer::removeUser(const string &k) {
    return(HT.remove(k));
}       //deletes user if matching key is found

bool PassServer::changePassword(const pair<string, string> &p, const string &newpassword) {
    if(!(HT.contains(p.first))){
        return false;
    }
    if(!(HT.match(pair<string, string>(p.first, encrypt(p.second))))){
        return false;
    }else{
        return(HT.insert(pair<string, string>(p.first, encrypt(newpassword))));
    }
}       //changes password if pair is correct and new password is different

bool PassServer::find(const string &user) {
    return(HT.contains(user));
}           //finds if a user exists in the hash table

void PassServer::dump() {
    HT.dump();
}       //displays hash table

size_t PassServer::size()const {
    return HT.size();
}       //outputs the current size

size_t PassServer::capacity() const {
    return HT.capacity();
}       //outputs the capacity

bool PassServer::write_to_file(const char *filename) {
    return(HT.write_to_file(filename));
}       //writes hash table toa file

string PassServer::encrypt(const string &str) const {
    char salt[] = "$1$########";
    char * password = new char [100];
    string tempPass;
    strcpy(password, crypt(str.c_str(),salt));
    tempPass = password;
    delete [] password;
    return(tempPass.substr(12,22));
}       //encrypts given password
#endif