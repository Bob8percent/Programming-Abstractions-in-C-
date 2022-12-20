#include <iostream>
#include <cctype>
#include <sstream>
#include <fstream>
#include <string>
#include "Expression.h"
#include "Library/tokenscanner.h"
#include "Library/strlib.h"

//	算術演算に限定したインタプリタの作成

Expression* parseExp(TokenScanner& scanner);
Expression* readE(TokenScanner& scanner, int prec);
Expression* readT(TokenScanner& scanner);
int precedence(const std::string& token);

int main() {
	EvaluationContext context;
	Expression* exp = nullptr;
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
		int value = exp->eval(context);
		std::cout << value << std::endl;

		delete exp;
	}
}

Expression* parseExp(TokenScanner& scanner) {
	//	構文木の作成(再帰下降構文解析を行う)
	Expression* exp = readE(scanner, 0);	//	ルートノードを取得。下から上の階層に向かって構文木を作成していくイメージ
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
Expression* readE(TokenScanner& scanner, int prec) {
	Expression* exp = readT(scanner);	//	lhs

	std::string op;
	//	参照 : http://dai1741.github.io/maximum-algo-2012/docs/parsing/
	//	基本的に上のURLと同じことをしている
	while (1) {
		op = scanner.nextToken();
		int tprec = precedence(op);
		if (tprec <= prec)break;	//	優先度低いときは抜ける

		Expression* rhs = readE(scanner, tprec);
		exp = new CompoundExp(op, rhs, exp);
	}

	//	終了または呼び出し元の演算子のほうが優先順位が高いときはsaveして保存して後で処理
	scanner.saveToken(op);
	return exp;
}

//	T -> integer
//	T -> identifier
//	T -> ( E )
Expression* readT(TokenScanner& scanner) {
	std::string token = scanner.nextToken();
	TokenScanner::TokenType t = scanner.getTokenType(token);
	if (t == TokenScanner::TokenType::WORD)return new IdentifierExp(token);
	if (t == TokenScanner::TokenType::NUMBER)return new ConstantExp(stringToInteger(token));

	//	( E )に関する処理
	if (token != "(") {
		std::cerr << "ERROR : Expression * readT(TokenScanner & scanner) : "
			<< "違法な文法です" << std::endl;
		std::exit(EXIT_FAILURE);
	}
	Expression* exp = readE(scanner, 0);	//	parseExpと同様に再度構文解析開始
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
	if (token == "*" || token == "/")return 3;
	return 0;
}

