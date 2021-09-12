#ifndef HASHTABLE_H
#define HASHTABLE_H
#include <algorithm>
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>
#include <list>

namespace cop4530 {

    template <typename K, typename V>
    class HashTable{
    private:
        std::vector<std::list<std::pair<K, V>>> theLists;      //vector of lists
        int currentsize;

        static const unsigned int max_prime = 1301081;      //constant for prime number functions

        void makeEmpty();                                           //deletes elements in hash table
        void rehash();                                              //grows the vector when elements exceed vector size
        size_t myhash(const K& k) const;                            //returns index for where key should be stored
        unsigned long prime_below (unsigned long n);                //finds largest prime number for vector size
        void setPrimes(std::vector<unsigned long>& vprimes);        //fills in prime numbers
    public:
        explicit HashTable(size_t size = 101);       //default constructor
        ~HashTable();                           //destructor

        bool contains(const K& k) const;      //checks if key is in hash table
        bool match(const std::pair<K,V>& kv) const;        //checks if key value pair is in hash table
        size_t size() const;                               //returns the size of the Hash Table
        size_t capacity() const;                           //return the capacity of the Hash Table

        bool insert(const std::pair<K,V>& kv);      //inserts key value pair to hash table
        bool insert(std::pair<K,V>&& kv);           //move insertion

        bool remove(const K& k);        //deletes the key value pair from hash table
        void clear();                   //deletes all elements in hash table

        bool load(const char* filename);        //loads file contents into hash table

        void dump() const;                                      //displays entries in hash table
        bool write_to_file(const char* filename) const;         //writes hash table to a file


    };




    #include "hashtable.hpp"
}       //end of namespace cop4530
#endif
