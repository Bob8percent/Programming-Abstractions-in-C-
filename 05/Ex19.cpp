
//  モールス信号の翻訳
std::string morseCodeTranslator(const std::string& str);

int main()
{
	std::string line = "";
	while (1)
	{
		std::cout << "> ";
		std::getline(std::cin, line);
		if (line == "")
		{
			break;
		}

		std::cout << morseCodeTranslator(line) << std::endl;
	}
}

std::string morseCodeTranslator(const std::string& str)
{
	std::string morseCode[26] = {
		".-","-...","-.-.", "-..", ".","..-.","--.","....","..",".---","-.-",".-..","--","-.",
		"---",".--.","--.-",".-.","...","-","..-","...-",".--","-..-","-.--","--.."
	};
	std::string newStr = "";

	//	アルファベットに変換する場合
	char startCh = str.at(0);
	if (startCh == '.' || startCh == '-')
	{
		std::istringstream iss(str);
		while (1)
		{
			std::string morseWord = "";
			iss >> morseWord >> std::skipws;

			for (int i = 0; i < 26; ++i)
			{
				if (morseCode[i] == morseWord)
				{
					newStr += ('A' + i);
					break;
				}
			}

			if (!iss.fail() && iss.eof())
			{
				break;
			}
		}
	}

	//	モールス信号へ変換する場合
	else
	{
		for (std::size_t i = 0; i < str.size(); ++i)
		{
			char lowerCh = tolower(str.at(i));
			if (isalpha(lowerCh))
			{
				newStr += morseCode[lowerCh - 'a'];
			}
			newStr += ' ';
		}
	}

	return newStr;
}
