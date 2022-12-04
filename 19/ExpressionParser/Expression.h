#pragma once
#include <map>
#include <string>

class EvaluationContext;

enum ExpressionType {
	CONSTANT, IDENTIFIER, COMPOUND
};

//	(整数)式木の各ノードの親クラス。
//	継承を使うのは様々なノードをExpressionポインタで表現できることからコードがすっきりするので合理的
//	また、すべてのExpression型は一度作成されたら変更できない。
class Expression
{
public:
	Expression() {}
	virtual ~Expression() {}	//	子クラスのデストラクタも呼ばれるようするためのvirtual

	virtual int eval(EvaluationContext& context) const = 0;
	virtual std::string toString() const = 0;
	virtual ExpressionType getType() const = 0;

	virtual int getConstantValue() const;
	virtual std::string getIdentifierName() const;
	virtual std::string getOperator() const;
	virtual Expression* getLHS() const;
	virtual Expression* getRHS() const;
};

/*
* =================================================================================================
* ConstactExpクラス
* =================================================================================================
*/
class ConstantExp :public Expression {
public:
	ConstantExp(int value);
	~ConstantExp() {}

	virtual int eval(EvaluationContext& context) const;
	virtual std::string toString() const;
	virtual ExpressionType getType() const;

	virtual int getConstantValue() const;

private:
	int value;
};

/*
* =================================================================================================
* IdentifierExpクラス
* =================================================================================================
*/
class IdentifierExp :public Expression {
public:
	IdentifierExp(const std::string& name);
	~IdentifierExp() {}
	virtual int eval(EvaluationContext& context) const;
	virtual std::string toString() const;
	virtual ExpressionType getType() const;

	virtual std::string getIdentifierName() const;

private:
	std::string name;
};

/*
* =================================================================================================
* CompoundExpクラス
* =================================================================================================
*/
class CompoundExp :public Expression {
public:
	CompoundExp(const std::string& op, Expression* rhs, Expression* lhs);
	~CompoundExp();
	virtual int eval(EvaluationContext& context) const;
	virtual std::string toString() const;
	virtual ExpressionType getType() const;

	virtual std::string getOperator() const;
	virtual Expression* getLHS() const;
	virtual Expression* getRHS() const;

private:
	Expression* rhs;
	Expression* lhs;
	std::string op;
};

/*
* =================================================================================================
* EvaluationContextクラス
* =================================================================================================
*/
class EvaluationContext {
public:
	EvaluationContext() {}
	void setValue(const std::string& var, int value);
	int getValue(const std::string& var) const;
	bool isDefined(const std::string& var) const;

private:
	std::map<std::string, int> symbolTable;
};
