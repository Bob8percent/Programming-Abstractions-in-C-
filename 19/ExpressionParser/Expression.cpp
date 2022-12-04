#include "Expression.h"
#include <iostream>

int Expression::getConstantValue() const {
	std::cerr << "Illigal : int Expression::getConstantValue() const" << std::endl;
	std::exit(EXIT_FAILURE);

	return 0;
}

std::string Expression::getIdentifierName() const {
	std::cerr << "Illigal : std::string Expression::getIdentifierName() const" << std::endl;
	std::exit(EXIT_FAILURE);

	return "";
}

std::string Expression::getOperator() const {
	std::cerr << "Illigal : std::string Expression::getOperator() const" << std::endl;
	std::exit(EXIT_FAILURE);

	return "";
}

Expression* Expression::getLHS() const {
	std::cerr << "Illigal : Expression* Expression::getLHS() const" << std::endl;
	std::exit(EXIT_FAILURE);

	return nullptr;
}

Expression* Expression::getRHS() const {
	std::cerr << "Illigal : Expression* Expression::getRHS() const" << std::endl;
	std::exit(EXIT_FAILURE);

	return nullptr;
}

/*
* =================================================================================================
* ConstactExpクラス
* =================================================================================================
*/
ConstantExp::ConstantExp(int value) {
	this->value = value;
}


int ConstantExp::eval(EvaluationContext& context) const {
	return value;
}

std::string ConstantExp::toString() const {
	int tmp = value;
	std::string s;
	while (tmp > 0) {
		s = std::string(1, (tmp % 10) + '0') + s;
		tmp /= 10;
	}

	return s;
}

ExpressionType ConstantExp::getType() const {
	return CONSTANT;
}

int ConstantExp::getConstantValue() const {
	return value;
}

/*
* =================================================================================================
* IdentifierExpクラス
* =================================================================================================
*/
IdentifierExp::IdentifierExp(const std::string& name) {
	this->name = name;
	
}

int IdentifierExp::eval(EvaluationContext& context) const {
	if (!context.isDefined(name)) {
		std::cerr << "ERROR : int IdentifierExp::eval(EvaluationContext& context) const : "
			<< "nameが定義されていません" << std::endl;
		std::exit(EXIT_FAILURE);
	}

	return context.getValue(name);
}

std::string IdentifierExp::toString() const {
	return name;
}

ExpressionType IdentifierExp::getType() const {
	return IDENTIFIER;
}

std::string IdentifierExp::getIdentifierName() const {
	return name;
}

/*
* =================================================================================================
* CompoundExpクラス
* =================================================================================================
*/
CompoundExp::CompoundExp(const std::string& op, Expression* rhs, Expression* lhs) {
	this->op = op;
	this->rhs = rhs;
	this->lhs = lhs;
}

CompoundExp::~CompoundExp() {
	//	再帰的に式木すべてが解放する
	delete rhs;
	delete lhs;
}

int CompoundExp::eval(EvaluationContext& context) const {
	int right = rhs->eval(context);
	if (op == "=") {
		context.setValue(lhs->getIdentifierName(), right);
		return right;
	}

	int left = lhs->eval(context);
	if (op == "+")return left + right;
	if (op == "-")return left - right;
	if (op == "*")return left * right;
	if (op == "/") {
		if (right == 0) {
			std::cerr << "ERROR : int CompoundExp::eval(EvaluationContext& context) const : "
				<< "ゼロ除算が発生しました" << std::endl;
			std::exit(EXIT_FAILURE);
		}

		return left / right;
	}

	std::cerr << "ERROR : int CompoundExp::eval(EvaluationContext& context) const : "
		<< "演算子" << op << "が不適です" << std::endl;
	std::exit(EXIT_FAILURE);
	return 0;
}

std::string CompoundExp::toString() const {
	return '(' + lhs->toString() + ' ' + op + ' ' + rhs->toString() + ')';
}

ExpressionType CompoundExp::getType() const {
	return COMPOUND;
}

std::string CompoundExp::getOperator() const {
	return op;
}

Expression* CompoundExp::getLHS() const {
	return lhs;
}

Expression* CompoundExp::getRHS() const {
	return rhs;
}

/*
* =================================================================================================
* EvaluationContextクラス
* =================================================================================================
*/
void EvaluationContext::setValue(const std::string& var, int value) {
	symbolTable[var] = value;
}

int EvaluationContext::getValue(const std::string& var) const {
	return symbolTable.at(var);
}

bool EvaluationContext::isDefined(const std::string& var) const {
	return symbolTable.contains(var);
}
