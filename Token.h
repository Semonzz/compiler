#pragma once

#include "Head.h"

class Token {
public:
    string type;   
    string value; 
    Token* next;
    string typeLex;
    Token() : type(""), value(""), next(nullptr) {}
    Token(string t, string v, Token* a, string typL) : type(t), value(v), next(a), typeLex(typL) {}

    Token operator=(Token& other) {
        type = other.type;
        value = other.value;
        next = other.next;
        typeLex = other.typeLex;
        return *this;
    }

    bool operator!=(Token& other) {
        return type != other.type || value != other.value;
    }
};
