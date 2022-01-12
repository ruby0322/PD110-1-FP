#include <random>
#include <string>

#ifndef GENERATOR_HPP
	#define GENERATOR_HPP

class Generator
{
private:
	// Preventing instantiation
	Generator();
	~Generator();

public:
	static const float PI;
	static int RandInt(int lowerBound, int upperBound);
	static std::string RandNumStr(int lowerBound, int upperBound);
	static std::vector<int> RandIntVec(int lowerBound, int upperBound, int maxLen);
};

#endif