#include "Item.hpp"

Item::Item(int borderx, int bordery, const std::vector<sf::Texture>& frames) :
	Entity(frames),
	borderx(borderx),
	bordery(bordery)
{
	sprite.setPosition(rand() % borderx, rand() % bordery);
}

Item::~Item()
{
}

void Item::update(const sf::Event& event, float deltaTime)
{
	currTime += deltaTime;
	switch (event.type)
	{
		default:
			break;
	}
	if (currTime >= Item::UPDATE_TIME)
	{
		updateFrame();
		currTime -= Item::UPDATE_TIME;
	}
}

void Item::reset()
{
	sprite.setPosition(rand() % borderx, rand() % bordery);
}
