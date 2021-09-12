#ifndef BET_H
#define BET_H
#include <iostream>
#include <string>
#include <stack>
#include <sstream>
#include <cctype>
using namespace std;

class BET{
    private:
        //nested BinaryNode structure
        struct BinaryNode {
            string element;         //element in node
            BinaryNode* left;       //pointer to left node
            BinaryNode* right;      //pointer to right node

            BinaryNode(const string & e = string{}, BinaryNode* l = nullptr, BinaryNode* r = nullptr)
                : element{e}, left{l}, right{r} {}              //BinaryNode constructor
            BinaryNode( string && e, BinaryNode* l = nullptr, BinaryNode* r = nullptr)
                : element{move(e)}, left{l}, right{r} {}        //move BinaryNode constructor
        };

    public:
        BET();      //default constructor
        BET(const string& postfix);     //postfix constructor
        BET(const BET& rhs);            //copy constructor
        ~BET();     //destructor

        bool buildFromPostfix(const string& postfix);       //creates BET from postfix string
        const BET& operator= (const BET& rhs);              //copy assignment operator

        void printInfixExpression() const;          //prints the BET in infix format
        void printPostfixExpression() const;        //prints the BET in postfix format

        size_t size() const;             //returns number of nodes in BET
        size_t leaf_nodes() const;       //returns number of leaf nodes in BET
        bool empty() const;              //returns if BET is empty

    private:
        BinaryNode* root;       //pointer to BET root node

        void printInfixExpression(BinaryNode* n) const;         //recursive infix print function
        void printPostfixExpression(BinaryNode* n) const;       //recursive postfix print function

        void makeEmpty(BinaryNode*& t);         //recursive node delete function
        BinaryNode* clone(BinaryNode* t);       //recursive clone function

        size_t size(BinaryNode* t) const;           //recursive size function
        size_t leaf_nodes(BinaryNode* t) const;     //recursive leaf node function

        int prec(char c) const;         //operator precedence function
};
#include "bet.hpp"

#endif
