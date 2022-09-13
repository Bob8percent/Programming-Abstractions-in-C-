#include <iostream>
#include <cctype>
#include <sstream>
#include <fstream>
#include "TokenScanner.h"
#include "Library/queue.h"

void runCalculator();
double _stringToReal(const std::string& str);

int main()
{
	runCalculator();
}

//	演算子に優先順位のない電卓
void runCalculator()
{
	while (1)
	{
		std::string line;
		std::getline(std::cin, line);

		TokenScanner scanner(line);
		scanner.ignoreWhiteSpace();
		Vector<double> operands;
		Vector<char> operators;
		bool hasDot = false;
		std::string beforeToken;
		while (scanner.hasMoreTokens())
		{
			std::string token = scanner.nextToken();
			char ch = token.at(0);
			if (isdigit(ch))
			{
				if (hasDot)
				{
					hasDot = false;
					double decimal = _stringToReal(token) / std::pow(10, token.size());
					if (operands.size() >= 1 && isdigit(beforeToken.at(0)))
					{
						//	表記が"n.4"の形の場合
						operands[operands.size() - 1] += decimal;
					}
					else
					{
						//	表記が".4"という形の場合
						operands.add(decimal);
					}
				}
				else
				{
					operands.add(_stringToReal(token));
				}
			}
			else
			{
				switch (ch)
				{
				case '+':
				case '-':
				case '*':
				case '/':
					operators.add(ch);
					break;
				case '.':
					hasDot = true;
					break;
				default:
					std::cerr << "ERROR : void runCalculator() : 不適な文字列が入力されています" << std::endl;
					std::exit(EXIT_FAILURE);
				}
			}

			if(!hasDot)	beforeToken = token;
		}

		//	計算開始
		for (int i = 0; i < operands.size() - 1; ++i)
		{
			switch (operators[i])
			{
			case '+':
				operands[i + 1] += operands[i];
				break;
			case '-':
				operands[i + 1] = operands[i] - operands[i + 1];
				break;
			case '*':
				operands[i + 1] *= operands[i];
				break;
			case '/':
				operands[i + 1] = operands[i] / operands[i + 1];
				break;
			default:
				break;
			}
		}

		std::cout << ">" << operands[operands.size() - 1] << std::endl;
	}
}

double _stringToReal(const std::string& str)
{
	std::istringstream iss(str);
	double value;
	iss >> value >> std::skipws;

	if (!iss.fail())
	{
		return value;
	}

	std::cerr << "ERROR : double stringToReal(const std::string& str) : 文字列を実数に変換できません" << std::endl;
	std::exit(EXIT_FAILURE);
}

