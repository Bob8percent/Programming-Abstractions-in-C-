#include "Rational.h"
#include <iostream>

//	x/yの約分
void reduction(int& x, int& y);

Rational::Rational()
{
	num = 0;
	den = 1;
}

Rational::Rational(int n)
{
	num = n;
	den = 1;
}

Rational::Rational(int x, int y)
{
	//	分母が0のとき
	if (y == 0)
	{
		std::cerr << "ERROR : Rational::Rational(int x, int y) : yは分母に相当するので0以外を入力してください" << std::endl;
		std::exit(EXIT_FAILURE);
	}
	else if (x == 0)
	{
		//	有理数0は0/1で表す
		y = 1;
	}
	else
	{
		//	約分する
		num = x;
		den = y;
		reduction(num, den);
	}
}

//	x,yが非0であるという前提で実装した
void reduction(int& x, int& y)
{
	if (x == 0)
	{
		y = 1;
		return;
	}

	int gcd = 1;
	{
		//	最大公約数求める
		int a = std::abs(x), b = std::abs(y);
		while (1)
		{
			int d = a % b;
			if (d == 0)
			{
				gcd = b;
				break;
			}

			a = b;
			b = d;
		}
	}

	x /= gcd;
	if (y < 0)x = -x;
	y = std::abs(y / gcd);
}

Rational Rational::operator+(const Rational& rhs)
{
	int newNum = num * rhs.den + den * rhs.num;
	int newDen = den * rhs.den;
	
	reduction(newNum, newDen);
	return Rational(newNum, newDen);
}

Rational Rational::operator-(const Rational& rhs)
{
	int newNum = num * rhs.den - den * rhs.num;
	int newDen = den * rhs.den;

	reduction(newNum, newDen);
	return Rational(newNum, newDen);
}

Rational Rational::operator*(const Rational& rhs)
{
	int newNum = num * rhs.num;
	int newDen = den * rhs.den;

	reduction(newNum, newDen);
	return Rational(newNum, newDen);
}

Rational Rational::operator/(const Rational& rhs)
{
	if (rhs.num == 0)
	{
		std::cerr << "ERROR : Rational Rational::operator/(const Rational& rhs) : 右オペランドが0です" << std::endl;
		std::exit(EXIT_FAILURE);
	}

	return (*this) * Rational(rhs.den, rhs.num);
}

Rational& Rational::operator+=(const Rational& rhs)
{
	num = num * rhs.den + den * rhs.num;
	den *= rhs.den;

	reduction(num, den);
	return *this;
}
Rational& Rational::operator-=(const Rational& rhs)
{
	num = num * rhs.den - den * rhs.num;
	den *= rhs.den;

	reduction(num, den);
	return *this;
}

Rational& Rational::operator*=(const Rational& rhs)
{
	num *= rhs.num;
	den *= rhs.den;

	reduction(num, den);
	return *this;
}

Rational& Rational::operator/=(const Rational& rhs)
{
	if (rhs.num == 0)
	{
		std::cerr << "ERROR : Rational& Rational::operator/=(const Rational& rhs) : 右オペランドが0です" << std::endl;
		std::exit(EXIT_FAILURE);
	}

	return (*this) *= Rational(rhs.den, rhs.num);
}

Rational Rational::operator+(int rhs)
{
	return Rational(num + den * rhs, den);
}

Rational Rational::operator-(int rhs)
{
	return (*this) + (-rhs);
}

Rational Rational::operator*(int rhs)
{
	int newNum = num * rhs;
	int newDen = den;

	reduction(newNum, newDen);
	return Rational(newNum, newDen);
}

Rational Rational::operator/(int rhs)
{
	if (rhs == 0)
	{
		std::cerr << "ERROR : Rational Rational::operator/(int rhs) : 右オペランドが0です" << std::endl;
		std::exit(EXIT_FAILURE);
	}

	int newNum = num;
	int newDen = den * rhs;

	reduction(newNum, newDen);
	return Rational(newNum, newDen);
}

Rational operator+(int lhs, const Rational& rhs)
{
	return Rational(rhs.num, rhs.den) + lhs;
}

Rational operator-(int lhs, const Rational& rhs)
{
	return Rational(rhs.num, rhs.den) - lhs;
}

Rational operator*(int lhs, const Rational& rhs)
{
	return Rational(rhs.num, rhs.den) * lhs;
}

Rational operator/(int lhs, const Rational& rhs)
{
	return Rational(rhs.num, rhs.den) / lhs;
}

Rational& Rational::operator+=(int rhs)
{
	num += den * rhs;
	return *this;
}

Rational& Rational::operator-=(int rhs)
{
	num -= den * rhs;
	return *this;
}

Rational& Rational::operator*=(int rhs)
{
	num *= rhs;

	reduction(num, den);
	return *this;
}

Rational& Rational::operator/=(int rhs)
{
	if (rhs == 0)
	{
		std::cerr << "ERROR : Rational& Rational::operator/=(int rhs) : 右オペランドが0です" << std::endl;
		std::exit(EXIT_FAILURE);
	}

	den *= rhs;

	reduction(num, den);
	return *this;
}

bool Rational::operator==(const Rational& rhs)
{
	return (num == rhs.num) && (den == rhs.den);
}

bool Rational::operator!=(const Rational& rhs)
{
	return !(*this == rhs);
}

std::ostream& operator<<(std::ostream& os, const Rational& rhs)
{
	return os << rhs.num << '/' << rhs.den;
}

