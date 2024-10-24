#pragma once

#include "Token.h"

class HashTable {
private:
	int sz = 10000;
	Token* table = new Token[sz+1];

	int hash(string key);

public:
	HashTable() {}
	~HashTable();
	
	void print();
	void printToFile(string path);
	void insert(Token token);
};
