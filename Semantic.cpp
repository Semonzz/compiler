#include "Node.h"

void Node::semanticErrors() {
	if (children.size() == 0) return;

	for (int i = 0; i < children.size(); i++) children[i].semanticErrors();

	string currType = "";
	int currLine = 0;
	for (int i = children.size() - 1; i >= 0; i--) {
		if (children[i].type != currType) {
			currType = children[i].type;
			currLine = children[i].line;
			break;
		}
	}

	for (Node tmp : children) {
		if (tmp.type != "" && tmp.type != currType && tmp.data != "Descr" && tmp.data != "Op" && tmp.data != "Operators"  && tmp.data != "Descriptions") {
			cout << "Error in line " << currLine << '\n';
			exit(1);
		}
	}

	line = currLine;
	this->type = currType;
	if (data == "Operators" || data == "Descriptions") this->type = "";
	return;
}

string Node::postfixPrint(int& cnt) {
	if (children.size() == 0) return data + " ";

	string outputStr = "", currStr = "", tmpCnt = "";
	for (int i = 0; i < children.size(); i++) {
		if (children[i].data != "(" && children[i].data != ")" && children[i].data != "}" && children[i].data != "eps") {
			if (children[i].data == ",")cnt++;

			else if (children[i].data == ";" && data == "Descr") {
				tmpCnt += to_string(2 + cnt) + " DECL\n";
				cnt = 0;
			}

			else if (children[i].data == "{" || children[i].data == ";") currStr += '\n';
			else if (children[i].data == "=" || children[i].data == "-" || children[i].data == "+" || children[i].data == "*" || children[i].data == "/") currStr += children[i].data + " ";
			else outputStr += children[i].postfixPrint(cnt);

			if (children[i].data == "FunctionName") currStr += "functionBegin";
			else if (children[i].data == "return") currStr += "functionEnd";
		}
	}
	outputStr += tmpCnt;
	outputStr += currStr;
	return outputStr;
}