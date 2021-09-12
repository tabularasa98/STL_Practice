#include <termios.h>
#include <unistd.h>
#include <stdio.h>
#include <iostream>
#include <string>
#include "passserver.h"
using namespace std;
void Menu()
{
    cout << "\n\n";
    cout << "l - Load From File" << endl;
    cout << "a - Add User" << endl;
    cout << "r - Remove User" << endl;
    cout << "c - Change User Password" << endl;
    cout << "f - Find User" << endl;
    cout << "d - Dump HashTable" << endl;
    cout << "s - HashTable Size" << endl;
    cout << "w - Write to Password File" << endl;
    cout << "x - Exit program" << endl;
    cout << "\nEnter choice : ";
}
int getch() {
    int ch;
    struct termios t_old, t_new;

    tcgetattr(STDIN_FILENO, &t_old);
    t_new = t_old;
    t_new.c_lflag &= ~(ICANON | ECHO);
    tcsetattr(STDIN_FILENO, TCSANOW, &t_new);

    ch = getchar();

    tcsetattr(STDIN_FILENO, TCSANOW, &t_old);
    return ch;
}
string findpass(string prompt){
    string password;
    unsigned char ch = 0;
    cout << prompt << endl;
    while((ch = getch()) != 10){            //while ch doesn't equal enter
        if(ch == 127 && password.length() != 0){        // if char is a backspace
            password.resize(password.length()-1);
        }
        else{
            password+=ch;
        }
    }
    cout << endl;
    return password;
}
int main(){
    int cap;
    char inp;
    cout << "Enter preferred hash table capacity: ";
    cin >> cap;
    PassServer PS(cap);
    cout << PS.capacity() << endl;
    Menu();
    cin >> inp;
    while(inp != 'x'){
        char filename[100];
        string username, password, newpass;
        switch(inp){
            case 'l':
                cout << "Enter password file name to load from: ";
                cin >> filename;
                PS.load(filename);
                break;
            case 'a':
                cout << "Enter username: ";
                cin >> username;
                password = findpass("Enter password: ");
                if(PS.addUser(pair<string, string>(username, password))){
                    cout << "\nUser " << username << " added.\n";
                }else{
                    cerr << "\n*****Error: User already exists. Could not add user.\n";
                }
                break;
            case 'r':

                cout << "Enter username: ";
                cin >> username;
                if(PS.removeUser(username)){
                    cout << "User " << username << " deleted.\n";
                }else{
                    cerr << "*****Error: User not found.  Could not delete user\n";
                }
                break;
            case 'c':
                cout << "Enter username    : ";
                cin >> username;
                password = findpass("Enter password    : ");
                newpass = findpass("\nEnter new password: ");
                if(PS.changePassword(pair<string,string>(username,password),newpass)){
                    cout << "\nPassword changed for user " << username << endl;
                }else{
                    cerr << "\n*****Error: Could not change user password\n";
                }
                break;
            case 'f':
                cout << "Enter username    : ";
                cin >> username;
                if(PS.find(username)){
                    cout << "\nUser '" << username<< "' found.\n";
                }else{
                    cerr << "\nUser '" << username<< "' not found.\n";
                }
                break;
            case 'd':
                PS.dump();
                break;
            case 's':
                cout << "Size of hashtable: " << PS.size() << endl;
                break;
            case 'w':
                cout << "Enter password file name to write to: ";
                cin >> filename;
                PS.write_to_file(filename);
                break;
            default:
                cerr << "*****Error: Invalid entry.  Try again." << endl;
                break;
        }
        Menu();
        cin >> inp;
    }
}