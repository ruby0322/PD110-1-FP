#include "Generator.hpp"

const float Generator::PI = 3.14159265358979323846264338327950288f;

Generator::Generator()
{
}

Generator::~Generator()
{
}

int Generator::RandInt(int lowerBound, int upperBound) {
	int delta = upperBound - lowerBound + 1;
	return (rand() % delta) + lowerBound;
}

std::string Generator::RandNumStr(int lowerBound, int upperBound)
{
	unsigned digitCnt = std::to_string(upperBound).length();
	std::string str = std::to_string(Generator::RandInt(lowerBound, upperBound));
	while (str.length() < digitCnt)
		str = "0" + str;
	return str;
}

std::vector<int> Generator::RandIntVec(int lowerBound, int upperBound, int maxLen) {
	std::vector<int> randIntVec;
	int randLen = Generator::RandInt(0, maxLen);
	for (int i = 0; i < randLen; ++i)
		randIntVec.push_back(Generator::RandInt(lowerBound, upperBound));
	return randIntVec;
}