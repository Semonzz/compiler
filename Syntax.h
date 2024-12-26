#pragma once
#include "Node.h"
#include "HashTable.h"

class Syntax {
private:
	int i, lineNum;
	string lexemeType, lexeme;
	HashTable& table;
	void Function(Node& curr);
	void Begin(Node& curr);
	void Descriptions(Node& curr);
	void Operators(Node& curr);
	void End(Node& curr);
	void Type(Node& curr);
	void FunctionName(Node& curr);
	void Op(Node& curr);
	void Descr(Node& curr);
	void VarList(Node& curr);
	void Expr(Node& curr);
	void SimpleExpr(Node& curr);
	void Const(Node& curr);
	void Id(Node& curr);
	void Term(Node& curr);
	void ExprOther(Node& curr);
	void TermOther(Node& curr);
	void PrintError();
	void SemanticPrintError(string str);
public:
	Syntax(HashTable& table) : table(table) {};
	void push(Node& root, string lexemType, int line, string lexeme);
};