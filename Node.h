#pragma once

#include "Head.h"
using namespace std;
class Node{
private:
	string data;
	vector<Node> children;
public:
	bool flag = false, sonsCreated = false;
	Node(string s);
	void addSon(string s);
	Node& getSon(int i);
	void print(int lvl);
	string getData();
	vector<Node> getChildren();
};