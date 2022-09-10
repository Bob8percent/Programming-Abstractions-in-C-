bool checkBracketing(const std::string& str);

int main()
{
	while (1)
	{
		std::string line = "";
		std::getline(std::cin, line);
		std::cout << std::boolalpha << checkBracketing(line) << std::endl;
	}
}

bool checkBracketing(const std::string& str)
{
	//	()は0, []は1, {}は2という数字に対応させて考える
	const std::string UPPER_BRACKETS = "([{";
	const std::string LOWER_BRACKETS = ")]}";
	const std::size_t NOT_FOUND = std::string::npos;
	Stack<int> brackets;	//	()が0, []が1, {}が2
	for (std::size_t i = 0; i < str.length(); ++i)
	{
		char ch = str.at(i);
		std::size_t uNum = UPPER_BRACKETS.find(ch);
		if (uNum != NOT_FOUND)
		{
			brackets.push(uNum);
			continue;
		}

		std::size_t lowerNum = LOWER_BRACKETS.find(ch);
		if (lowerNum != NOT_FOUND)
		{
			if (brackets.isEmpty() || brackets.pop() != lowerNum)
			{
				return false;
			}
		}
	}

	//	bracketsが空であれば正しくネストされている
	return brackets.isEmpty();
}
