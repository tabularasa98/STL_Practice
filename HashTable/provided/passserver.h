#ifndef PASSSERVER_H
#define PASSSERVER_H
#include "hashtable.h"
#include <string>
#include <cstring>
#include <unistd.h>
#include <crypt.h>
using namespace std;

class PassServer{
private:
    cop4530::HashTable<string, string> HT;        //hash table to hold usernames and passwords
    string encrypt(const string& str) const;        //encrypts the parameter string
public:
    explicit PassServer(size_t size = 101);         //default constructor
    ~PassServer();                                  //destructor

    bool load(const char* filename);                    //loads file contents into hash table
    bool addUser(std::pair<string, string>& kv);        //inserts key value pair to hash table
    bool addUser(std::pair<string, string>&& kv);       //move insertion
    bool removeUser(const string & k);                  //deletes the key value pair from hash table

    bool changePassword(const pair<string, string> &p, const string & newpassword);         //changes a user's password

    bool find(const string & user);         //checks if user exists
    void dump();                            //prints the hash table

    size_t size()const;          //returns size of hash table
    size_t capacity()const;      //returns the capacity of hash table

    bool write_to_file(const char *filename);           //saves the hash table to a file


};


#include "passserver.hpp"
#endif
