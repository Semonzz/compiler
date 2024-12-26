#pragma once

#include "Head.h"
using namespace std;
class Node{
private:
	string data;
	string type = "";
	vector<Node> children;
	int line = 1;
public:
	bool flag = false, sonsCreated = false;
	Node(string data);
	void addSon(string s);
	Node& getSon(int i);
	void print(int lvl);
	string getData();
	vector<Node> getChildren();
	string postfixPrint(int& cnt);
	void semErr();
	void addSon(string s, string type, int ln);
};