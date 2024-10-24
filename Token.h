#pragma once

#include "Head.h"

class Token {
public:
    string type;   
    string value; 
    Token* next;
    Token() : type(""), value(""), next(nullptr) {}
    Token(string t, string v, Token* a) : type(t), value(v), next(a) {}

    Token operator=(Token& other) {
        type = other.type;
        value = other.value;
        next = other.next;
        return *this;
    }

    bool operator!=(Token& other) {
        return type != other.type || value != other.value;
    }
};
