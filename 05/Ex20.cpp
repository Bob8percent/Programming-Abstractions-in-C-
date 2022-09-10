void areaCodeToMap(std::istream& is, Map<int, std::string>& map);
void areaCodeToMap(std::istream& is, Map<std::string, Vector<int>>& map);
std::string findLocation(int areaCode, const Map<int, std::string>& map);
int stringToInteger(const std::string& str);
void promptForOpenFile(std::ifstream& ifs, const std::string& prompt);

int main()
{
	std::ifstream ifs;
	promptForOpenFile(ifs, "ファイル名：");
	Map<int, std::string> map;
	Map<std::string, Vector<int>> rmap;
	areaCodeToMap(ifs, map);

	ifs.clear();	//	eofフラグが立っているときはseekgが実行されない
	ifs.seekg(0, std::ios_base::beg);
	areaCodeToMap(ifs, rmap);

	std::string line = "";
	while (1)
	{
		std::cout << "Area Code または Stateを入力：";
		std::getline(std::cin, line);

		//	Stateが入力された時の処理する
		bool isFound = false;
		if (isalpha(line.at(0)))
		{
			Vector<int> codes = rmap.get(line);
			if (!codes.isEmpty())
			{
				for (int i = 0; i < codes.size(); ++i)
				{
					std::cout << codes[i] << std::endl;
					isFound = true;
				}
			}
		}
		if (isFound)continue;

		//	Codesが入力された時の処理
		std::string location = map.get(stringToInteger(line));
		if (location == "")
		{
			std::cout << "そのようなArea Codeは見つかりません" << std::endl;
		}
		else
		{
			std::cout << location << std::endl;
		}
	}
}

std::string findLocation(int areaCode, const Map<int, std::string>& map)
{
	return map.get(areaCode);
}

void areaCodeToMap(std::istream& is, Map<int, std::string>& map)
{
	std::string line = "";
	while (std::getline(is, line))
	{
		map.put(stringToInteger(line.substr(0, 3)), line.substr(4));
	}
}

void areaCodeToMap(std::istream& is, Map<std::string, Vector<int>>& map)
{
	std::string line = "";
	while (std::getline(is, line))
	{
		map[line.substr(4)] += stringToInteger(line.substr(0, 3));
	}
}

int stringToInteger(const std::string& str)
{
	std::istringstream iss(str);
	int value;
	iss >> value >> std::skipws;
	if (!iss.fail() && iss.eof())
	{
		return value;
	}
	else
	{
		std::cout << "ERROR: int stringToInteger(const std::string& str) : 文字列を整数に変換できません" << std::endl;
		return -1;
	}
}

void promptForOpenFile(std::ifstream& ifs, const std::string& prompt)
{
	while (1)
	{
		std::cout << prompt;
		std::string filename = "";
		std::getline(std::cin, filename);

		ifs.open(filename);
		if (!ifs.fail())
		{
			return;
		}

		ifs.clear();
		std::cout << "ERROR: void promptForOpenFile(std::ifstream& ifs, const std::string& prompt) : "
			<< "ファイルを開けません" << std::endl;
	}
}
