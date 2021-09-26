#include <iostream>
#include <fstream>
#include <list>
#include <io.h>
#include "JsonParserLib/JsonParser.h"

using std::cout;
using std::endl;
using std::string;
using std::list;
using std::pair;
using std::ifstream;
using std::exception;

inline bool file_exist (const std::string& name) {
    return ( access( name.c_str(), F_OK ) != -1 );
}


int main(int argc, char* argv[]) {

    if(argc == 1){
        cout << "use -h to show help message" << endl;
        return 0;
    }

    string path;
    string key;

    for (int i = 1; i < argc; ++i) {
        if(string("-h") == argv[i]){
            cout
            << "-f <path to file>\n"
            << "-k key to find\n"
            << "-h to show this message" << endl;
            return 0;
        }

        if(string("-f") == argv[i]){
            path = argv[++i];
            continue;
        }

        if(string("-k") == argv[i]){
            key = argv[++i];
        }
    }

    if(path.empty() || key.empty()){
        cout << "use -h to show help message" << endl;
        return 0;
    }

    if(!file_exist(path)){
        cout << "wrong path" << endl;
        return 0;
    }

    try {
        ifstream file(path);

        list<pair<string, string>> result = find_keys(file, key);

        for (auto &p : result) {
            cout << p.first + ": " + p.second << endl;
        }
    }catch(exception& e){
        cout << e.what() << endl;
    }
    return 0;
}