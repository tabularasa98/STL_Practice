#ifndef HASHTABLE_HPP
#define HASHTABLE_HPP
#include "hashtable.h"

template <typename K, typename V>
cop4530::HashTable<K, V>::HashTable(size_t size) {
    theLists = std::vector<std::list<std::pair<K, V>>>(prime_below(size));
    currentsize = 0;
}       //default constructor for hash tale

template <typename K, typename V>
cop4530::HashTable<K, V>::~HashTable() {
    clear();
}       //destructor

template <typename K, typename V>
bool cop4530::HashTable<K, V>::contains(const K &k) const {
    bool flag = false;
    auto& whichList = theLists[myhash(k)];
    for(std::pair<K, V> whichPair: whichList){
        if(whichPair.first == k){
            flag = true;
        }else{}
    }
    return flag;

}       //returns if hash table contains key

template <typename K, typename V>
bool cop4530::HashTable<K, V>::match(const std::pair<K, V> &kv) const {
    auto& whichList = theLists[myhash(kv.first)];
    return std::find(begin(whichList), end(whichList), kv) != end(whichList);
}           //returns if hash table contains pair

template <typename K, typename V>
size_t cop4530::HashTable<K, V>::size() const{
    return currentsize;
}       //returns current size

template <typename K, typename V>
size_t cop4530::HashTable<K, V>::capacity()const{
    return theLists.size();
}       //returns the capacity

template <typename K, typename V>
bool cop4530::HashTable<K, V>::insert(const std::pair<K, V> &kv) {
    auto& whichList = theLists[myhash(kv.first)];
    if(match(kv)){
        return false;       //case if pair already exists
    }else{
        if(contains(kv.first)){
            for(std::pair<K, V>& whichPair: whichList){
                if(whichPair.first == kv.first){
                    whichPair.second = kv.second;       //case if key exists with different value
                }else{}
            }
        }else {
            whichList.push_back(kv);        //adds new pair
            if (++currentsize > theLists.size()) {
                rehash();       //grows vector if there are too may pairs
            }
        }
        return true;
    }
}

template <typename K, typename V>
bool cop4530::HashTable<K, V>::insert(std::pair<K, V> &&kv) {
    auto& whichList = theLists[myhash(kv.first)];
    if(match(kv)){
        return false;
    }else{
        if(contains(kv.first)){
            for(std::pair<K, V>& whichPair: whichList){
                if(whichPair.first == kv.first){
                    whichPair.second = kv.second;
                }else{}
            }
        }else {
            whichList.push_back(std::move(kv));
            if (++currentsize > theLists.size()) {
                rehash();
            }
        }
        return true;
    }
}           //move version of pair insertion

template <typename K, typename V>
bool cop4530::HashTable<K, V>::remove(const K &k) {
    if(contains(k)){
        auto& whichList = theLists[myhash(k)];
        for(std::pair<K, V> whichPair: whichList){
            if(whichPair.first == k){
                whichList.remove(whichPair);        //removes pair with matching key
                --currentsize;
                return true;
            }else{}
        }
    }else{
        return false;
    }
}

template <typename K, typename V>
void cop4530::HashTable<K, V>::clear(){
    makeEmpty();
}       //deletes all pairs

template <typename K, typename V>
bool cop4530::HashTable<K, V>::load(const char* filename){
    std::ifstream myfile (filename);
    std::string key, value,line;
    if(myfile.is_open()){
        while(getline(myfile,line)){
            line += " ";
            std::stringstream l(line);
            getline(l, key, ' ');
            getline(l, value, ' ');
            insert(std::pair<std::string, std::string>(key,value));         //inputs pairs from a file
        }
        myfile.close();
        return true;
    }else{
        std::cerr << "Error: Cannot open file " << filename << std::endl;
        return false;
    }
}

template <typename K, typename V>
void cop4530::HashTable<K, V>::dump() const {
    for(int i = 0; i < theLists.size(); i++){
        std::cout << "v[" << i << "]:";
        for(auto& tempPair: theLists[i]){
            if(tempPair == theLists[i].front()){
                std::cout << " " << tempPair.first << " " << tempPair.second;
            }else{
                std::cout << ":" << tempPair.first << " " << tempPair.second;
            }
        }
        std::cout << std::endl;
    }
}           //displays hash table in specified format

template<typename K, typename V>
bool cop4530::HashTable<K, V>::write_to_file(const char *filename) const {
    std::ofstream myfile (filename);
    if(myfile.is_open()){
        for(auto& tempList: theLists){
            for(auto& tempPair: tempList){
                myfile << tempPair.first << " " << tempPair.second << std::endl;
            }
        }
        myfile.close();
        return true;
    }else{
        return false;
    }
}           //outputs hash table to a file

template <typename K, typename V>
void cop4530::HashTable<K, V>::makeEmpty() {
    for(auto & thisList : theLists){
        thisList.clear();
    }
}           //clears each list

template <typename K, typename V>
void cop4530::HashTable<K,V>::rehash() {
    std::vector<std::list<std::pair<K, V>>> old = theLists;
    theLists.resize(prime_below(2*theLists.size()));
    for(auto& tempList: theLists){
        tempList.clear();
    }
    currentsize = 0;
    for(auto& tempList: old){
        for(auto& tempPair: tempList){
            insert(std::move(tempPair));
        }
    }
}           //grows the vector and rehashes each stored pair

template <typename K, typename V>
size_t cop4530::HashTable<K, V>::myhash(const K& k) const{
    static std::hash<K> hf;
    return hf(k) % theLists.size();
}       //uses hash functor to locate proper index

template <typename K, typename V>
unsigned long cop4530::HashTable<K, V>::prime_below (unsigned long n)
{
  if (n > max_prime)
    {
      std::cerr << "** input too large for prime_below()\n";
      return 0;
    }
  if (n == max_prime)
    {
      return max_prime;
    }
  if (n <= 1)
    {
		std::cerr << "** input too small \n";
      return 0;
    }

  std::vector <unsigned long> v (n+1);
  setPrimes(v);
  while (n > 2)
    {
      if (v[n] == 1)
	return n;
      --n;
    }

  return 2;
}

template <typename K, typename V>
void cop4530::HashTable<K, V>::setPrimes(std::vector<unsigned long>& vprimes)
{
  int i = 0;
  int j = 0;

  vprimes[0] = 0;
  vprimes[1] = 0;
  int n = vprimes.capacity();

  for (i = 2; i < n; ++i)
    vprimes[i] = 1;

  for( i = 2; i*i < n; ++i)
    {
      if (vprimes[i] == 1)
        for(j = i + i ; j < n; j += i)
          vprimes[j] = 0;
    }
}
#endif
