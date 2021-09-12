#include "stack.h"
#include <iostream>
#include <string>
#include <sstream>
#include <cctype>
int prec(char c)
{
    if(c == '*' || c == '/')
        return 2;
    if(c == '+' || c == '-')
        return 1;
    else
        return -1;
}       //function to return the operator precedence
int main() {
    cop4530::Stack<std::string> op, out, cpy, fout;
    std::string exp, token, prev;
    bool flag = false;
    int opcnt = 0, ocnt = 0;  //variable declarions
    std::cout << "Enter infix expression (\"exit\" to quit):\n";
    std::getline(std::cin, exp);        //prompts and collects input
    while(exp != "exit" && std::cin){
        exp += ' ';     //adds space to input to make parsing easier
        std::stringstream inp(exp);     //creates stringstream from input
        while(inp){
            std::getline(inp,token, ' ');       //collects token
            if(std::isalnum(token[0])){
                out.push(token);
                ocnt++;     //increases count of operands
            }       //if token is a number or letter, pushes it to output stack
            if(token == "("){
                op.push(token);
            }       //pushes ( to stack
            if(token == "+" || token == "-" || token == "*" || token == "/"){
                while(!(op.empty()) && op.top() != "(" && !(prec(op.top()[0]) < prec(token[0]))){
                    out.push(op.top());
                    op.pop();
                }       //adds operators in  op stack to output stack if criteria is met
                op.push(token);     //adds new token to op stack
                opcnt++;        //increases count of operators
            }
            if(token == ")"){
                if(prev == "+" || prev == "-" || prev == "*" || prev == "/"){
                    std::cout << "operator missing operand\n";
                    return -1;
                }       //error if operator before )
                else{
                    if(op.empty()){
                        std::cout << "missing (\n";
                        return -1;
                    }       //error if expression is missing (
                    while(op.top() != "(" && !(op.empty())){
                        out.push(op.top());
                        op.pop();
                    }       //pushes operators to output until ( is encountered
                    if(op.empty()){
                        std::cout << "missing (\n";
                        return -1;      //expression is missing a (
                    }else {
                        op.pop();       //removes (
                    }
                }
            }
            prev = token;       //records the previous value
        }
        if(prev == "+" || prev == "-" || prev == "*" || prev == "/" || prev == "("){
            std::cout << "operator missing operand\n";
            return -1;
        }       //checks if last token is an operator
        if(ocnt != (opcnt+1)){
            std::cout << "error in infix expression\n";
            return -1;      //checks the number of operands to operators is correct
        }else{
                while(!(op.empty())){
                    if(op.top() == "("){
                        std::cout << "missing )\n";
                        return -1;      //case where a ( is remaining in the op stack
                    }else{
                        out.push(op.top());
                        op.pop();
                    }       //outputs remaining operators
                }
        }
        std::cout << "Postfix expression: " << out << std::endl;        //outputs postfix
        cpy = out;      //copies output stack
        flag = false;
        while(!(cpy.empty())){
            if(std::isalpha(cpy.top()[0])){
                flag = true;
                break;      //checks if expresion has a variable
            }else{
                cpy.pop();
            }
        }
        if(flag){
            std::cout << "Postfix evaluation: " << out << " = " << out << std::endl;        //outputs postfix if expression contains variable
        }
        if(!flag){
            cpy = out;
            while(!(cpy.empty())){
                fout.push(cpy.top());
                cpy.pop();
            }       //creates a flipped stack of the output
            std::size_t found = fout.top().find('.');       //checks if operands are floating point
            if(found != std::string::npos){
                cop4530::Stack<double> dop;     //stack to hold double operands
                while(!(fout.empty())) {
                    if (std::isdigit(fout.top()[0])) {
                        dop.push(std::stod(fout.top()));
                        fout.pop();     //pushes operands to stack
                    } else {
                        char op = fout.top()[0];
                        double x, y;
                        if (dop.size() < 2) {
                            std::cout << "missing an operand\n";
                            return -1;      //ensures the stack has enough operands for evaluation
                        } else {
                            switch (op) {
                                case '+':
                                    x = dop.top();
                                    dop.pop();
                                    y = dop.top();
                                    dop.pop();
                                    dop.push(x+y);
                                    fout.pop();
                                    break;      //adds operands
                                case '-':
                                    x = dop.top();
                                    dop.pop();
                                    y = dop.top();
                                    dop.pop();
                                    dop.push(y-x);
                                    fout.pop();
                                    break;      //subtracts operands
                                case '*':
                                    x = dop.top();
                                    dop.pop();
                                    y = dop.top();
                                    dop.pop();
                                    dop.push(x*y);
                                    fout.pop();
                                    break;      //multiplies operands
                                case '/':
                                    x = dop.top();
                                    dop.pop();
                                    y = dop.top();
                                    dop.pop();
                                    dop.push(y/x);
                                    fout.pop();
                                    break;      //divides operands
                                default:
                                    std::cout << "Invalid operator\n";
                                    return -1;  //case where invalid operator is in expression
                            }
                        }
                    }
                }
                if(dop.size() > 1){
                    std::cout << "Missing operator\n";
                    return -1;      //ensures operand stack isn't missing operator
                }
                if(dop.size() == 1){
                    std::cout << "Postfix Evaluation: " << out << " = " << dop.top() << std::endl;
                }           //outputs evaluation
                dop.clear();        //clears stack for next use
            }else{          //integer evaluation
                cop4530::Stack<int> iop;
                while(!(fout.empty())) {
                    if (std::isdigit(fout.top()[0])) {
                        iop.push(std::stod(fout.top()));
                        fout.pop();     //adds operands to stack
                    } else {
                        char op = fout.top()[0];
                        int x, y;
                        if (iop.size() < 2) {
                            std::cout << "missing an operand\n";
                            return -1;      //ensures there are enough operands
                        } else {
                            switch (op) {
                                case '+':
                                    x = iop.top();
                                    iop.pop();
                                    y = iop.top();
                                    iop.pop();
                                    iop.push(x+y);
                                    fout.pop();
                                    break;      //adds operands
                                case '-':
                                    x = iop.top();
                                    iop.pop();
                                    y = iop.top();
                                    iop.pop();
                                    iop.push(y-x);
                                    fout.pop();
                                    break;      //subtracts operands
                                case '*':
                                    x = iop.top();
                                    iop.pop();
                                    y = iop.top();
                                    iop.pop();
                                    iop.push(x*y);
                                    fout.pop();
                                    break;      //multiplies operands
                                case '/':
                                    x = iop.top();
                                    iop.pop();
                                    y = iop.top();
                                    iop.pop();
                                    iop.push(y/x);
                                    fout.pop();
                                    break;      //divides operands
                                default:
                                    std::cout << "Invalid operator\n";
                                    return -1;      //case of incorrect operator
                            }
                        }
                    }
                }
                if(iop.size() > 1){
                    std::cout << "Missing operator\n";
                    return -1;
                }       //ensures expression isn't missing operator
                if(iop.size() == 1){
                    std::cout << "Postfix Evaluation: " << out << " = " << iop.top() << std::endl;
                }       //outputs evaluation
                iop.clear();        //clears stack for next use
            }
        }
        out.clear();        //clears output stack for next use
        ocnt = opcnt = 0;       //clears counters for next use
        std::cout << "Enter infix expression (\"exit\" to quit):\n";
        std::getline(std::cin, exp);        //prompts and collects input
    }
    return 0;
}
