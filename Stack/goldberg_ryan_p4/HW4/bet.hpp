#ifndef BET_HPP
#define BET_HPP
#include "bet.h"

BET::BET() {
    root = nullptr;
}       //default constructor creates empty BET

BET::BET(const string& postfix) {
    root = nullptr;
    if (buildFromPostfix(postfix)) {
        stack<BinaryNode *> S;
        string post = postfix, token;
        BinaryNode *l, *r, *tor, *rand;
        post += " $";
        stringstream inp(post);
        getline(inp, token, ' ');
        while (token != "$") {
            if (isalnum(token[0])) {
                rand = new BinaryNode(token);
                S.push(rand);
            } else {
                r = S.top();
                S.pop();
                l = S.top();
                S.pop();
                tor = new BinaryNode(token, l, r);
                S.push(tor);
            }
        getline(inp, token, ' ');
        }
        if (S.size() == 1) {
            root = S.top();
        }
    }
}

BET::BET(const BET& rhs) {
    root = clone(rhs.root);
}

BET::~BET() {
    makeEmpty(root);
}


bool BET::buildFromPostfix(const string &postfix) {
    stack<BinaryNode*> S;
    string post = postfix, token;
    BinaryNode *l,*r, *tor,*rand;
    post += " $";
    stringstream inp(post);
    makeEmpty(root);
    getline(inp, token, ' ');
    while(token != "$"){
        if(isalnum(token[0])){
            rand = new BinaryNode(token);
            S.push(rand);
        }else{
            if(S.size() < 2){
                cout << "here";
                cout << "Wrong postfix expression" << endl;
                return false;
            }else{
                r = S.top();
                S.pop();
                l = S.top();
                S.pop();
                tor = new BinaryNode(token,l,r);
                S.push(tor);
            }
        }
        getline(inp, token, ' ');
    }
    if(S.size() > 1){
        cout << "Wrong postfix expression" << endl;
        return false;
    }
    if(S.size() == 1) {
        root = S.top();
        return true;
    }
}

const BET& BET::operator=(const BET& rhs) {
    BET copy;
    root = clone(rhs.root);
    return *this;
}

void BET::printInfixExpression() const {
    printInfixExpression(root);
    cout << endl;
}


void BET::printPostfixExpression() const {
    printPostfixExpression(root);
    cout << endl;
}

size_t BET::size() const {
    return size(root);
}

size_t BET::leaf_nodes() const {
    return leaf_nodes(root);
}

bool BET::empty() const {
    return size() == 0;
}


void BET::printInfixExpression(BinaryNode *n) const {
    if(n != nullptr){
        if(n->left != nullptr && n->right != nullptr){
            if(prec(n->left->element[0]) <= prec(n->right->element[0]))
            cout << "( ";
        }

        printInfixExpression(n->left);
        cout << n->element << " ";
        printInfixExpression(n->right);
        if(n->left != nullptr && n->right != nullptr){
            if(prec(n->left->element[0]) <= prec(n->right->element[0]))
            cout << ") ";
        }
    }
}

void BET::printPostfixExpression(BinaryNode *n) const {
    if(n != nullptr){
        printPostfixExpression(n->left);
        printPostfixExpression(n->right);
        if(n == root){
            cout << n->element;
        }else{
            cout << n->element << " " ;
        }
    }
}


void BET::makeEmpty(BinaryNode *&t) {
    if(t != nullptr){               //checks if subtree is empty
        makeEmpty(t->left);         //recursive call to traverse each left node
        makeEmpty(t->right);        //recursive call to traverse each right node
        delete t;                   //deletes node if it has no remaining children
    }
    t = nullptr;                    //sets deleted nodes to nullptr
}       //recursive clear function


typename BET::BinaryNode* BET::clone(BinaryNode *t) {
    if(t == nullptr){
        return nullptr;      //returns nullptr if node doesn't exist
    }else{
        return new BinaryNode{t->element,clone(t->left), clone(t->right)};      //creates new node with children created recursively
    }
}       //recursive function to clone a subtree given a root

size_t BET::size(BinaryNode* t) const {
    size_t total = 0;                   //declares total
    if(t != nullptr){
        total++;                        //increments total
        total += size(t->left);         //adds the total of all left nodes
        total += size(t->right);        //adds the total of all right nodes
    }
    return total;
}       //recursive function for the size of a subtree

size_t BET::leaf_nodes(BinaryNode *t) const {
    size_t total = 0;                       //total variable
    if(t != nullptr){
        if(t->left == nullptr && t->right == nullptr){
            total++;        //increments total if node is a leaf
        }
        total += leaf_nodes(t->left);       //adds all left leaf nodes
        total += leaf_nodes(t->right);      //adds all right leaf nodes
    }
    return total;
}       //recursive function to find number of leaf nodes

int BET::prec(char c) const {
    if(c == '*' || c == '/')
        return 2;
    if(c == '+' || c == '-')
        return 1;
    else
        return 5;
}       //function to return the operator precedence
#endif
