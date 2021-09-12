#include <iostream>
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
int main(){
    int cap;
    char inp;
    cout << "Enter preferred hash table capacity: ";
    cin >> cap;
    PassServer PS(cap);         //creates pass server
    cout << PS.capacity() << endl;      //outputs capacity
    Menu();
    cin >> inp;     //prompts and collects user
    while(inp != 'x'){      //loop for menu
        char filename[100];
        string username, password, newpass;
        switch(inp){
            case 'l':       //case for load file
                cout << "Enter password file name to load from: ";
                cin >> filename;
                PS.load(filename);
                break;
            case 'a':       //case for add user
                cout << "Enter username: ";
                cin >> username;
                cout << "Enter password: ";
                cin >> password;
                if(PS.addUser(pair<string, string>(username, password))){
                    cout << "\nUser " << username << " added.\n";
                }else{
                    cerr << "\n*****Error: User already exists. Could not add user.\n";
                }
                break;
            case 'r':       //case for remove user
                cout << "Enter username: ";
                cin >> username;
                if(PS.removeUser(username)){
                    cout << "User " << username << " deleted.\n";
                }else{
                    cerr << "*****Error: User not found.  Could not delete user\n";
                }
                break;
            case 'c':       //case for change password
                cout << "Enter username    : ";
                cin >> username;
                cout << "Enter password    : ";
                cin >> password;
                cout << "\nEnter new password: ";
                cin >> newpass;
                if(PS.changePassword(pair<string,string>(username,password),newpass)){
                    cout << "\nPassword changed for user " << username << endl;
                }else{
                    cerr << "\n*****Error: Could not change user password\n";
                }
                break;
            case 'f':       //case for find user
                cout << "Enter username    : ";
                cin >> username;
                if(PS.find(username)){
                    cout << "\nUser '" << username<< "' found.\n";
                }else{
                    cerr << "\nUser '" << username<< "' not found.\n";
                }
                break;
            case 'd':       //case for dump
                PS.dump();
                break;
            case 's':       //case for size
                cout << "Size of hashtable: " << PS.size() << endl;
                break;
            case 'w':       //case for write to file
                cout << "Enter password file name to write to: ";
                cin >> filename;
                PS.write_to_file(filename);
                break;
            default:        //invalid entry case
                cerr << "*****Error: Invalid entry.  Try again." << endl;
                break;
        }
        Menu();
        cin >> inp;     //reprompts user for input
    }
}