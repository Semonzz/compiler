#pragma once
#include "HashTable.h"
#include "dfa.h"
#include "Syntax.h"

class Lexer {
private:
	string nextLexeme(ifstream& file);
	void insert(HashTable& table, int state, int st, string typeLexeme, string lexem, Node& root, Syntax& synt);
	int lineNum = 1;

public:
	Lexer() {}

	void analyze(string inputFile, Node& root);

	~Lexer() {}
};