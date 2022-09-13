#include <iostream>
#include <cctype>
#include <sstream>
#include "Library/stack.h"
#include "Rational.h"

void runRPN();
Rational stringToRational(const std::string& str);

int main()
{
	runRPN();
}

void runRPN()
{
	const std::string operators = "+-*/";
	Stack<Rational> operands;

	while (1)
	{
		std::string line = "";
		std::getline(std::cin, line);
		char ch = toupper(line.at(0));
		if (isdigit(ch))
		{
			operands.push(stringToRational(line));
		}
		else if (ch == 'Q')
		{
			return;
		}
		else
		{
			Rational r1 = operands.pop();
			Rational r2 = operands.pop();
			Rational result;
			switch (ch)
			{
			case '/':
				result = r2 / r1;
				break;
			case '*':
				result = r2 * r1;
				break;
			case '+':
				result = r2 + r1;
				break;
			case '-':
				result = r2 - r1;
				break;
			default:
				break;
			}
			operands.push(result);
			std::cout << result << std::endl;
		}
	}
}

Rational stringToRational(const std::string& str)
{
	std::istringstream iss(str);
	int value;
	iss >> value >> std::skipws;
	if (!iss.fail() && iss.eof())
	{
		return Rational(value);
	}

	std::cerr << "ERROR : Rational stringToRational(const std::string& str)"
		<< " : 文字列を有理数に変換できません" << std::endl;
}
