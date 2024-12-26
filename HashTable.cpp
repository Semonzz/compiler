#include "HashTable.h"

int HashTable::hash(string key) {
	int index = 0;
	for (int i = 0; i < key.size(); i++) {
		index += int(key[i]);
		index %= sz;
	}
	return index;
}

HashTable::~HashTable() {
	delete[] table;
}

void HashTable::insert(Token token) {
	int index = hash(token.value);
	if (table[index].value=="") {
		table[index] = token;
	}
	else {
		Token* curr = &table[index];
		while (curr->next!=nullptr) {
			curr = curr->next;
		}
		curr->next = &token;
	}
}

void HashTable::print() {
	for (int i = 0; i < sz; i++) {
		if (table[i].type != "") {
			Token* curr = &table[i];
			while (curr->next != nullptr && curr->type!="") {
				cout << curr->type << " \t|\t" << curr->value << "\t|\t" << i << '\n';
				curr = curr->next;
			}
			if(curr->type!="")cout << curr->type << " \t|\t" << curr->value << "\t|\t" << i << '\n';
		}
	}
}

void HashTable::printToFile(string path) {
	ofstream out(path);
	for (int i = 0; i < sz; i++) {
		if (table[i].type != "") {
			Token* curr = &table[i];
			while (curr->next != nullptr && curr->type != "") {
				out << curr->type << " \t|\t" << curr->value << "\t|\t" << i << '\n';
				curr = curr->next;
			}
			if (curr->type != "")out << curr->type << " \t|\t" << curr->value << "\t|\t" << i << '\n';
		}
	}
	out.close();
}

bool HashTable::isFind(Token& other) {
	int index = hash(other.value);
	if (table[index].value.size() != 0) {
		if (table[index].next != nullptr) {
			Token* curr = &table[index];
			while (curr->next != nullptr) {
				if (other.value != curr->value)curr = curr->next;
				else return 1;
			}
			return 0;
		}
		else {
			if (table[index].value != other.value) return 0;
			else return 1;
		}
	}
	else return 0;
}

Token HashTable::find(string lexeme) {
	int index = hash(lexeme);
	Token emptyToken;
	if (table[index].value.size() != 0) {
		if (table[index].next != nullptr) {
			Token* curr = &table[index];
			while (curr->next != nullptr) {
				if (lexeme != curr->value)curr = curr->next;
				else return *curr;
			}
			return emptyToken;
		}
		else {
			if (table[index].value != lexeme) return emptyToken;
			else return table[index];
		}
	}
	else return emptyToken;
}