#include "kvstore.hpp"
#include <iostream>
#include <string>
#include <sstream>
#include <vector>
#include <cctype>

using namespace std;


int main(){
    
    KVStore db;

    while (true){
        string line;
        cout << "mini-redis> ";

        if (!getline(cin,line)) break;

        stringstream ss(line);
        string token;
        vector<string> tokens;

        while (ss >> token){
            tokens.push_back(token);
        }

        if (tokens.empty()){
            continue;
        }

        for (char& c : tokens[0]){
            c=std::toupper(c);
        }
        
        if (tokens[0] == "SET"){
            if (tokens.size()<3){
                cout << "(error) ERR wrong number of arguments for 'set' command\n";
            }
            else{
                db.set(tokens[1],tokens[2]);
                cout << "OK\n";
            }
        }
        else if (tokens[0]=="GET"){
            if (tokens.size()<2){
                cout << "(error) ERR wrong number of arguments for 'get' command\n";
            } else {
                auto val=db.get(tokens[1]);
                if (val.has_value()){
                    cout << "\"" << val.value() << "\"\n";
                } else {
                    cout << "(nil)\n";
                }
            }
        } 
        else if (tokens[0]=="DEL"){
            if (tokens.size()<2){
                cout << "(error) ERR wrong number of arguments for 'del' command\n";
            } else {
                bool val = db.del(tokens[1]);
                if (val){
                    cout << 1 << "\n";
                }
                else{
                    cout << 0 << "\n";
                }
            }
        }
        else if (tokens[0]=="QUIT" || tokens[0]=="EXIT"){
            break;
        }
        else{
            cout << "(error) ERR unknown command '" << tokens[0] << "'\n";
        }
    }

    return 0;
}