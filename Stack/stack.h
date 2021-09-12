#ifndef STACK_H
#define STACK_H
#include <iostream>
#include <list>

namespace cop4530{

    template <typename T>
    class Stack{
    private:
        std::list<T> l;
    public:
        Stack();        //default constructor
        ~Stack();       //destructor

        Stack(const Stack<T>& rhs);         //copy constructor
        Stack(Stack<T> && rhs);             //move constructor

        Stack<T>& operator=(const Stack<T>& rhs);           //copy assignment operator
        Stack<T>& operator=(Stack<T> && rhs);               //move assignment operator

        bool empty() const;         //checks if stack is empty
        void clear();               //removes all elements from stack

        void push(const T& x);      //adds element to stack copy version
        void push(T && x);          //adds element to stack move version
        void pop();                 //removes element from stack

        T& top();                   //returns reference to top element
        const T& top()const;        //returns constant reference to top element

        int size() const;           //returns the size of the stack
        void print(std::ostream& os, char ofc = ' ') const;       //prints the stack
    };

    template <typename T>
    std::ostream& operator<< (std::ostream& os, const Stack<T>& a);      //overloads extraction operator to print stack

    template <typename T>
    bool operator== (const Stack<T>& lhs, const Stack <T>& rhs);        //overloads equality comparison operator

    template <typename T>
    bool operator!= (const Stack<T>& lhs, const Stack <T>& rhs);        //overloads inequality comparison operator

    template <typename T>
    bool operator<= (const Stack<T>& lhs, const Stack <T>& rhs);        //overloads less than or equal to comparison operator

    #include "stack.hpp"
}       //end of namespace cop45
#endif
