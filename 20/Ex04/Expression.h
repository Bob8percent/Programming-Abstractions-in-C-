#pragma once
#include <map>
#include <string>
#include <iostream>
#include <set>
#include "Library/strlib.h"

template<typename ValueType>
class EvaluationContext;

enum ExpressionType {
	CONSTANT, IDENTIFIER, COMPOUND, FUNCTION
};

//	(整数)式木の各ノードの親クラス。
//	継承を使うのは様々なノードをExpressionポインタで表現できることからコードがすっきりするので合理的
//	また、すべてのExpression型は一度作成されたら変更できない。
template <typename ValueType>
class Expression
{
public:
	Expression() {}
	virtual ~Expression();	//	子クラスのデストラクタも呼ばれるようするためのvirtual

	virtual ValueType eval(EvaluationContext<ValueType>& context) const = 0;
	virtual std::string toString() const = 0;
	virtual ExpressionType getType() const = 0;

	virtual ValueType getConstantValue() const;
	virtual std::string getIdentifierName() const;
	virtual std::string getOperator() const;
	virtual Expression* getLHS() const;
	virtual Expression* getRHS() const;
	virtual Expression* getArgument() const;
	virtual std::string getFunction() const;
	virtual void setConstantValue(const ValueType& value);
	virtual void setIdentifierName(const std::string& name);
	virtual void setOperator(const std::string& op);
	virtual void setLHS(Expression* lhs);
	virtual void setRHS(Expression* rhs);
	virtual void setArgument(Expression* argument);
	virtual void setFunction(const std::string& function);
};

//	virtual関数は定義が必要。想定外の使用方法を避けるためにエラー処理を記述した

template <typename ValueType>
Expression<ValueType>::~Expression() {
}

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

template <typename ValueType>
Expression<ValueType>* Expression<ValueType>::getArgument() const {
	std::cerr << "Illegal : Expression* Expression::getArgument() const" << std::endl;
	std::exit(EXIT_FAILURE);

	return nullptr;
}

template <typename ValueType>
std::string Expression<ValueType>::getFunction() const {
	std::cerr << "Illegal : std::string Expression::getFunction() const" << std::endl;
	std::exit(EXIT_FAILURE);

	return nullptr;
}

template <typename ValueType>
void Expression<ValueType>::setConstantValue(const ValueType& value){
	std::cerr << "Illegal : void Expression<ValueType>::setConstantValue(const ValueType & value)" << std::endl;
	std::exit(EXIT_FAILURE);
}

template <typename ValueType>
void Expression<ValueType>::setIdentifierName(const std::string& name){
	std::cerr << "Illegal : void Expression<ValueType>::setIdentifierName(const std::string & name)" << std::endl;
	std::exit(EXIT_FAILURE);
}

template <typename ValueType>
void Expression<ValueType>::setOperator(const std::string& op){
	std::cerr << "Illegal : void Expression<ValueType>::setOperator(const std::string & op)" << std::endl;
	std::exit(EXIT_FAILURE);
}

template <typename ValueType>
void Expression<ValueType>::setLHS(Expression<ValueType>* lhs) {
	std::cerr << "Illegal : void Expression<ValueType>::setLHS(Expression<ValueType>* lhs)" << std::endl;
	std::exit(EXIT_FAILURE);
}

template <typename ValueType>
void Expression<ValueType>::setRHS(Expression<ValueType>* rhs) {
	std::cerr << "Illegal : void Expression<ValueType>::setRHS(Expression<ValueType>* rhs)" << std::endl;
	std::exit(EXIT_FAILURE);
}

template <typename ValueType>
void Expression<ValueType>::setArgument(Expression* argument) {
	std::cerr << "Illegal : void Expression<ValueType>::setArgument(Expression<ValueType>* argument)" << std::endl;
	std::exit(EXIT_FAILURE);
}

template <typename ValueType>
void Expression<ValueType>::setFunction(const std::string& function) {
	std::cerr << "Illegal : void Expression<ValueType>::setFunction(const std::string& function)" << std::endl;
	std::exit(EXIT_FAILURE);
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
	virtual void setConstantValue(const ValueType& value);

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

template <typename ValueType>
void ConstantExp<ValueType>::setConstantValue(const ValueType& value) {
	this->value = value;
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
	virtual void setIdentifierName(const std::string& name);

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

template <typename ValueType>
void IdentifierExp<ValueType>::setIdentifierName(const std::string& name) {
	this->name = name;
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

	virtual void setOperator(const std::string& op);
	virtual void setLHS(Expression<ValueType>* lhs);
	virtual void setRHS(Expression<ValueType>* rhs);

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
		std::string identifierName = lhs->getIdentifierName();
		context.setValue(identifierName, right);
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

template <typename ValueType>
void CompoundExp<ValueType>::setOperator(const std::string& op) {
	this->op = op;
}

template <typename ValueType>
void CompoundExp<ValueType>::setLHS(Expression<ValueType>* lhs) {
	this->lhs = lhs;
}

template <typename ValueType>
void CompoundExp<ValueType>::setRHS(Expression<ValueType>* rhs) {
	this->rhs = rhs;
}

/*
* =================================================================================================
* FunctionExpクラス
* =================================================================================================
*/
template <typename ValueType>
class FunctionExp :public Expression<ValueType> {
public:
	FunctionExp(const std::string& function, Expression<ValueType>* argument);
	~FunctionExp();
	virtual ValueType eval(EvaluationContext<ValueType>& context) const;
	virtual std::string toString() const;
	virtual ExpressionType getType() const;

	virtual Expression<ValueType>* getArgument() const;
	virtual std::string getFunction() const;

	virtual void setArgument(Expression<ValueType>* argument);
	virtual void setFunction(const std::string& function);

private:
	std::string function;
	Expression<ValueType>* argument;
};
template<typename ValueType>
FunctionExp<ValueType>::FunctionExp(const std::string& function, Expression<ValueType>* argument) {
	this->function = function;
	this->argument = argument;
}

template<typename ValueType>
FunctionExp<ValueType>::~FunctionExp() {
	delete argument;
}

template<typename ValueType>
ValueType FunctionExp<ValueType>::eval(EvaluationContext<ValueType>& context) const {
	ValueType arg = argument->eval(context);
	if (context.isFuncDefined(function)) {
		return context.getFunction(function)(arg);
	}
	else {
		std::cerr << "ERROR : ValueType FunctionExp::eval(EvaluationContext<ValueType>&context) const : "
			<< "呼び出された関数は不適です" << std::endl;
		std::exit(EXIT_FAILURE);
	}
}

template<typename ValueType>
std::string FunctionExp<ValueType>::toString() const {
	return function + "(" + argument->toString() + ")";
}

template<typename ValueType>
ExpressionType FunctionExp<ValueType>::getType() const {
	return FUNCTION;
}


template<typename ValueType>
Expression<ValueType>* FunctionExp<ValueType>::getArgument() const {
	return argument;
}

template<typename ValueType>
std::string FunctionExp<ValueType>::getFunction() const {
	return function;
}

template<typename ValueType>
void FunctionExp<ValueType>::setArgument(Expression<ValueType>* argument) {
	this->argument = argument;
}

template<typename ValueType>
void FunctionExp<ValueType>::setFunction(const std::string& function) {
	this->function = function;
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

	typedef ValueType (*FnPtr)(ValueType);
	void setFunction(const std::string& name, FnPtr func);
	FnPtr getFunction(const std::string& name) const;
	bool isFuncDefined(const std::string& func) const;

private:
	std::map<std::string, ValueType> symbolTable;
	std::map<std::string, FnPtr> functionTable;
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
void EvaluationContext<ValueType>::setFunction(const std::string& name, FnPtr func) {
	functionTable[name] = func;
}

template <typename ValueType>
EvaluationContext<ValueType>::FnPtr EvaluationContext<ValueType>::getFunction(const std::string& name) const {
	return functionTable.at(name);
}

template <typename ValueType>
bool EvaluationContext<ValueType>::isDefined(const std::string& var) const {
	return symbolTable.contains(var);
}

template <typename ValueType>
bool EvaluationContext<ValueType>::isFuncDefined(const std::string& func) const {
	return functionTable.contains(func);
}


