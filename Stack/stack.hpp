#ifndef STACK_HPP
#define STACK_HPP
#include "stack.h"

template <typename T>
cop4530::Stack<T>::Stack(){}        //default constructor
template <typename T>
cop4530::Stack<T>::~Stack(){}       //destructor
template <typename T>
cop4530::Stack<T>::Stack(const Stack<T> &rhs) {
    l = rhs.l;
}       //copy constructor
template <typename T>
cop4530::Stack<T>::Stack( Stack<T> &&rhs) {
    std::list<T> temp;
    l = rhs.l;
    rhs.l = temp;
}       //move constructor
template <typename T>
cop4530::Stack<T> & cop4530::Stack<T>::operator=(const Stack<T> &rhs) {
    Stack copy = rhs;
    std::swap(*this, copy);
    return *this;
}       //copy assignment operator
template <typename T>
cop4530::Stack<T> & cop4530::Stack<T>::operator=(Stack<T> && rhs) {
    std::swap(l, rhs.l);
    return *this;
}       //move assignment operator
template <typename T>
bool cop4530::Stack<T>::empty() const {
    return l.empty();
}       //returns whether the stack is empty
template <typename T>
void cop4530::Stack<T>::clear() {
    l.clear();
}       //clears the stack
template <typename T>
void cop4530::Stack<T>::push(const T& x) {
    l.push_back(x);
}       //adds new value to the stack copy
template <typename T>
void cop4530::Stack<T>::push(T &&x) {
    l.push_back(x);
}       //adds new value to the stack move
template <typename T>
void cop4530::Stack<T>::pop() {
    l.pop_back();
}       //removes value from stack
template <typename T>
T& cop4530::Stack<T>::top() {
    return l.back();
}       //returns value at top of stack
template <typename T>
const T& cop4530::Stack<T>::top() const {
    return l.back();
}       //returns const reference to value at top of stack
template <typename T>
int cop4530::Stack<T>::size() const {
    return l.size();
}       //returns size of stack
template <typename T>
void cop4530::Stack<T>::print(std::ostream &os, char ofc) const{
    for(auto itr = std::begin(l); itr!= std::end(l); itr++){
        if(itr == --end(l)){
            os << *itr;         //if the node it the last node, doesnt include deliminator
        }else{
            os << *itr << ofc;      //outputs node
        }
    }
}       //prints all the elements in stack separated by deliminator
template <typename T>
std::ostream& operator<< (std::ostream& os, const cop4530::Stack<T>& a){
    a.print(os);
    return os;
}       //overloads extraction operator
template <typename T>
bool operator== (const cop4530::Stack<T>& lhs, const cop4530::Stack <T>& rhs){
    bool flag = true;
    cop4530::Stack<T> clhs = lhs, crhs = rhs;
    if(lhs.size() != rhs.size()){
        return false;
    }else{
        while(!clhs.empty()){
            if(clhs.top() != crhs.top()){
                flag = false;
                break;
            }else{
                clhs.pop();
                crhs.pop();
            }
        }
        return flag;
    }
}       //overloads equality comparison
template <typename T>
bool operator !=(const cop4530::Stack<T>& lhs, const cop4530::Stack<T>& rhs){
    return !(lhs == rhs);
}       //overloads inequality comparison
template <typename T>
bool operator<= (const cop4530::Stack<T>& lhs, const cop4530::Stack<T>& rhs){
    bool flag = true;
    cop4530::Stack<T> clhs = lhs, crhs = rhs;
    if(lhs.size() > rhs.size()){
        return false;
    }else{
        while(!clhs.empty()){
            if(clhs.top() <= crhs.top()){
                clhs.pop();
                crhs.pop();
            }else{
                flag = false;
                break;
            }
        }
        return flag;
    }
}       //compares each element to see if its less than ofr equal to corresponding element in other stack

#endif
