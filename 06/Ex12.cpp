#include <iostream>
#include <cctype>
#include <sstream>
#include <fstream>
#include "TokenScanner.h"
#include "Library/queue.h"
#include "Library/map.h"

void runCalculator();
double _stringToReal(const std::string& str);

int main()
{
	runCalculator();
}

//	演算子に優先順位のない電卓
void runCalculator()
{

	Map<std::string, double> variableDict;	//	変数(シンボル)と値の関連付け	

	while (1)
	{
		std::string line;
		std::getline(std::cin, line);
		TokenScanner scanner(line);
		scanner.ignoreWhiteSpace();
		Vector<std::string> tokens;
		Stack<double> operands;
		Stack<char> operators;
		while (scanner.hasMoreTokens())
		{
			std::string token = scanner.nextToken();
			tokens.add(token);
		}

		//	後ろから読む
		for (int i = tokens.size() - 1; i >= 0; --i)
		{
			char ch = tokens[i].at(0);

			if (isdigit(ch))
			{
				operands.push(_stringToReal(tokens[i]));
			}
			else
			{
				switch (ch)
				{
				case '+':
				case '-':
				case '*':
				case '/':
				case '=':
					operators.push(ch);
					break;
				default:
					//	数字、一部の演算子以外の文字列は変数とみなす
					if (variableDict.containsKey(tokens[i]))
					{
						if (!operators.isEmpty() && operators.peek() == '=')
						{
							//	変数の再定義
							variableDict.put(tokens[i], operands.peek());
							operators.pop();
						}
						else
						{
							//	オペランドに変換
							operands.push(variableDict.get(tokens[i]));
						}
					}
					else if (operators.peek() == '=')
					{
						//	変数を新しく定義
						variableDict.put(tokens[i], operands.peek());
					}
					else
					{
						std::cerr << "ERROR : void runCalculator() : "
							<< "変数" << tokens[i] << "が定義されていません" << std::endl;
						std::exit(EXIT_FAILURE);
					}
					break;
				}
			}

			//	算術演算
			if (operands.size() == 2)
			{
				double lhs = operands.pop();
				double rhs = operands.pop();
				switch (operators.pop())
				{
				case '+':
					operands.push(lhs + rhs);
					break;
				case '-':
					operands.push(lhs - rhs);
					break;
				case '*':
					operands.push(lhs * rhs);
					break;
				case '/':
					operands.push(lhs / rhs);
					break;
				default:
					std::cerr << "ERROR : void runCalculator() : "
						<< "不適な入力がなされています" << std::endl;
					std::exit(EXIT_FAILURE);
					break;
				}
			}
		}

		//	計算結果出力
		std::cout << "> " << operands.pop() << std::endl;
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
