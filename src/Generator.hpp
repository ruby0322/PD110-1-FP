#include <random>
#include <string>

#ifndef GENERATOR_HPP
#define GENERATOR_HPP

class Generator {
private:
	Generator();
	~Generator();
public:

	static std::string RandNumStr(int lowerBound, int upperBound);

};

#endif