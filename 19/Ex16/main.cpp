#include <iostream>
#include <cctype>
#include <sstream>
#include <fstream>
#include <string>
#include <stack>
#include "Expression.h"
#include "Library/tokenscanner.h"
#include "Library/strlib.h"

//	算術演算に限定したインタプリタの作成
using ValueType = double;
Expression<ValueType>* parseExp(TokenScanner& scanner);
Expression<ValueType>* readE(TokenScanner& scanner, int prec);
Expression<ValueType>* readT(TokenScanner& scanner);
int precedence(const std::string& token);
void listVariables(Expression<ValueType>* exp);
void listVariables(Expression<ValueType>* exp, std::set<std::string>& variables);
Expression<ValueType>* changeVariable(Expression<ValueType>* exp, 
	const std::string& oldName, const std::string& newName);
bool expMatch(Expression<ValueType>* e1, Expression<ValueType>* e2);
void printRPN(Expression<ValueType>* exp);
void unparse(Expression<ValueType>* exp);

void foldConstants(Expression<ValueType>*& exp);
void foldConstants(ValueType& value, bool& isChildChanged, Expression<ValueType>* exp);

void compile(std::istream& is, std::ostream& os);
void compile(Expression<ValueType>* exp, std::set<std::string>& variables, std::ostream& os);

int main() {
	std::ifstream ifs;
	ifs.open("ch19-ex16.txt");
	if (ifs.fail()) {
		std::cerr << "ERROR : ファイル\"ch19 - ex16.txt\"が開けません" << std::endl;
		std::exit(EXIT_FAILURE);
	}

	compile(ifs, std::cout);
}

Expression<ValueType>* parseExp(TokenScanner& scanner) {
	//	構文木の作成(再帰下降構文解析を行う)
	Expression<ValueType>* exp = readE(scanner, 0);	//	ルートノードを取得。下から上の階層に向かって構文木を作成していくイメージ
	if (scanner.hasMoreTokens()) {
		std::cerr << "ERROR : Expression* parseExp(TokenScanner& scanner) : "
			<< "未処理のトークン\"" << scanner.nextToken() << "\"があります" << std::endl;
		std::exit(EXIT_FAILURE);
	}

	return exp;
}

//	終端記号と非終端記号について。参照：https://detail.chiebukuro.yahoo.co.jp/qa/question_detail/q1166069621

//	E -> T
//	E -> E op E
Expression<ValueType>* readE(TokenScanner& scanner, int prec) {
	Expression<ValueType>* exp = readT(scanner);	//	lhs

	std::string op;
	while (1) {
		op = scanner.nextToken();
		int tprec = precedence(op);
		if (tprec <= prec)break;	//	優先度低いときは抜ける

		Expression<ValueType>* rhs = readE(scanner, tprec);
		exp = new CompoundExp(op, rhs, exp);
	}

	//	終了または呼び出し元の演算子のほうが優先順位が高いときはsaveして保存して後で処理
	scanner.saveToken(op);
	return exp;
}

//	T -> integer
//	T -> identifier
//	T -> ( E )
Expression<ValueType>* readT(TokenScanner& scanner) {
	std::string token = scanner.nextToken();
	TokenScanner::TokenType t = scanner.getTokenType(token);
	if (t == TokenScanner::TokenType::WORD)return new IdentifierExp<ValueType>(token);
	if (t == TokenScanner::TokenType::NUMBER) {
		std::stringstream ss;
		ValueType val;
		ss << token;
		ss >> val;
		return new ConstantExp<ValueType>(val);
	}
	if (token == "+" || token == "-") {
		//	単項演算子を取得した時はreadT()でopにこの演算子文字列を取得させたいのでtoken(-/+)をセーブする
		scanner.saveToken(token);
		return new ConstantExp<ValueType>(0);	//	単項演算子の場合、lhsを0としたCompoundExpを作ることで対処する
	}

	//	( E )に関する処理
	if (token != "(") {
		std::cerr << "ERROR : Expression * readT(TokenScanner & scanner) : "
			<< "違法な文法です" << std::endl;
		std::exit(EXIT_FAILURE);
	}
	Expression<ValueType>* exp = readE(scanner, 0);	//	parseExpと同様に再度構文解析開始
	if (scanner.nextToken() != ")") {	//	()で閉じられていないとき
		std::cerr << "ERROR : Expression * readT(TokenScanner & scanner) : "
			<< "違法な文法です" << std::endl;
		std::exit(EXIT_FAILURE);
	}

	return exp;
}

//	大きいほど優先度高い
//	0のとき、そのtokenはoperatorではないことを意味する
int precedence(const std::string& token) {
	if (token == "=")return 1;
	if (token == "+" || token == "-")return 2;
	if (token == "*" || token == "/" || token == "%")return 3;
	return 0;
}

void listVariables(Expression<ValueType>* exp) {
	std::set<std::string> variables;
	listVariables(exp, variables);
	for (const std::string& e : variables) {
		std::cout << e << std::endl;
	}
}

void listVariables(Expression<ValueType>* exp, std::set<std::string>& variables) {
	ExpressionType et = exp->getType();
	if (et == CONSTANT) {
		return;
	}
	else if (et == IDENTIFIER) {
		variables.insert(exp->getIdentifierName());
		return;
	}
	else if (et == COMPOUND) {
		listVariables(exp->getRHS(), variables);
		listVariables(exp->getLHS(), variables);
		return;
	}

	std::cerr << "ERROR : void listVariables(Expression<ValueType>* exp, std::set<std::string>& variables) : "
		<< "ExpressionTypeが不適当な値となっています" << std::endl;
	std::exit(EXIT_FAILURE);
}

//	注意 : expをルートとする式木は変更しない
Expression<ValueType>* changeVariable(Expression<ValueType>* exp, 
	const std::string& oldName, const std::string& newName) {
	ExpressionType et = exp->getType();
	if (et == CONSTANT) {
		return new ConstantExp<ValueType>(exp->getConstantValue());
	}
	else if (et == IDENTIFIER) {
		std::string name = exp->getIdentifierName();
		if (name == oldName) name = newName;
		return new IdentifierExp<ValueType>(name);
	}
	else if (et == COMPOUND) {
		Expression<ValueType>* rhs = changeVariable(exp->getRHS(), oldName, newName);
		Expression<ValueType>* lhs = changeVariable(exp->getLHS(), oldName, newName);
		return new CompoundExp<ValueType>(exp->getOperator(), rhs, lhs);
	}

	std::cerr << "ERROR : Expression<ValueType>*changeVariable(Expression<ValueType>*exp"
		<< "const std::string & oldName, const std::string& newName) : "
		<< "ExpressionTypeが不適当な値となっています" << std::endl;
	std::exit(EXIT_FAILURE);
}

bool expMatch(Expression<ValueType>* e1, Expression<ValueType>* e2) {
	ExpressionType et = e1->getType();
	if (et != e2->getType())return false;

	if (et == CONSTANT) {
		return e1->getConstantValue() == e2->getConstantValue();
	}
	else if (et == IDENTIFIER) {
		return e1->getIdentifierName() == e2->getIdentifierName();	//	変数の値が同じであることは確認しない
	}
	else if (et == COMPOUND) {
		if (!expMatch(e1->getRHS(), e2->getRHS()))return false;
		if (!expMatch(e1->getLHS(), e2->getLHS()))return false;
		if (e1->getOperator() != e2->getOperator())return false;
		return true;
	}
	
	std::cerr << "ERROR : bool expMatch(Expression<ValueType>* e1, Expression<ValueType>* e2) : "
		<< "ExpressionTypeが不適当な値となっています" << std::endl;
	std::exit(EXIT_FAILURE);
}

void printRPN(Expression<ValueType>* exp) {
	ExpressionType et = exp->getType();

	if (et == CONSTANT) {
		std::cout << exp->getConstantValue() << " ";
	}
	else if (et == IDENTIFIER) {
		std::cout << exp->getIdentifierName() << " ";
	}
	else if (et == COMPOUND) {
		printRPN(exp->getLHS());
		printRPN(exp->getRHS());
		std::cout << exp->getOperator() << " ";
	}
}

//	式木をinorderで探索すれば通常の式の形になる
void unparse(Expression<ValueType>* exp) {
	ExpressionType et = exp->getType();

	if (et == CONSTANT) {
		std::cout << exp->getConstantValue() << " ";
	}
	else if (et == IDENTIFIER) {
		std::cout << exp->getIdentifierName() << " ";
	}
	else if (et == COMPOUND) {
		unparse(exp->getLHS());
		std::cout << exp->getOperator() << " ";
		unparse(exp->getRHS());
	}
}

//	定数計算が1つの値にまとめられた式木に変換する
void foldConstants(Expression<ValueType>*& exp) {
	bool isChanged = false;
	ValueType value;
	foldConstants(value, isChanged, exp);
	if (isChanged) {
		exp = new ConstantExp(value);
	}
}

//	戻り値は変更後の値
void foldConstants(ValueType& value, bool& isChildChanged, Expression<ValueType>* exp) {
	ExpressionType et = exp->getType();

	if (et == COMPOUND) {
		foldConstants(value, isChildChanged, exp->getRHS());
		if (isChildChanged) {
			exp->setRHS(new ConstantExp(value));
			isChildChanged = false;
		}
		foldConstants(value, isChildChanged, exp->getLHS());
		if (isChildChanged != 0) {
			exp->setLHS(new ConstantExp(value));
			isChildChanged = false;
		}

		ExpressionType etLeft = exp->getLHS()->getType();
		ExpressionType etRight = exp->getRHS()->getType();
		std::string op = exp->getOperator();
		//	左右の子がどちらもConstantExpであるCompoundExpのみが変更対象となる
		if (etLeft == CONSTANT && etRight == CONSTANT) {
			if (op != "=") {
				EvaluationContext<ValueType> c;	//	左右の子はどちらも定数であるのでcontextを使う処理は行われないので一時的に作るだけでOK
				value = exp->eval(c);
				delete exp;

				isChildChanged = true;
			}
		}
	}
}

//	スタックマシンへの指示言語へ変換する
//	LOAD #n		: stackに定数nをpush
//	LOAD var	: stackに変数varをpush
//	STORE var	: stackのtop値をvarに格納
//	DISPLAY		: stackをpopして表示
//	ADD, SUB, MUL, DIV : stackから2つの値をpopし(topが右、次のtopが左オペランドを指す)、最終結果をpush
void compile(std::istream& is, std::ostream& os) {
	Expression<ValueType>* exp = nullptr;
	TokenScanner scanner;
	scanner.ignoreWhitespace();
	scanner.scanNumbers();

	std::string line;
	std::set<std::string> variables;
	while (std::getline(is, line)) {
		//	字句解析
		scanner.setInput(line);

		//	構文解析
		exp = parseExp(scanner);

		compile(exp, variables, os);


		delete exp;

		os << "DISPLAY\n";
	}
}

void compile(Expression<ValueType>* exp,std::set<std::string>& variables, std::ostream& os) {
	ExpressionType et = exp->getType();

	if (et == CONSTANT) {
		os << "LOAD #" << exp->getConstantValue() << "\n";
	}
	else if (et == IDENTIFIER) {
		std::string var = exp->getIdentifierName();
		if (variables.contains(var)) {
			os << "LOAD " << var << "\n";
		}
		variables.insert(var);
	}
	else if (et == COMPOUND) {
		compile(exp->getLHS(), variables, os);
		compile(exp->getRHS(), variables, os);

		std::string op = exp->getOperator();
		if (op == "+") os << "ADD\n";
		else if (op == "-")os << "SUB\n";
		else if (op == "*")os << "MUL\n";
		else if (op == "/")os << "DIV\n";
		else if (op == "=")os << "STORE " << exp->getLHS()->getIdentifierName() << "\n";
	}
}
