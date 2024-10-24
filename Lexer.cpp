#include "Lexer.h"

char Buf;
string Lexer::nextLexeme(ifstream& file) {
	string word = "";
	char x = '/0';
	char x_op = '/0';
	if ((Buf == '=') || (Buf == '+') || (Buf == '-') || (Buf == '{') || (Buf == '}') || (Buf == ';') || (Buf == '(') || (Buf == ')') || (Buf == ',') || (Buf == '*') || (Buf == '/')) {
		word += Buf;
		Buf = '/0';
		return word;
	}
	else {
		x = file.get();
		if (file.eof()) return word;
	}
	//ñ÷èòûâàíèå ïğîáåëîâ â ôàéëå äî ïåğâîé áóêâû â ñòğîêå;
	while ((!file.eof() && ((x == ' ') || (x == '\n') || (x == '\t')))){
		x = file.get();
	}
	if (!file.eof())
		word += x;
	if ((x == '=') || (x == '+') || (x == '-') || (x == '{') || (x == '}') ||
		(x == ';') || (x == '(') || (x == ')') || (x == ',') || (x == '*') || (x == '/')) {
		return word;
	}
	// Ñ÷èòûâàíèå ñèìâîëîâ äî ğàçäåëèòåëÿ
	while ((!file.eof() && (x != ' ') && (x != '\n') && (x != '\t')))
	{
		x = file.get();
		if ((x == '=') || (x == '+') || (x == '-') || (x == '{') || (x == '}') ||
			(x == ';') || (x == '(') || (x == ')') || (x == ',') || (x == '*') || (x == '/')) {
			Buf = x;
			break;
		}
		if (!file.eof() && (x != ' ') && (x != '\n') && (x != '\t'))
			word += x;
	}

	return word;
}

void Lexer::insert(HashTable& table, int state, int st, string type_lexeme, string lexeme) {
	if (state == st) {
		Token a(type_lexeme, lexeme, nullptr);
		table.insert(a);
	}
}

void Lexer::analyze(string path_input_file) {
	ifstream file(path_input_file);

	dfa my;

	HashTable table;

	string word;
	int state;
	while (!file.eof())
	{
		word.clear();
		word = nextLexeme(file);

		if (word.size() != 0) {
			if (my.isAccept(word, state)) {

				// Êëş÷åâûå ñëîâà (int, double, return)
				insert(table, state, 13, "key_word", word);

				// Îïåğàòîğû (+, -, =)
				insert(table, state, 7, "operator", word);

				// Ğàçäåëèòåëè ({, }, (, ), ;, ,,)
				insert(table, state, 6, "delimiter", word);

				// constant
				insert(table, state, 5, "int_num", word);
				insert(table, state, 15, "double_num", word);

				// Íàçâàíèÿ
				if (state >= 1 && state <= 4 || state >= 8 && state <= 10 || state == 14 || state == 12 || state >= 16 && state <= 19)
					insert(table, state, state, "id_name", word);
			}
			else {
				//âûäàåì ñîîáùåíèå îá îøèáêå ñ ôàéëîì ñ îøèáêàìè;
				insert(table, -1, -1, "Error", word);
				//fout << word << "\n";
			}
		}
	}
	file.close();
	table.print();
	table.printToFile("output.txt");

}