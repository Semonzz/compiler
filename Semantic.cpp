#include "Node.h"

void Node::semErr() {
	if (children.size() == 0)
		return;

	for (int i = 0; i < children.size(); i++)
		children[i].semErr();

	string tp = "";
	int ln = 0;
	for (int i = children.size() - 1; i >= 0; i--)
		if (children[i].type != tp) {
			tp = children[i].type;
			ln = children[i].line;
			break;
		}

	for (Node n : children)
		if (n.type != "" && n.type != tp && n.data != "Operators" && n.data != "Op" && n.data != "Descriptions" && n.data != "Descr") {
			cout << "Error in line " << ln << '\n';
			exit(1);
		}

	line = ln;
	this->type = tp;
	if (data == "Operators" || data == "Descriptions")
		this->type = "";
	return;
}

string Node::postfixPrint(int& cnt) {
	if (children.size() == 0)
		return data + " ";

	string str = "", post = "", tmp = "";
	for (int i = 0; i < children.size(); i++) {
		if (children[i].data != "(" && children[i].data != ")" && children[i].data != "}" && children[i].data != "eps") {
			if (children[i].data == ",")
				cnt++;
			else if (children[i].data == ";" && data == "Descr") {
				tmp += to_string(2 + cnt) + " DECL\n";
				cnt = 0;
			}
			else if (children[i].data == "{" || children[i].data == ";") post += '\n';
			else if (children[i].data == "=" || children[i].data == "-" || children[i].data == "+" || children[i].data == "*" || children[i].data == "/") post += children[i].data + " ";
			else str += children[i].postfixPrint(cnt);

			if (children[i].data == "FunctionName") {
				post += "functionBegin";
			}
			else if (children[i].data == "return")
				post += "functionEnd";
		}
	}
	str += tmp;
	str += post;
	return str;
}