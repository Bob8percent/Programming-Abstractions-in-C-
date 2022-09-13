#pragma once
#include <string>

class LabelGenerator
{
public:
	LabelGenerator(const std::string& prefix, int startIdx);

	std::string nextLabel();
private:
	std::string mPrefix;
	int mIndex;
};

