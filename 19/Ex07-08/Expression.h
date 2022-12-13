#pragma once
#include <map>
#include <string>
#include <iostream>
#include "Library/strlib.h"

template<typename ValueType>
class EvaluationContext;

enum ExpressionType {
	CONSTANT, IDENTIFIER, COMPOUND
};

//	(整数)式木の各ノードの親クラス。
//	継承を使うのは様々なノードをExpressionポインタで表現できることからコードがすっきりするので合理的
//	また、すべてのExpression型は一度作成されたら変更できない。
template <typename ValueType>
class Expression
{
public:
	Expression() {}
	virtual ~Expression() {}	//	子クラスのデストラクタも呼ばれるようするためのvirtual

	virtual ValueType eval(EvaluationContext<ValueType>& context) const = 0;
	virtual std::string toString() const = 0;
	virtual ExpressionType getType() const = 0;

	virtual ValueType getConstantValue() const;
	virtual std::string getIdentifierName() const;
	virtual std::string getOperator() const;
	virtual Expression* getLHS() const;
	virtual Expression* getRHS() const;
};

template <typename ValueType>
ValueType Expression<ValueType>::getConstantValue() const {
	std::cerr << "Illegal : ValueType Expression::getConstantValue() const" << std::endl;
	std::exit(EXIT_FAILURE);

	return ValueType();
}

template <typename ValueType>
std::string Expression<ValueType>::getIdentifierName() const {
	std::cerr << "Illegal : std::string Expression::getIdentifierName() const" << std::endl;
	std::exit(EXIT_FAILURE);

	return "";
}

template <typename ValueType>
std::string Expression<ValueType>::getOperator() const {
	std::cerr << "Illegal : std::string Expression::getOperator() const" << std::endl;
	std::exit(EXIT_FAILURE);

	return "";
}

template <typename ValueType>
Expression<ValueType>* Expression<ValueType>::getLHS() const {
	std::cerr << "Illegal : Expression* Expression::getLHS() const" << std::endl;
	std::exit(EXIT_FAILURE);

	return nullptr;
}

template <typename ValueType>
Expression<ValueType>* Expression<ValueType>::getRHS() const {
	std::cerr << "Illegal : Expression* Expression::getRHS() const" << std::endl;
	std::exit(EXIT_FAILURE);

	return nullptr;
}

/*
* =================================================================================================
* ConstactExpクラス
* =================================================================================================
*/
template <typename ValueType>
class ConstantExp :public Expression<ValueType> {
public:
	ConstantExp(ValueType value);
	~ConstantExp() {}

	virtual ValueType eval(EvaluationContext<ValueType>& context) const;
	virtual std::string toString() const;
	virtual ExpressionType getType() const;

	virtual ValueType getConstantValue() const;

private:
	ValueType value;
};

template <typename ValueType>
ConstantExp<ValueType>::ConstantExp(ValueType value) {
	this->value = value;
}

template <typename ValueType>
ValueType ConstantExp<ValueType>::eval(EvaluationContext<ValueType>& context) const {
	return value;
}

template <typename ValueType>
std::string ConstantExp<ValueType>::toString() const {
	std::ostringstream oss;
	oss << value;
	return oss.str();
}

template <typename ValueType>
ExpressionType ConstantExp<ValueType>::getType() const {
	return CONSTANT;
}

template <typename ValueType>
ValueType ConstantExp<ValueType>::getConstantValue() const {
	return value;
}

/*
* =================================================================================================
* IdentifierExpクラス
* =================================================================================================
*/
template <typename ValueType>
class IdentifierExp :public Expression<ValueType> {
public:
	IdentifierExp(const std::string& name);
	~IdentifierExp() {}
	virtual ValueType eval(EvaluationContext<ValueType>& context) const;
	virtual std::string toString() const;
	virtual ExpressionType getType() const;

	virtual std::string getIdentifierName() const;

private:
	std::string name;
};

template <typename ValueType>
IdentifierExp<ValueType>::IdentifierExp(const std::string& name) {
	this->name = name;

}

template <typename ValueType>
ValueType IdentifierExp<ValueType>::eval(EvaluationContext<ValueType>& context) const {
	if (!context.isDefined(name)) {
		std::cerr << "ERROR : ValueType IdentifierExp::eval(EvaluationContext& context) const : "
			<< "nameが定義されていません" << std::endl;
		std::exit(EXIT_FAILURE);
	}

	return context.getValue(name);
}

template <typename ValueType>
std::string IdentifierExp<ValueType>::toString() const {
	return name;
}

template <typename ValueType>
ExpressionType IdentifierExp<ValueType>::getType() const {
	return IDENTIFIER;
}

template <typename ValueType>
std::string IdentifierExp<ValueType>::getIdentifierName() const {
	return name;
}
/*
* =================================================================================================
* CompoundExpクラス
* =================================================================================================
*/
template <typename ValueType>
class CompoundExp :public Expression<ValueType> {
public:
	CompoundExp(const std::string& op, Expression<ValueType>* rhs, Expression<ValueType>* lhs);
	~CompoundExp();
	virtual ValueType eval(EvaluationContext<ValueType>& context) const;
	virtual std::string toString() const;
	virtual ExpressionType getType() const;

	virtual std::string getOperator() const;
	virtual Expression<ValueType>* getLHS() const;
	virtual Expression<ValueType>* getRHS() const;

private:
	Expression<ValueType>* rhs;
	Expression<ValueType>* lhs;
	std::string op;
};

template <typename ValueType>
CompoundExp<ValueType>::CompoundExp(const std::string& op, Expression<ValueType>* rhs, Expression<ValueType>* lhs) {
	this->op = op;
	this->rhs = rhs;
	this->lhs = lhs;
}

template <typename ValueType>
CompoundExp<ValueType>::~CompoundExp() {
	//	再帰的に式木すべてが解放する
	delete rhs;
	delete lhs;
}

template <typename ValueType>
ValueType CompoundExp<ValueType>::eval(EvaluationContext<ValueType>& context) const {
	ValueType right = rhs->eval(context);
	if (op == "=") {
		context.setValue(lhs->getIdentifierName(), right);
		return right;
	}

	ValueType left = lhs->eval(context);
	if (op == "+")return left + right;
	if (op == "-")return left - right;
	if (op == "*")return left * right;
	if (op == "/") {
		if (right == 0) {
			std::cerr << "ERROR : ValueType CompoundExp::eval(EvaluationContext& context) const : "
				<< "\"/\"演算子の計算において、ゼロ除算が発生しました" << std::endl;
			std::exit(EXIT_FAILURE);
		}

		return left / right;
	}
	//if (op == "%") {
	//	if (right == 0) {
	//		std::cerr << "ERROR : ValueType CompoundExp::eval(EvaluationContext& context) const : "
	//			<< "\"%\"演算子の計算において、ゼロ除算が発生しました" << std::endl;
	//		std::exit(EXIT_FAILURE);
	//	}

	//	return left % right;
	//}

	std::cerr << "ERROR : ValueType CompoundExp::eval(EvaluationContext& context) const : "
		<< "演算子" << op << "が不適です" << std::endl;
	std::exit(EXIT_FAILURE);
	return 0;
}

template <typename ValueType>
std::string CompoundExp<ValueType>::toString() const {
	return '(' + lhs->toString() + ' ' + op + ' ' + rhs->toString() + ')';
}

template <typename ValueType>
ExpressionType CompoundExp<ValueType>::getType() const {
	return COMPOUND;
}

template <typename ValueType>
std::string CompoundExp<ValueType>::getOperator() const {
	return op;
}

template <typename ValueType>
Expression<ValueType>* CompoundExp<ValueType>::getLHS() const {
	return lhs;
}

template <typename ValueType>
Expression<ValueType>* CompoundExp<ValueType>::getRHS() const {
	return rhs;
}


/*
* =================================================================================================
* EvaluationContextクラス
* =================================================================================================
*/
template <typename ValueType>
class EvaluationContext {
public:
	EvaluationContext() {}
	void setValue(const std::string& var, ValueType value);
	ValueType getValue(const std::string& var) const;
	bool isDefined(const std::string& var) const;

private:
	std::map<std::string, ValueType> symbolTable;
};

template <typename ValueType>
void EvaluationContext<ValueType>::setValue(const std::string& var, ValueType value) {
	symbolTable[var] = value;
}

template <typename ValueType>
ValueType EvaluationContext<ValueType>::getValue(const std::string& var) const {
	return symbolTable.at(var);
}

template <typename ValueType>
bool EvaluationContext<ValueType>::isDefined(const std::string& var) const {
	return symbolTable.contains(var);
}

