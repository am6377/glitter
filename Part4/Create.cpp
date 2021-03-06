#include "Create.h"

#include <iostream>
#include <vector>
#include <istream>
#include <fstream>
#include <sstream>
#include <cstring>
#include <string>



using namespace std;
// using namespace glitter;

// Function for Creating new accounts
string create(const string& id, const string& username, const string& password,  const char tweetFile [], const char userFile [], const char friendFile []){
    string line, token;
    fstream idfile(userFile);
    if(!idfile.is_open()){cerr<< "Users.txt file did not open, create failed \n";}
    
    // Does the ID already exist? If so mark it and leave nested loop.
    bool idexists = 0;
    while(getline(idfile, line)){
        istringstream spilt(line);
        token = "";
        while(getline(spilt, token, ':')){
            if(id==token){
                idexists = 1;
                goto afterreading;
            }
            break;
        }
    }
    
    afterreading:
    idfile.close();
    if (idexists){ // ID already exists, send back exists
        return "exists";
    } 
    else {
        // ID doesn't exist, add it.
        ofstream usersFile;
        usersFile.open (userFile,ios::app);
        usersFile << id << ":" << username << ":" << password << "\n";
        usersFile.close();
        
        // Add them to tweet file
        ofstream tweetsFile;
        tweetsFile.open (tweetFile,ios::app);
        tweetsFile << id << "\n";
        tweetsFile.close();
        
        // Add them to friends file
        ofstream friendsFile;
        friendsFile.open (friendFile,ios::app);
        friendsFile << id << "\n";
        friendsFile.close();
        
        return "newaccount";
    }
};