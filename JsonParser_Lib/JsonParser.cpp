//
// Created by Victor on 21.09.2021.
//

#include "JsonParser.h"

#include <iostream>
#include <string>
#include <memory.h>
#include <cstring>
#include <list>

using std::cout;
using std::endl;
using std::string;
using std::list;
using std::pair;

enum VariableType {
    STRING,
    NUMBER,
    NULL_,
    BOOLEAN,
    ARRAY,
    OBJECT
};

struct Entry{
    int start;
    int end;
};

int parse_object(std::istream& stream, string parent, string& frequired_key, list<pair<string,string>>& result);
Entry read_variable(std::istream& stream, string& key_name, string& frequired_key, list<pair<string,string>>& result);

//return key name
string decode_key_name(std::istream& stream){
    char quotes = '\0';
    stream >> quotes;
    if(quotes != '\"'){
        throw JsonException("incorrect format. expected quotes in key name");
    }

    string key_name;
    char c = '\0';
    bool ignore_quotes = false;
    while(!stream.eof()){
        stream.read(&c, sizeof(char));

        if(c == '\\'){
            ignore_quotes = true;
            continue;
        }

        if(ignore_quotes){
            ignore_quotes = false;
            continue;
        }

        if(c == '\"'){
            break;
        }
        key_name.push_back(c);
    }

    return key_name;
}
//return variable type
VariableType determine_type(std::istream& stream){
    //the first variable symbol
    char c = '\0';
    stream >> c;
    if(c == '\"'){
        return STRING;
    }

    if(c >= '0' && c <= '9'){
        return NUMBER;
    }

    if(c == 'n'){
        return NULL_;
    }

    if(c == 't' || c == 'f'){
        return BOOLEAN;
    }

    if(c == '['){
        return ARRAY;
    }

    if(c == '{'){
        return OBJECT;
    }

    throw JsonException("incorrect format. undefined variable type");
}

int read_string_variable(std::istream& stream){
    char c = '\0';
    bool ignore_quotes = false;
    while(!stream.eof()){
        stream.read(&c, sizeof(char));
        if(c == '\\'){
            ignore_quotes = true;
            continue;
        }

        if(ignore_quotes){
            ignore_quotes = false;
            continue;
        }

        if(c == '\"'){
            break;
        }
    }

    return stream.tellg();
}

int read_number(std::istream& stream){
    char c = '\0';
    while(!stream.eof()){
        stream >> c;
        if(c == ',' || c == '}' || c == ']'){
            break;
        }
        if(!(c >= '0' && c <= '9') && c != 'e'  && c != '+'  && c != '-'  && c != '.'){
            throw JsonException("incorrect format. undefined variable type");
        }
    }
    stream.seekg(-1, std::ios::cur);
    return stream.tellg();
}

int read_boolean(std::istream& stream){
    //the second symbol of boolean variable
    char c = '\0';
    stream >> c;

    if(c == 'a'){
        string false_str(3, '\0');
        stream.read(false_str.data(),3); //read the rest of "false" (lse)
        if(memcmp(false_str.data(), "lse", 3) == 0){
            return stream.tellg();
        }else{
            throw JsonException("incorrect format. undefined variable type");
        }
    }

    if(c == 'r'){
        string true_str(2, '\0');
        stream.read(true_str.data(),2); //read the rest of "true" (ue)
        if(memcmp(true_str.data(), "ue", 2) == 0){
            return stream.tellg();
        }else{
            throw JsonException("incorrect format. undefined variable type");
        }
    }
    throw JsonException("incorrect format. undefined variable type");
}

int read_array(std::istream& stream, string parent, string& frequired_key, list<pair<string,string>>& result){
    char c = '\0';
    while(!stream.eof()){
        read_variable(stream,parent,frequired_key,result);

        stream >> c;

        if(c == ']'){
            break;
        }

        if(c != ','){
            throw JsonException("incorrect format. undefined variable type");
        }
    }

    return stream.tellg();
}

int read_null(std::istream& stream){
    string null_str(3, '\0');
    stream.read(null_str.data(),3);
    //read the rest of "null" (ull)
    if(memcmp(null_str.data(), "ull", 3) == 0){
        return stream.tellg();
    }else{
        throw JsonException("incorrect format. undefined variable type");
    }
}

Entry read_variable(std::istream& stream, string& key_name, string& frequired_key, list<pair<string,string>>& result){
    VariableType type = determine_type(stream);

    Entry entry{};
    entry.start = stream.tellg();
    entry.start--; //start of variable

    if(type == STRING){
        entry.end = read_string_variable(stream);
        return entry;
    }

    if(type == NUMBER){
        entry.end = read_number(stream);
        return entry;
    }

    if(type == NULL_){
        entry.end = read_null(stream);
        return entry;
    }

    if(type == BOOLEAN){
        entry.end = read_boolean(stream);
        return entry;
    }

    if(type == ARRAY){
        entry.end = read_array(stream, "/" + key_name, frequired_key, result);
        return entry;
    }

    if(type == OBJECT){
        stream.seekg(-1, std::ios::cur);
        entry.end = parse_object(stream, "/" + key_name, frequired_key, result);
        return entry;
    }

    throw JsonException("incorrect format. undefined variable type");
}

int parse_object(std::istream& stream, string parent, string& frequired_key, list<pair<string,string>>& result){
    char open_brace = '\0';
    stream >> open_brace;
    if(open_brace != '{'){
        throw JsonException("incorrect format. expected open brace on object start");
    }

    while(!stream.eof()){
        string key_name = decode_key_name(stream);

        char colon = '\0';
        stream >> colon;
        if(colon != ':'){
            throw JsonException("incorrect format. expected colon after key name");
        }

        Entry entry = read_variable(stream,key_name, frequired_key, result);

        //if its key that we finding then add to list
        if(strcasecmp(key_name.c_str(), frequired_key.c_str()) == 0){
            string variable(entry.end - entry.start, '\0');
            stream.seekg(entry.start, std::ios::beg);
            stream.read(variable.data(), entry.end - entry.start);

            result.emplace_back(parent.append("/").append(key_name), variable);
        }

        char comma = '\0';
        stream >> comma;
        if(comma == '}'){
            return stream.tellg();
        }

        if(comma != ','){
            throw JsonException("incorrect format.");
        }
    }
    throw JsonException("incorrect format. unexpected object end");
}

list<pair<string,string>> find_keys(std::istream& stream, std::string key){
    string base;
    list<pair<string,string>> result;
    parse_object(stream,base, key,result);
    return result;
}