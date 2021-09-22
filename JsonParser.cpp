//
// Created by Victor on 21.09.2021.
//

#include "JsonParser.h"

#include <iostream>
#include <string>

using std::cout;
using std::endl;
using std::string;

//TODO ощибка неожиданого конца файла!

//возвращает первый не пустой символ(пробел, таб, перенос строки)
//char skip_space(std::istream& stream){
//    char c = '\0';
//    do{
//        stream >> c;
//    }while((c == ' ' || c == '\t' || c == '\n') && !stream.eof());
//    return c;
//}

//возвращает имя переменой
string decode_key_name(std::istream& stream){
    //char quotes = skip_space(stream);
    char quotes = '\0';
    stream >> quotes;
    if(quotes != '\"'){
        throw JsonException("incorrect format");
    }

    string key_name;
    char c = '\0';
    while(!stream.eof()){
        stream.read(&c, sizeof(char));
        if(c == '\"'){
            break;
        }
        key_name.push_back(c);
    }

    return key_name;
}
//возаращает тип переменой
VariableType determine_type(std::istream& stream){
    //первый символ переменой
    //char c = skip_space(stream);
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

    throw JsonException("incorrect format");
}

string read_string_variable(std::istream& stream){
    string str;
    char c = '\0';
    while(!stream.eof()){
        stream >> c;
        if(c == '\"'){
            break;
        }
        str.push_back(c);
    }
    return str;
}

string read_number(std::istream& stream){
    string num;
    stream.seekg(-1, std::ios::cur);
    char c = '\0';
    while(!stream.eof()){
        stream >> c;
        if(c == ',' || c == '}'){
            break;
        }
        num.push_back(c);
    }
    stream.seekg(-1, std::ios::cur);
    return num;
}

string read_boolean(std::istream& stream){
    //второй символ булевой переменой
    char c = '\0';
    stream >> c;

    if(c == 'a'){
        stream.seekg(3, std::ios::cur);
        return "false";
    }

    if(c == 'r'){
        stream.seekg(2, std::ios::cur);
        return "true";
    }
    throw JsonException("incorrect format");
}

string read_array(std::istream& stream){
    string array;
    char c = '\0';
    while(!stream.eof()){
        stream >> c;
        if(c == ']'){
            break;
        }
        array.push_back(c);
    }
    return array;
}

string read_variable(std::istream& stream){
    VariableType type = determine_type(stream);

    if(type == STRING){
        return read_string_variable(stream);
    }

    if(type == NUMBER){
        return read_number(stream);
    }

    if(type == NULL_){
        stream.seekg(3, std::ios::cur);
        return string("null");
    }

    if(type == BOOLEAN){
        return read_boolean(stream);
    }

    if(type == ARRAY){
        return read_array(stream);
    }

    if(type == OBJECT){
        stream.seekg(-1, std::ios::cur);
        int start = stream.tellg();
        int end = parse_object(stream);
        string obj(end - start, '\0');
        stream.seekg(start,std::ios::beg);
        stream.read(obj.data(), end - start);
        return obj;
    }

    throw JsonException("incorrect format");
}

int parse_object(std::istream& stream){
    //char open_brace = skip_space(stream);
    char open_brace = '\0';
    stream >> open_brace;
    if(open_brace != '{'){
        throw JsonException("incorrect format");
    }

    while(!stream.eof()){
        string key_name = decode_key_name(stream);
        //char colon = skip_space(stream);
        char colon = '\0';
        stream >> colon;
        if(colon != ':'){
            throw JsonException("incorrect format");
        }

        string variable = read_variable(stream);
        cout << key_name << " : " << variable << endl;

//        char comma = skip_space(stream);
        char comma = '\0';
        stream >> comma;
        if(comma == '}'){
            break;
        }

        if(comma != ','){
            throw JsonException("incorrect format");
        }
    }
    return stream.tellg();
}