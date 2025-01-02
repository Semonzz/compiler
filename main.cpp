#include "HashTable.h"
#include "dfa.h"
#include "nfa_to_dfa.h"
#include "Lexer.h"

int main() {
	Lexer lex;
	Node root("Function");
	lex.analyze("Test1.txt", root);
	int tmp = 0;
	//root.print(0);
	root.semanticErrors();
	cout << root.postfixPrint(tmp);
}
