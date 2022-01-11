#include "Entity.hpp"

#ifndef ITEM_HPP
#define ITEM_HPP

class Item : public Entity
{
public:
	Item(int borderx, int bordery, const std::vector<sf::Texture>& frames);
	~Item();

	void reset();
	void update(const sf::Event& event, float deltaTime) override;

	int borderx;
	int bordery;
};

#endif