#pragma once
#include <string>
class Employee
{
public:
	Employee(const std::string& name) { this->name = name; }

	//	virtualキーワードがなくてもgetNameをオーバーライドできるが、
	//	オブジェクトの構築方法ではなく、宣言方法に基づいて、呼び出すメソッドのバージョンを決定する
	//	このとき、サブクラスのgetName は、サブクラスとして宣言された変数に対してのみ使用される
	std::string getName() { return name; }

	//	純粋仮想関数。仮想関数の一種。
	//	サブクラスによってのみ定義される
	virtual double getPay() = 0;

private:
	std::string name;
};

class HourlyEmployee :public Employee
{
public:
	HourlyEmployee(const std::string& name) :Employee(name) {}

	//	サブクラスでのvirtualキーワードは、オーバーライドしていることをコンパイラに伝える役目を持っている
	virtual double getPay() { return hourlyRate * hoursWorked; }

	void setHourlyRate(double rate) { hourlyRate = rate; }
	void setHoursWorked(double hours) { hoursWorked = hours; }

private:
	double hoursWorked;	//	時間
	double hourlyRate;	//	時給
};

class CommissionEmployee :public Employee {
public:
	CommissionEmployee(const std::string& name) :Employee(name) {}

	virtual double getPay() {
		//	収入は売上に依存する
		return basedSalary + sales * commissionRate;
	}

	void setBasedSalary(double dollars) { basedSalary = dollars; }
	void setCommissionRate(double rate) { commissionRate = rate; }
	void setSalaryVolume(double dollars) { sales = dollars; }

private:
	double sales;			//	売上
	double basedSalary;		//	基本給
	double commissionRate;	//	手数料率
};

class SalariedEmployee :public Employee {
public:
	SalariedEmployee(const std::string& name) :Employee(name) {}

	virtual double getPay() {
		//	労働時間に関係ない固定給
		return salary;
	}

	void setSalary(double salary) { this->salary = salary; }

private:
	double salary;
};
