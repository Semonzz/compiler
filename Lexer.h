#pragma once
#include "HashTable.h"
#include "dfa.h"

class Lexer {
private:
	string nextLexeme(ifstream& file);
	void insert(HashTable& table, int state, int st, string type_lexeme, string lexeme);

public:
	Lexer() {}

	void analyze(string path_input_file);

	~Lexer() {}
};