#pragma once
#include <string>
class Employee
{
public:
	//	virtualキーワードがなくてもgetNameをオーバーライドできるが、
	//	オブジェクトの構築方法ではなく、宣言方法に基づいて、呼び出すメソッドのバージョンを決定する
	//	このとき、サブクラスのgetName は、サブクラスとして宣言された変数に対してのみ使用される
	std::string getName();

	//	純粋仮想関数。仮想関数の一種。
	//	サブクラスによってのみ定義される
	virtual double getPay() = 0;
};

class HourlyEmployee :public Employee
{
public:
	//	サブクラスでのvirtualキーワードは、オーバーライドしていることをコンパイラに伝える役目を持っている
	virtual double getPay();

	void setHourlyRate(double rate);
	void setHourlyWorked(double hours);
};

class CommissionEmployee :public Employee {
public:
	virtual double getPay();

	void setBasedSalary(double dollars);
	void setCommissionRate(double rate);
	void setSalaryVolume(double dollars);
};

class SalariedEmployee :public Employee {
public:
	virtual double getPay();

	void setSalary(double salary);
};
