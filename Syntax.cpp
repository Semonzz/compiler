#include "Syntax.h"
#include "Token.h"

void Syntax::PrintError() {
    cout << "Error in line " << lineNum << '\n';
    exit(1);
}

void Syntax::SemanticPrintError(string str) {
    cout << "Error in line " << lineNum << ": " << str << '\n';
    exit(1);
}

void Syntax::Function(Node& curr){
    bool errorFlag = 1;
    if (!curr.sonsCreated) {
        curr.addSon("Begin");
        curr.addSon("Descriptions");
        curr.addSon("Operators");
        curr.addSon("End");
        curr.sonsCreated = 1;
    }
    if (!curr.getSon(0).flag) {
        Begin(curr.getSon(0));
        errorFlag = 0;
    }
    else if (!curr.getSon(1).flag) {
        Descriptions(curr.getSon(1));
        errorFlag = 0;
    }
    if (!curr.getSon(2).flag && curr.getSon(1).flag) {
        Operators(curr.getSon(2));
        errorFlag = 0;
    }
    if (!curr.getSon(3).flag && curr.getSon(2).flag) {
        End(curr.getSon(3));
        errorFlag = 0;
    }
    if (lexeme == "ENDF") errorFlag = 0;
    if (errorFlag) PrintError();
}

void Syntax::Begin(Node& curr){
    if (!curr.sonsCreated) {
        curr.addSon("Type");
        curr.addSon("FunctionName");
        curr.addSon("(");
        curr.addSon(")");
        curr.addSon("{");
        curr.sonsCreated = 1;
    }
    if (!curr.getSon(0).flag) Type(curr.getSon(0));
    else if (!curr.getSon(1).flag) FunctionName(curr.getSon(1));
    else if (!curr.getSon(2).flag && lexeme == "(") curr.getSon(2).flag = 1;
    else if (!curr.getSon(3).flag && lexeme == ")" && curr.getSon(2).flag) curr.getSon(3).flag = 1;
    else if (!curr.getSon(4).flag && lexeme == "{" && curr.getSon(3).flag) {
        curr.getSon(4).flag = 1;
        curr.flag = 1;
    }
    else PrintError();
}

void Syntax::End(Node& curr) {
    if (!curr.sonsCreated) {
        curr.addSon("return");
        curr.addSon("Id");
        curr.addSon(";");
        curr.addSon("}");
        curr.sonsCreated = 1;
    }
    if (!curr.getSon(0).flag && lexeme == "return") curr.getSon(0).flag = 1;
    else if (!curr.getSon(1).flag && curr.getSon(0).flag) Id(curr.getSon(1));
    else if (!curr.getSon(2).flag && lexeme == ";" && curr.getSon(1).flag) curr.getSon(2).flag = 1;
    else if (!curr.getSon(3).flag && lexeme == "}" && curr.getSon(2).flag) {
        curr.getSon(3).flag = 1;
        curr.flag = 1;
    }
    else PrintError();
}

void Syntax::FunctionName(Node& curr) {
    if (!curr.sonsCreated) {
        curr.addSon("Id");
        curr.sonsCreated = 1;
    }
    if (!curr.getSon(0).flag) {
        Id(curr.getSon(0));
        if (curr.getSon(0).flag) {
            curr.flag = 1;
        }
    }
    else PrintError();
}

void Syntax::Descriptions(Node& curr) {
    if (!curr.sonsCreated) {
        curr.addSon("Descr");
        curr.sonsCreated = 1;
    }
    bool flag = 1;
    if (!curr.getSon(0).flag) {
        Descr(curr.getSon(0));
        flag = 0;
    }
    else if (curr.getSon(0).flag) {
        if (curr.getChildren().size() == 1 && (lexeme == "int" || lexeme == "double")){
            curr.addSon("Descriptions");
        }
        if (curr.getChildren().size()==1) {
            curr.flag = 1;
        }
        else if (!curr.getSon(1).flag){
            Descriptions(curr.getSon(1));
            if (curr.getSon(1).flag) {
                curr.flag = 1;
            }
        }
    }
    else PrintError();
}

void Syntax::Operators(Node& curr) {
    if (!curr.sonsCreated) {
        curr.addSon("Op");
        
        curr.sonsCreated = 1;
    }
    if (!curr.getSon(0).flag) {
            Op(curr.getSon(0));
    }
    else if (curr.getSon(0).flag) {
        if (curr.getChildren().size()==1 && lexemeType == "id_name")
            curr.addSon("Operators");
        if (curr.getChildren().size() == 1) {
            curr.flag = 1;
        }
        else if (!curr.getSon(1).flag){
           
            Operators(curr.getSon(1));
            if (curr.getSon(1).flag) {
                curr.flag = 1;
            }
        }
    }
    else PrintError();
}

void Syntax::Descr(Node& curr) {
    if (!curr.sonsCreated) {
        curr.addSon("Type");
        curr.addSon("VarList");
        curr.addSon(";");
        curr.sonsCreated = 1;
    }
    if (!curr.getSon(0).flag) Type(curr.getSon(0));
    else if (!curr.getSon(1).flag) {
        VarList(curr.getSon(1));
        if (curr.getSon(1).flag) {
            curr.flag = 1;
        }
    }
    else PrintError();
}

void Syntax::VarList(Node& curr) {
    if (!curr.sonsCreated) {
        curr.addSon("Id");
        curr.sonsCreated = 1;
    }
    if (!curr.getSon(0).flag) {
        Id(curr.getSon(0));

        Token toFind(lexemeType, lexeme, nullptr, lexemeType);
        if (table.isFind(toFind)) {
            SemanticPrintError("Name " + lexeme + " is already used\n");
        }
    }
    else {
        if (lexeme != ";") {
            if (curr.getChildren().size() == 1 && lexeme == ",") {
                curr.addSon(",");
                curr.getSon(1).flag = 1;
                curr.addSon("VarList");
            }
            else if (curr.getChildren().size() == 3 && (lexemeType == "id_name" || lexeme == ",")) {
                if (curr.getChildren().size() > 1 && curr.getSon(1).flag) {
                    VarList(curr.getSon(2));
                    if (curr.getSon(2).flag) {
                        curr.flag = 1;
                    }
                }
                else {
                    curr.flag = 1;
                }
            }
            else PrintError();
        }
        else {
            curr.flag = 1;
        }
    }
}

void Syntax::Type(Node& curr)
{
    if (lexeme == "int") {
        curr.addSon("int", "int", lineNum);
        curr.flag = 1;
    }
    else if (lexeme == "double") {
        curr.addSon("double", "double", lineNum);
        curr.flag = 1;
    }
    else PrintError();
}

void Syntax::Op(Node& curr) {
    if (!curr.sonsCreated) {
        curr.addSon("Id");
        curr.addSon("=");
        curr.addSon("Expr");
        curr.addSon(";");
        curr.sonsCreated = 1;
    }
    if (!curr.getSon(0).flag) {
        Id(curr.getSon(0));

        Token toFind(lexemeType, lexeme, nullptr, lexemeType);
        if (!table.isFind(toFind)) {
            SemanticPrintError("Name " + lexeme + " is not defined\n");
        }
    }
    else if (!curr.getSon(1).flag && lexeme == "=") curr.getSon(1).flag = 1;
    else if (!curr.getSon(2).flag && curr.getSon(1).flag) {
        Expr(curr.getSon(2));
        if(curr.getSon(2).flag && lexeme==";")curr.flag = 1;
    }
    else PrintError();
}

void Syntax::SimpleExpr(Node& curr) {
    if (!curr.sonsCreated) {
        if (lexeme == "(") {
            curr.addSon("(");
            curr.addSon("Expr");
            curr.addSon(")");
            curr.sonsCreated = 1;
        }
        else if (lexemeType == "int_num" || lexemeType == "double_num") {
            curr.addSon("Const");
            curr.sonsCreated = 1;
        }
        else if (lexemeType == "id_name") {
            curr.addSon("Id");
            curr.sonsCreated = 1;
        }
        else PrintError();
    }
    if (curr.getSon(0).getData() == "(") {
        if (!curr.getSon(0).flag && lexeme == "(") {
            curr.getSon(0).flag = 1;
        }
        else if (!curr.getSon(1).flag && (lexeme == "+" || lexeme == "-" || lexeme == "*" || lexeme == "/" || lexeme == "(" || lexemeType == "int_num" || lexemeType == "double_num" || lexemeType == "id_name") && curr.getSon(0).flag) {
            Expr(curr.getSon(1));
        }
        else if (!curr.getSon(2).flag && lexeme == ")") {
            Expr(curr.getSon(1));
            curr.getSon(2).flag = 1;
            curr.flag = 1;
        }
        else PrintError();
    }
    else if (curr.getSon(0).getData() == "Const") {
        Const(curr.getSon(0));
        if (curr.getSon(0).flag) {
            curr.flag = 1;
        }
    }
    else if (curr.getSon(0).getData() == "Id") {
        Id(curr.getSon(0));

        Token toFind(lexemeType, lexeme, nullptr, lexemeType);
        if (!table.isFind(toFind)) {
            SemanticPrintError("Name " + lexeme + " is not defined\n");
        }

        if (curr.getSon(0).flag) {
            curr.flag = 1;
        }
    }
    else PrintError();
}

void Syntax::Expr(Node& curr) {
    bool flag = 1;
    if (!curr.sonsCreated) {
        curr.addSon("Term");
        curr.addSon("ExprOther");
        curr.sonsCreated = 1;
    }
    if (!curr.getSon(0).flag) {
        Term(curr.getSon(0));
        flag = 0;
    }
    if (!curr.getSon(1).flag && curr.getSon(0).flag) {
        ExprOther(curr.getSon(1));
        if (curr.getSon(1).flag) {
            curr.flag = 1;
        }
        flag = 0;
    }
    if (flag) PrintError();
}

void Syntax::ExprOther(Node& curr)
{
    if (lexeme == "return") PrintError();
    if (curr.getChildren().size()==0 && !curr.sonsCreated && (lexeme == ")" || lexeme == ";")) {
        curr.addSon("eps");
        curr.sonsCreated = 1;
        curr.flag = 1;
    }
    else {
        if (!curr.sonsCreated) {
            if (lexeme == "+") {
                curr.addSon("+");
                curr.addSon("Term");
                curr.addSon("ExprOther");
            }
            else if (lexeme == "-") {
                curr.addSon("-");
                curr.addSon("Term");
                curr.addSon("ExprOther");
            }
            curr.sonsCreated = 1;
        }
        bool flag = 1;
        if (curr.getChildren().size() > 0 && !curr.getSon(0).flag) {
            curr.getSon(0).flag = 1;
            flag = 0;
        }
        else if (curr.getChildren().size() > 0 && !curr.getSon(1).flag && curr.getSon(0).flag) {
            Term(curr.getSon(1));
            if (lexeme == ";" && curr.getSon(1).flag) {
                curr.flag = 1;
            }
            flag = 0;
        }
        if (curr.getChildren().size() > 0 && !curr.getSon(2).flag && curr.getSon(1).flag) {
            ExprOther(curr.getSon(2));
            if (curr.getSon(2).flag) {
                curr.flag = 1;
            }
            flag = 0;
        }
        if (flag) PrintError();
    }
}

void Syntax::Term(Node& curr) {
    if (!curr.sonsCreated) {
        curr.addSon("SimpleExpr");
        curr.addSon("TermOther");
        curr.sonsCreated = 1;
    }
    if (!curr.getSon(0).flag) {
        SimpleExpr(curr.getSon(0));
    }
    else if (!curr.getSon(1).flag) {
        TermOther(curr.getSon(1));
        if (curr.getSon(1).flag) {
            curr.flag = 1;
        }
    }
    else PrintError();
}

void Syntax::TermOther(Node& curr) {
    if (lexeme == "return") PrintError();
    if (!curr.sonsCreated && (lexeme == ")" || lexeme == ";" || lexeme == "+" || lexeme == "-")) {
        curr.addSon("eps");
        curr.sonsCreated = 1;
        curr.flag = 1;
    }
    else {
        if (!curr.sonsCreated) {
            if (lexeme == "*") {
                curr.addSon("*");
                curr.addSon("SimpleExpr");
                curr.addSon("TermOther");
            }
            else if (lexeme == "/") {
                curr.addSon("/");
                curr.addSon("SimpleExpr");
                curr.addSon("TermOther");
            }
            else
                curr.sonsCreated = 1;
        }
        if (curr.getChildren().size() > 0 && !curr.getSon(0).flag) {
            curr.getSon(0).flag = 1;
        }
        else if (curr.getChildren().size() > 0 && !curr.getSon(1).flag && curr.getSon(0).flag) {
            SimpleExpr(curr.getSon(1));
        }
        else if (curr.getChildren().size() > 0 && !curr.getSon(2).flag && curr.getSon(1).flag) {
            TermOther(curr.getSon(2));
            if (curr.getSon(2).flag) {
                curr.flag = 1;
            }
        }
        else PrintError();
    }
}

void Syntax::Id(Node& curr){
    if (lexemeType == "id_name") {
        Token find = table.find(lexeme);
        curr.addSon(lexeme, find.typeLex, lineNum);
        curr.flag = 1;
    }
    else PrintError();
}

void Syntax::Const(Node& curr){
    if (lexemeType == "int_num") {
        curr.addSon(lexeme, "int", lineNum);
        curr.flag = 1;
    }
    else if (lexemeType == "double_num") {
        curr.addSon(lexeme, "double", lineNum);
        curr.flag = 1;
    }
    else PrintError();
}

void Syntax::push(Node& root, string lexemType, int line, string lexem){
    lexemeType = lexemType;
    lexeme = lexem;
    lineNum = line;
	Function(root);
}