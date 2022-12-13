#include <iostream>
#include <cctype>
#include <sstream>
#include <fstream>
#include <string>
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

int main() {
	EvaluationContext<ValueType> context;
	Expression<ValueType>* exp = nullptr;
	TokenScanner scanner;
	scanner.ignoreWhitespace();
	scanner.scanNumbers();

	while (1) {
		exp = nullptr;

		std::cout << "> ";
		std::string line;
		//	入力
		std::getline(std::cin, line);
		if (line == "quit")break;

		//	字句解析
		scanner.setInput(line);

		//	構文解析
		exp = parseExp(scanner);
		ValueType value = exp->eval(context);
		std::cout << "解析結果 : " << value << std::endl;
		listVariables(exp);

		delete exp;
	}
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
	if (t == TokenScanner::TokenType::OPERATOR) {
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
