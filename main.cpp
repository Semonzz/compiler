#include "HashTable.h"
#include "dfa.h"
#include "nfa_to_dfa.h"
#include "Lexer.h"

int main() {
	Lexer lex;
	lex.analyze("Test2.txt");
}

//13 - kword
//7 - oper
//6 - delimeter
//5 - int_num
//15 - double_num
//1 2 3 4 8 9 10 12 14 16 17 18 19 - id_name


 //nfaTOdfa();
	//dfa new_dfa;
	//vector<string> str = { "int", "double","return","*","/","+","-","=","{","}","(",")",";",",","122352","1332.1235","aaaasdjicm","i","in","d","do","dou","doub","doubl","r","re","ret","retu","retur","it","ito","dt","dto" };
	//set<int> s;
	//int p;
	//for (int i = 16; i < str.size(); i++)
	//	if (new_dfa.isAccept(str[i], p))
	//		s.insert(p);

	//for (int i : s)
	//	cout << i << ' ';