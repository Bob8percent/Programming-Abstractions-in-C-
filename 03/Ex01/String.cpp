bool endWith(const std::string& str, const std::string& suffix)
{
	if (str.length() < suffix.length())
	{
		return false;
	}

	for (int i = str.length() - 1, j = suffix.length() - 1; j >= 0; --i, --j)
	{
		if (str.at(i) != suffix.at(j))
		{
			return false;
		}
	}

	return true;
}

bool endWith(const std::string& str, const char suffix)
{
	if (str.length() < 1)
	{
		return false;
	}

	return str.at(str.length() - 1) == suffix;
}
