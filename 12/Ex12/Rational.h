#pragma once
#include <ostream>

class Rational
{
public:
	Rational();
	Rational(int x, int y);
	Rational(int n);

	Rational operator+(const Rational& rhs) const;
	Rational operator-(const Rational& rhs) const;
	Rational operator*(const Rational& rhs) const;
	Rational operator/(const Rational& rhs) const;
	Rational& operator+=(const Rational& rhs);
	Rational& operator-=(const Rational& rhs);
	Rational& operator*=(const Rational& rhs);
	Rational& operator/=(const Rational& rhs);

	Rational operator+(int rhs) const;
	Rational operator-(int rhs) const;
	Rational operator*(int rhs) const;
	Rational operator/(int rhs) const;
	friend Rational operator+(int lhs, const Rational& rhs);
	friend Rational operator-(int lhs, const Rational& rhs);
	friend Rational operator*(int lhs, const Rational& rhs);
	friend Rational operator/(int lhs, const Rational& rhs);
	Rational& operator+=(int rhs);
	Rational& operator-=(int rhs);
	Rational& operator*=(int rhs);
	Rational& operator/=(int rhs);

	bool operator==(const Rational& rhs) const;
	bool operator!=(const Rational& rhs) const;

	bool operator<(const Rational& rhs) const;
	bool operator<=(const Rational& rhs) const;
	bool operator>(const Rational& rhs) const;
	bool operator>=(const Rational& rhs) const;

	Rational operator++(int);
	Rational& operator++();
	Rational operator--(int);
	Rational& operator--();

	friend std::ostream& operator<<(std::ostream& os, const Rational& rhs);

private:
	int num, den;
};

Rational operator+(int lhs, const Rational& rhs);
Rational operator-(int lhs, const Rational& rhs);
Rational operator*(int lhs, const Rational& rhs);
Rational operator/(int lhs, const Rational& rhs);
