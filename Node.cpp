#include "Node.h"

Node::Node(string Ndata){
	data = Ndata;
}

void Node::addSon(string s){
	Node n(s);
	children.push_back(n);
}

void Node::addSon(string s, string type, int ln) {
	Node n(s);
	n.line = ln;
	n.type = type;
	children.push_back(n);
}

Node& Node::getSon(int i){
	return children[i];
}

void Node::print(int lvl){
	for (int i = 0; i < lvl; ++i) cout << "  ";
	cout << data << '\n';
	for (Node n : children) n.print(lvl + 1);
}

string Node::getData() {
	return data;
}

vector<Node> Node::getChildren() {
	return children;
}