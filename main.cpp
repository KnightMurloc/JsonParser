#include <iostream>
#include <fstream>
#include "JsonParser.h"

int main() {

    std::ifstream file("test.json");

    try {
        parse_object(file);
    }catch(std::exception& e){
        std::cout << e.what() << std::endl;
    }

    return 0;
}