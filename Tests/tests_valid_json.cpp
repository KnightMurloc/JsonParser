//
// Created by Victor on 23.09.2021.
//

#define CATCH_CONFIG_MAIN

#include <catch.hpp>
#include "JsonParser.h"
#include <list>
#include <string>

using std::list;
using std::pair;
using std::string;
using std::ios;

TEST_CASE("valid key", "[valid json]"){
    std::ifstream file("test_Files/valid1.json");

    SECTION("string") {
        file.clear();
        file.seekg(0, ios::beg);
        auto result = find_keys(file, "string");

        if(result.size() != 2){
            FAIL(string("wrong result size: expect 2 but get: ") + std::to_string(result.size()));
        }

        auto begin = result.begin();
        auto first_pair = *begin;
        begin++;
        auto second_pair = *begin;

        REQUIRE(first_pair.first == "/string");
        REQUIRE(first_pair.second == "\"test string\"");

        REQUIRE(second_pair.first == "/object/STRING");
        REQUIRE(second_pair.second == "\"test string2\"");
    }

    SECTION("number") {
        file.clear();
        file.seekg(0, ios::beg);
        auto result = find_keys(file, "num");

        if(result.size() != 2){
            FAIL(string("wrong result size: expect 2 but get: ") + std::to_string(result.size()));
        }

        auto begin = result.begin();
        auto first_pair = *begin;
        begin++;
        auto second_pair = *begin;

        REQUIRE(first_pair.first == "/num");
        REQUIRE(first_pair.second == "10.5e+10");

        REQUIRE(second_pair.first == "/object/NUM");
        REQUIRE(second_pair.second == "20.9e+30");
    }

    SECTION("boolean") {
        file.clear();
        file.seekg(0, ios::beg);
        auto result = find_keys(file, "boolean");

        if(result.size() != 2){
            FAIL(string("wrong result size: expect 2 but get: ") + std::to_string(result.size()));
        }

        auto begin = result.begin();
        auto first_pair = *begin;
        begin++;
        auto second_pair = *begin;

        REQUIRE(first_pair.first == "/boolean");
        REQUIRE(first_pair.second == "true");

        REQUIRE(second_pair.first == "/object/BOOLEAN");
        REQUIRE(second_pair.second == "false");
    }

    SECTION("boolean") {
        file.clear();
        file.seekg(0, ios::beg);
        auto result = find_keys(file, "boolean");

        if(result.size() != 2){
            FAIL(string("wrong result size: expect 2 but get: ") + std::to_string(result.size()));
        }

        auto begin = result.begin();
        auto first_pair = *begin;
        begin++;
        auto second_pair = *begin;

        REQUIRE(first_pair.first == "/boolean");
        REQUIRE(first_pair.second == "true");

        REQUIRE(second_pair.first == "/object/BOOLEAN");
        REQUIRE(second_pair.second == "false");
    }

    SECTION("null") {
        file.clear();
        file.seekg(0, ios::beg);
        auto result = find_keys(file, "null");

        if(result.size() != 2){
            FAIL(string("wrong result size: expect 2 but get: ") + std::to_string(result.size()));
        }

        auto begin = result.begin();
        auto first_pair = *begin;
        begin++;
        auto second_pair = *begin;

        REQUIRE(first_pair.first == "/null");
        REQUIRE(first_pair.second == "null");

        REQUIRE(second_pair.first == "/object/NULL");
        REQUIRE(second_pair.second == "null");
    }

    SECTION("null") {
        file.clear();
        file.seekg(0, ios::beg);
        auto result = find_keys(file, "array");

        if(result.size() != 2){
            FAIL(string("wrong result size: expect 2 but get: ") + std::to_string(result.size()));
        }

        auto begin = result.begin();
        auto first_pair = *begin;
        begin++;
        auto second_pair = *begin;

        REQUIRE(first_pair.first == "/array");
        REQUIRE(first_pair.second == "[1,2,4,5,6,7,8]");

        REQUIRE(second_pair.first == "/object/ARRAY");
        REQUIRE(second_pair.second == "[0,9,8,7,6,56,54]");
    }

    SECTION("object") {
        file.clear();
        file.seekg(0, ios::beg);
        auto result = find_keys(file, "object");

        if(result.size() != 1){
            FAIL(string("wrong result size: expect 1 but get: ") + std::to_string(result.size()));
        }

        auto begin = result.begin();
        auto first_pair = *begin;

        REQUIRE(first_pair.first == "/object");
        REQUIRE(first_pair.second == "{\n"
                                     "    \"STRING\" : \"test string2\",\n"
                                     "    \"NUM\": 20.9e+30,\n"
                                     "    \"BOOLEAN\": false,\n"
                                     "    \"NULL\": null,\n"
                                     "    \"ARRAY\": [0,9,8,7,6,56,54]\n"
                                     "  }");

    }
}

TEST_CASE("unValid key", "[valid json]"){
    std::ifstream file("test_Files/valid1.json");

    SECTION("string") {
        file.clear();
        file.seekg(0, ios::beg);
        auto result = find_keys(file, "123");

        if(!result.empty()){
            FAIL(string("wrong result size: expect 0 but get: ") + std::to_string(result.size()));
        }
        SUCCEED();
    }
}

TEST_CASE("with extra space/tabs/line break", "[valid json]"){
    std::ifstream file("test_Files/valid2.json");

    SECTION("string") {
        file.clear();
        file.seekg(0, ios::beg);
        auto result = find_keys(file, "string");

        if(result.size() != 2){
            FAIL(string("wrong result size: expect 2 but get: ") + std::to_string(result.size()));
        }

        auto begin = result.begin();
        auto first_pair = *begin;
        begin++;
        auto second_pair = *begin;

        REQUIRE(first_pair.first == "/string");
        REQUIRE(first_pair.second == "\"test string\"");

        REQUIRE(second_pair.first == "/object/STRING");
        REQUIRE(second_pair.second == "\"test string2\"");
    }

    SECTION("number") {
        file.clear();
        file.seekg(0, ios::beg);
        auto result = find_keys(file, "num");

        if(result.size() != 2){
            FAIL(string("wrong result size: expect 2 but get: ") + std::to_string(result.size()));
        }

        auto begin = result.begin();
        auto first_pair = *begin;
        begin++;
        auto second_pair = *begin;

        REQUIRE(first_pair.first == "/num");
        REQUIRE(first_pair.second == "10.5e+10");

        REQUIRE(second_pair.first == "/object/NUM");
        REQUIRE(second_pair.second == "20.9e+30");
    }

    SECTION("boolean") {
        file.clear();
        file.seekg(0, ios::beg);
        auto result = find_keys(file, "boolean");

        if(result.size() != 2){
            FAIL(string("wrong result size: expect 2 but get: ") + std::to_string(result.size()));
        }

        auto begin = result.begin();
        auto first_pair = *begin;
        begin++;
        auto second_pair = *begin;

        REQUIRE(first_pair.first == "/boolean");
        REQUIRE(first_pair.second == "true");

        REQUIRE(second_pair.first == "/object/BOOLEAN");
        REQUIRE(second_pair.second == "false");
    }

    SECTION("boolean") {
        file.clear();
        file.seekg(0, ios::beg);
        auto result = find_keys(file, "boolean");

        if(result.size() != 2){
            FAIL(string("wrong result size: expect 2 but get: ") + std::to_string(result.size()));
        }

        auto begin = result.begin();
        auto first_pair = *begin;
        begin++;
        auto second_pair = *begin;

        REQUIRE(first_pair.first == "/boolean");
        REQUIRE(first_pair.second == "true");

        REQUIRE(second_pair.first == "/object/BOOLEAN");
        REQUIRE(second_pair.second == "false");
    }

    SECTION("null") {
        file.clear();
        file.seekg(0, ios::beg);
        auto result = find_keys(file, "null");

        if(result.size() != 2){
            FAIL(string("wrong result size: expect 2 but get: ") + std::to_string(result.size()));
        }

        auto begin = result.begin();
        auto first_pair = *begin;
        begin++;
        auto second_pair = *begin;

        REQUIRE(first_pair.first == "/null");
        REQUIRE(first_pair.second == "null");

        REQUIRE(second_pair.first == "/object/NULL");
        REQUIRE(second_pair.second == "null");
    }

    SECTION("null") {
        file.clear();
        file.seekg(0, ios::beg);
        auto result = find_keys(file, "array");

        if(result.size() != 2){
            FAIL(string("wrong result size: expect 2 but get: ") + std::to_string(result.size()));
        }

        auto begin = result.begin();
        auto first_pair = *begin;
        begin++;
        auto second_pair = *begin;

        REQUIRE(first_pair.first == "/array");
        REQUIRE(first_pair.second == "[1,2,4,5,6,7,8]");

        REQUIRE(second_pair.first == "/object/ARRAY");
        REQUIRE(second_pair.second == "[0,9,8,7,6,56,54]");
    }

    SECTION("object") {
        file.clear();
        file.seekg(0, ios::beg);
        auto result = find_keys(file, "object");

        if(result.size() != 1){
            FAIL(string("wrong result size: expect 1 but get: ") + std::to_string(result.size()));
        }

        auto begin = result.begin();
        auto first_pair = *begin;

        REQUIRE(first_pair.first == "/object");
        REQUIRE(first_pair.second == "{\n"
                                     "    \"STRING\" : \"test string2\",\n"
                                     "    \"NUM\": 20.9e+30,\n"
                                     "    \"BOOLEAN\": false,\n"
                                     "    \"NULL\": null,\n"
                                     "    \"ARRAY\": [0,9,8,7,6,56,54]\n"
                                     "  }");

    }
}