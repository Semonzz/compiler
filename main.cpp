#include "HashTable.h"
#include "dfa.h"
#include "nfa_to_dfa.h"
#include "Lexer.h"

int main() {
	Lexer lex;
	Node root("Function");
	lex.analyze("Test1.txt", root);
	root.print(0);
}
