
/*
* ファイルに現れるコメントを無視して出力する。
* 
* 実装過程で苦労したこと：std::size_tは-1になると最大になってしまうので、この型における引き算に注意
* 
* 学んだこと：改行された文字列について、それぞれの文末の文字は'\n'であるという理解でよさそう(また、当然だが文末以外に\nは来ない)。
* std::getline()は改行文字を含めない。
*
*/

#define _USE_MATH_DEFINES

#include <iostream>
#include <fstream>
#include <sstream>
#include <iomanip>
#include <string>
#include <cmath>
#include "String.h"

void promptForOpenFile(std::ifstream& ifs);
void removeComments(std::istream& is, std::ostream& os);
void copyStream(std::istream& is, std::ostream& os);

int main()
{
	std::ifstream ifs;
	promptForOpenFile(ifs);

	removeComments(ifs, std::cout);
	
	
}

void promptForOpenFile(std::ifstream& ifs)
{
	while (1)
	{
		std::cout << "ファイル名：";
		std::string filename = "";
		std::getline(std::cin, filename);

		ifs.open(filename);
		if (!ifs.fail())
		{
			return;
		}

		ifs.clear();
		std::cout << "ファイルが開けません" << std::endl;
	}
}

void removeComments(std::istream& is, std::ostream& os)
{
	std::string newText = "";
	std::size_t startCommentPos = std::string::npos;
	std::size_t endCommentPos = std::string::npos;

	/*
	* ------------------------------------------------------------------------------------------------
	* ダブルクオーテーションコメントの削除
	* ------------------------------------------------------------------------------------------------
	*/
	while (1)
	{
		std::string line = "";
		if (!std::getline(is, line))
		{
			break;
		}
		for (std::size_t i = 1; i < line.length(); ++i)
		{
			if (line.at(i - 1) == '/' && line.at(i) == '/')
			{
				startCommentPos = i - 1;
				break;
			}
		}

		if (startCommentPos == std::string::npos)
		{
			newText += line;
		}
		else
		{
			newText += line.substr(0, startCommentPos);
			startCommentPos = std::string::npos;
		}
		newText += '\n';	//	std::getlineで取得できているということは改行文字が文末にあるのは確定
	}

	/*
	* ------------------------------------------------------------------------------------------------
	* シングルクオーテーションコメントの削除
	* ------------------------------------------------------------------------------------------------
	*/
	startCommentPos = std::string::npos;
	while (1)
	{
		for (std::size_t i = 1; i < newText.length(); ++i)
		{
			if (startCommentPos == std::string::npos && newText.at(i - 1) == '/' && newText.at(i) == '*')
			{
				startCommentPos = i - 1;
				continue;
			}

			if (endCommentPos == std::string::npos && newText.at(i - 1) == '*' && newText.at(i) == '/')
			{
				endCommentPos = i;
			}
		}

		if (startCommentPos != std::string::npos && endCommentPos != std::string::npos)
		{
			std::size_t charNum = (startCommentPos >= 1) ? startCommentPos : 0;	//	コメントより以前の文字列の文字数
			newText = (newText.substr(0, charNum) + newText.substr(endCommentPos + 1));

			startCommentPos = std::string::npos;
			endCommentPos = std::string::npos;
		}
		else
		{
			//	コメントを削除したテキストを出力
			os << newText;
			return;
		}
	}
}

void copyStream(std::istream& is, std::ostream& os)
{
	char ch;
	while (is.get(ch))
	{
		os.put(ch);
	}
}
