//
// Created by Victor on 21.09.2021.
//

#ifndef JSON_PARSE_JSONPARSER_H
#define JSON_PARSE_JSONPARSER_H

#include <iostream>

enum VariableType {
    STRING,
    NUMBER,
    NULL_,
    BOOLEAN,
    ARRAY,
    OBJECT
};


//TODO возвращать масив строк
int parse_object(std::istream& stream);

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
