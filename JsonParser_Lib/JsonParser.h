//
// Created by Victor on 21.09.2021.
//

#ifndef JSON_PARSE_JSONPARSER_H
#define JSON_PARSE_JSONPARSER_H

#include <iostream>
#include <string>
#include <list>


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
