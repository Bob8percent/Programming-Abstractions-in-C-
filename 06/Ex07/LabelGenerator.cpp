#include "LabelGenerator.h"
#include <sstream>
#include <iostream>

LabelGenerator::LabelGenerator(const std::string& prefix, int startIdx)
{
	if (startIdx < 0)
	{
		std::cerr << "ERROR : LabelGenerator::LabelGenerator(const std::string& prefix, int startIdx) : "
			<< "startIdxが負になっています" << std::endl;
		std::exit(EXIT_FAILURE);
	}

	mPrefix = prefix;
	mIndex = startIdx;
}

std::string LabelGenerator::nextLabel()
{
	std::ostringstream oss;
	oss << mPrefix << mIndex;
	++mIndex;
	return oss.str();
}
