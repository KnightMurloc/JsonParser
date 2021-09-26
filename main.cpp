#include <iostream>
#include <fstream>
#include <list>
#include "JsonParserLib/JsonParser.h"

using namespace std;

int main() {

    std::ifstream file("test.json");

    try {
        list<pair<string,string>> result = find_keys(file,"test str");
        for(auto& entry : result){
            std::cout << entry.first + ": " + entry.second << std::endl;
        }
    }catch(std::exception& e){
        std::cout << e.what() << std::endl;
    }

    return 0;
}