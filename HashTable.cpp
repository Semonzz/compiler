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
	if (table[index].type=="") {
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