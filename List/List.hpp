#ifndef DL_LIST_HPP
#define DL_LIST_HPP
#include "List.h"
template <typename T>
cop4530::List<T>::const_iterator::const_iterator() {
    current = nullptr;
}       //const_iterator default constructor
template <typename T>
const T & cop4530::List<T>::const_iterator:: operator*() const {
    return retrieve();
}       //dereferences const_iterator
template <typename T>
 typename cop4530::List<T>::const_iterator & cop4530::List<T>::const_iterator::operator++() {
    current = current->next;
    return *this;
}       //prefix incrementer
template <typename T>
typename cop4530::List<T>::const_iterator cop4530::List<T>::const_iterator::operator++(int) {
    const_iterator old = *this;
    ++(*this);
    return old;
}       //postfix incrementer
template <typename T>
typename cop4530::List<T>::const_iterator & cop4530::List<T>::const_iterator::operator--() {
    current = current->prev;
    return *this;
}       //prefix decrementer
template <typename T>
typename cop4530::List<T>::const_iterator cop4530::List<T>::const_iterator::operator--(int) {
    const_iterator old = *this;
    --(*this);
    return old;
}       //postfix decrementer
template <typename T>
bool cop4530::List<T>::const_iterator::operator==(const const_iterator &rhs) const {
    return current == rhs.current;
}       //equality comparison
template <typename T>
bool cop4530::List<T>::const_iterator::operator!=(const const_iterator &rhs) const {
    return !(*this == rhs);
}       //inequality comparison
template <typename T>
T & cop4530::List<T>::const_iterator::retrieve() const {
    return current->data;
}       //node data getter
template <typename T>
cop4530::List<T>::const_iterator::const_iterator(Node *p) {
    current = p;
}       //parameterized constructor for passing a Node
template <typename T>
    cop4530::List<T>::iterator::iterator() {}       //iterator default constructor
template <typename T>
T & cop4530::List<T>::iterator::operator*() {
    return const_iterator::retrieve();
}       //dereferences the iterator
template <typename T>
const T & cop4530::List<T>::iterator::operator*() const {
    return const_iterator::operator*();
}       //dereferences the iterator at const data type
template <typename T>
typename cop4530::List<T>::iterator & cop4530::List<T>::iterator::operator++(){
    this->current = this->current->next;
    return *this;
}       //prefix incrementer
template <typename T>
typename cop4530::List<T>::iterator cop4530::List<T>::iterator::operator++(int){
    iterator old = *this;
    ++( *this );
    return old;
}       //postfix incrementer
template <typename T>
typename cop4530::List<T>::iterator & cop4530::List<T>::iterator::operator--(){
    this->current = this->current->prev;
    return *this;
}       //prefix decrementer
template <typename T>
typename cop4530::List<T>::iterator cop4530::List<T>::iterator::operator--(int){
    iterator old = *this;
    --( *this );
    return old;
}       //postfix decrementer
template <typename T>
cop4530::List<T>::iterator::iterator(Node *p) {
   this->current = p;
}       //parameterized constructor for passing in a Node
template <typename T>
cop4530::List<T>::List() {
    init();
}       //default List constructor
template <typename T>
cop4530::List<T>::List(const List<T> &rhs) {
    init();
    for (auto & x: rhs){
        push_back(x);
    }
}       //copy constructor
template <typename T>
cop4530::List<T>::List(List<T> &&rhs) {
    theSize = rhs.theSize;
    head = rhs.head;
    tail = rhs.tail;
    rhs.theSize = 0;
    rhs.tail = nullptr;
    rhs.head = nullptr;
}       //move constructor
template <typename T>
cop4530::List<T>::List(int num, const T &val) {
    init();     //sets default values
    for(int i = 0; i < num; i++){
        push_back(val);     //adds nodes to the list with the value num times
    }
}       //constructor for filling list with the same value
template <typename T>
cop4530::List<T>::List(const_iterator start, const_iterator end) {
    init();     //sets default values
    for(const_iterator itr = start; itr != end; itr++){
        push_back(*itr);        //iterates within the specified range copying values
    }
}       //constructor for copying from another list given a [start,end) iterators
template <typename T>
cop4530::List<T>::List(std::initializer_list<T> iList) {
    init();     //sets default values
    for(auto x: iList){
        push_back(x);       //goes through initializer list adding each value
    }
}       //initialization list constructor
template <typename T>
cop4530::List<T>::~List() {
    clear();
    delete head;
    delete tail;
}       //destructor
template <typename T>
const cop4530::List<T> & cop4530::List<T>::operator=(const List<T> &rhs) {
    List copy = rhs;
    std::swap(*this, copy);
    return *this;
}       //copy assignment operator
template <typename T>
cop4530::List<T> & cop4530::List<T>::operator=(List<T> &&rhs) {
    std::swap( theSize, rhs.theSize );
    std::swap( head, rhs.head );
    std::swap( tail, rhs.tail );
    return *this;
}       //move assignment operator
template <typename T>
cop4530::List<T> & cop4530::List<T>::operator=(std::initializer_list<T> iList) {
    clear();        //clears list
    for(auto x: iList){
        push_back(x);       //adds node for each value in list
    }
    return *this;       //returns the list
}       //initialization list assignment operator
template <typename T>
int cop4530::List<T>::size() const {
    return theSize;
}       //size getter
template <typename T>
bool cop4530::List<T>::empty() const {
    return size() == 0;
}       //checks if list is empty
template <typename T>
void cop4530::List<T>::clear() {
    while(!empty())
        pop_front();
}       //clears all nodes form list
template <typename T>
void cop4530::List<T>::reverse() {
    for(iterator itr = begin(); itr != end(); itr--){       //iterates through list
        std::swap(itr.current->next,itr.current->prev);     //swaps each nodes next and previous pointers
    }
    std::swap(tail->prev, head->next);      //swaps the head and tail so they point to the reversed nodes
    std::swap(tail->prev->next, head->next->prev);      //swaps the first and last nodes pointer to the head and tail
}
template <typename T>
T& cop4530::List<T>::front() {
    return *begin();
}       //returns first node's data reference
template <typename T>
const T& cop4530::List<T>::front() const {
    return *begin();
}       //returns first node's data reference if const
template <typename T>
T& cop4530::List<T>::back() {
    return *--end();
}       //returns last node's data reference
template <typename T>
const T& cop4530::List<T>::back() const {
    return *--end();
}       //returns last node's data reference if const
template <typename T>
void cop4530::List<T>::push_front(const T &val) {
    insert(begin(),val);
}       //adds node to the front of the list
template <typename T>
void cop4530::List<T>::push_front(T &&val) {
    insert(begin(), std::move(val));
}       //move adds node to the front of the list
template <typename T>
void cop4530::List<T>::push_back(const T &val) {
    insert(end(),val);
}       //adds node to the back of the list
template <typename T>
void cop4530::List<T>::push_back(T &&val) {
    insert(end(), std::move(val));
}       //move adds node to the back of the list
template <typename T>
void cop4530::List<T>::pop_front() {
    erase(begin());
}       //removes node from front of list
template <typename T>
void cop4530::List<T>::pop_back() {
    erase(--end());
}       //removes node from end of the list
template <typename T>
void cop4530::List<T>::remove(const T &val) {
    for(iterator itr = begin(); itr!= end();){
        if(*itr == val){        //checks if val matches node data
            itr = erase(itr);       //moves iterator and erases node
        }else{
            itr++;      //moves the iterator
        }
    }
}       //removes all nodes with data equal to val
template <typename T>
template <typename PREDICATE>
void cop4530::List<T>::remove_if(PREDICATE pred) {
    for(iterator itr = begin(); itr!= end();){
        if(pred(*itr)){     //checks if functor returns true
            itr = erase(itr);       //moves iterator and erases node
        }else{
            itr++;      //moves the iterator
        }
    }
}       //functor version of remove operator
template <typename T>
void cop4530::List<T>::print(std::ostream &os, char ofc) const {
    for(const_iterator itr = begin(); itr!= end(); itr++){      //iterates through list
        if(itr == --end()){
            os << *itr;         //if the node it the last node, doesnt include deliminator
        }else{
            os << *itr << ofc;      //outputs node
        }
    }
}       //prints all nodes in list with given deliminator
template <typename T>
typename cop4530::List<T>::iterator cop4530::List<T>::begin() {
    return iterator(head->next);
}       //returns iterator to first node
template <typename T>
typename cop4530::List<T>::const_iterator cop4530::List<T>::begin() const {
    return const_iterator(head->next);
}       //returns const_iterator to first node
template <typename T>
typename cop4530::List<T>::iterator cop4530::List<T>::end() {
    return iterator(tail);
}       //returns iterator to tail node
template <typename T>
typename cop4530::List<T>::const_iterator cop4530::List<T>::end() const {
    return const_iterator(tail);
}       //returns const_iterator to tail node
template <typename T>
typename cop4530::List<T>::iterator cop4530::List<T>::insert(iterator itr, const T& val) {
    Node *p = itr.current;
    ++theSize;
    return iterator( p->prev = p->prev->next = new Node{ val, p->prev, p } );
}       //adds node after specified location with data val, returns at old node
template <typename T>
typename cop4530::List<T>::iterator cop4530::List<T>::insert(iterator itr, T&& val) {
    Node *p = itr.current;
    ++theSize;
    return iterator( p->prev = p->prev->next = new Node{ std::move(val), p->prev, p } );
}       //move version of insertion
template <typename T>
typename cop4530::List<T>::iterator cop4530::List<T>::erase(iterator itr) {
    Node *p = itr.current;
    iterator retVal( p->next );
    p->prev->next = p->next;
    p->next->prev = p->prev;
    delete p;
    --theSize;
    return retVal;
}       //removes a node at iterator and returns at the next node
template <typename T>
typename cop4530::List<T>::iterator cop4530::List<T>::erase(iterator start, iterator end) {
    for( iterator itr = start; itr != end; )
        itr = erase( itr );
    return end;
}       //moves nodes between iterators in [start,end) way, returns at end node
template <typename T>
void cop4530::List<T>::init() {
    theSize = 0;
    head = new Node;
    tail = new Node;
    head->next = tail;
    tail->prev = head;
}       //initializes List properties
template <typename T>
bool operator==(const cop4530::List<T> &lhs, const cop4530::List<T> &rhs) {
    bool flag = true;
    typename cop4530::List<T>::const_iterator ritr = rhs.begin();       //iterator for rhs List
    if(lhs.size() != rhs.size()){
        return false;           //returns false if the lists aren't the same size
    }else{
        for(typename cop4530::List<T>::const_iterator litr = lhs.begin(); litr != lhs.end(); litr++){
            if(*litr != *ritr){
                flag = false;
                break;          //returns false and breaks loop if node pair data isn't equal
            }else{
                ritr++;         //increments rhs iterator
            }
        }
        return flag;
    }
}           //overloaded comparison operator
template <typename T>
bool operator!=(const cop4530::List<T> &lhs, const cop4530::List<T> &rhs) {
    return !(lhs == rhs);       //negation of equality
}           //overloads comparison operator for inequality
template <typename T>
std::ostream & operator<<(std::ostream &os, const cop4530::List<T> &l) {
    l.print(os);
    return os;
}       //overloads insertion operator to print List and return output stream
#endif