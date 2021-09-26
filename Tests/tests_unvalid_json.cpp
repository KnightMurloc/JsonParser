//
// Created by Victor on 24.09.2021.
//

#include <catch.hpp>
#include "JsonParser.h"
#include <list>
#include <string>
#include <fstream>

using std::list;
using std::pair;
using std::string;
using std::ios;

TEST_CASE("random string", "[unvalid json]"){
    std::ifstream file("test_Files/unValid1.json");

    try {
        auto result = find_keys(file, "string");
        FAIL("expect JsonException");
    }catch(JsonException& e){
        REQUIRE(string("incorrect format. expected open brace on object start") == e.what());
    }
}

TEST_CASE("random string inside brakets", "[unvalid json]"){
    std::ifstream file("test_Files/unValid2.json");

    try {
        auto result = find_keys(file, "string");
        FAIL("expect JsonException");
    }catch(JsonException& e){
        REQUIRE(string("incorrect format. expected quotes in key name") == e.what());
    }
}

TEST_CASE("key name without quotes", "[unvalid json]"){
    std::ifstream file("test_Files/unValid3.json");
    try {
        auto result = find_keys(file, "string");
        FAIL("expect JsonException");
    }catch(JsonException& e){
        REQUIRE(string("incorrect format. expected quotes in key name") == e.what());
    }
}

TEST_CASE("no colon after key name", "[unvalid json]"){
    std::ifstream file("test_Files/unValid4.json");
    try {
        auto result = find_keys(file, "string");
        FAIL("expect JsonException");
    }catch(JsonException& e){
        REQUIRE(string("incorrect format. expected colon after key name") == e.what());
    }
}

TEST_CASE("undefined variable type", "[unvalid json]"){
    SECTION("string") {
        SECTION("without quotes") {
            std::ifstream file("test_Files/unValid51.json");
            try {
                auto result = find_keys(file, "string");
                FAIL("expect JsonException");
            } catch (JsonException &e) {
                REQUIRE(string("incorrect format. undefined variable type") == e.what());
            }
        }

        SECTION("with one quotes"){
            std::ifstream file("test_Files/unValid52.json");
            try {
                auto result = find_keys(file, "string");
                FAIL("expect JsonException");
            } catch (JsonException &e) {
                REQUIRE(string("incorrect format.") == e.what());
            }
        }
    }

    SECTION("int"){
        std::ifstream file("test_Files/unValid53.json");
        try {
            auto result = find_keys(file, "string");
            FAIL("expect JsonException");
        } catch (JsonException &e) {
            REQUIRE(string("incorrect format. undefined variable type") == e.what());
        }
    }

    SECTION("boolean"){
        SECTION("true typo") {
            std::ifstream file("test_Files/unValid54.json");
            try {
                auto result = find_keys(file, "string");
                FAIL("expect JsonException");
            } catch (JsonException &e) {
                REQUIRE(string("incorrect format. undefined variable type") == e.what());
            }
        }

        SECTION("false typo") {
            std::ifstream file("test_Files/unValid55.json");
            try {
                auto result = find_keys(file, "string");
                FAIL("expect JsonException");
            } catch (JsonException &e) {
                REQUIRE(string("incorrect format. undefined variable type") == e.what());
            }
        }
    }
    SECTION("null"){
        std::ifstream file("test_Files/unValid56.json");
        try {
            auto result = find_keys(file, "string");
            FAIL("expect JsonException");
        } catch (JsonException &e) {
            REQUIRE(string("incorrect format. undefined variable type") == e.what());
        }
    }

    SECTION("array"){

        SECTION("without brakets"){
            std::ifstream file("test_Files/unValid57.json");
            try {
                auto result = find_keys(file, "string");
                FAIL("expect JsonException");
            } catch (JsonException &e) {
                REQUIRE(string("incorrect format. expected quotes in key name") == e.what());
            }
        }

        SECTION("with one brakes"){
            std::ifstream file("test_Files/unValid58.json");
            try {
                auto result = find_keys(file, "string");
                FAIL("expect JsonException");
            } catch (JsonException &e) {
                REQUIRE(string("incorrect format. undefined variable type") == e.what());
            }
        }
    }

    SECTION("object"){

        SECTION("without brakets"){
            std::ifstream file("test_Files/unValid59.json");
            try {
                auto result = find_keys(file, "string");
                FAIL("expect JsonException");
            } catch (JsonException &e) {
                REQUIRE(string("incorrect format.") == e.what());
            }
        }

        SECTION("with one brakes"){
            std::ifstream file("test_Files/unValid510.json");
            try {
                auto result = find_keys(file, "string");
                FAIL("expect JsonException");
            } catch (JsonException &e) {
                REQUIRE(string("incorrect format.") == e.what());
            }
        }
    }
}