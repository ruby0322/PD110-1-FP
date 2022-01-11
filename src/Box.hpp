#include "Item.hpp"
#ifndef BOX_HPP
#define BOX_HPP

class Box
{
private:

	std::vector<Item*>* targetItems;

public:

	Box(std::vector<Item*>* targetItems);
	~Box();
};

#endif
