//
// Created by Victor on 21.09.2021.
//

#ifndef JSON_PARSE_JSONPARSER_H
#define JSON_PARSE_JSONPARSER_H

#include <iostream>
#include <string>
#include <list>
#include <map>

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

//TODO возвращать масив строк
int parse_object(std::istream& stream, std::string& parent, std::string& frequired_key, std::list<std::pair<std::string,std::string>>& result);

std::list<std::pair<std::string,std::string>> find_keys(std::istream& stream, std::string key);

class JsonException: public std::exception {
public:
    explicit JsonException(std::string msg)
            : msg_(std::move(msg)) {}

    ~JsonException() noexcept override = default;

    [[nodiscard]] const char* what() const noexcept override {
        return msg_.data();
    }

private:
    std::string msg_;
};

#endif //JSON_PARSE_JSONPARSER_H
