#include "Generator.hpp"

Generator::Generator()
{
}

Generator::~Generator()
{
}

std::string Generator::RandNumStr(int lowerBound, int upperBound)
{
	int delta = upperBound - lowerBound + 1;
	unsigned digitCnt = std::to_string(upperBound).length();

	std::string str = std::to_string((rand() % delta) + lowerBound);

	while (str.length() < digitCnt)
		str = "0" + str;
	return str;
}