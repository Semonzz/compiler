#pragma once
#include "Node.h"

class Syntax {
private:
	int i, lineNum;
	string lexemeType, lexeme;
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
public:
	Syntax() {};
	void push(Node& root, string lexemType, int line, string lexeme);
};