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
	std::cout << "[Item] Some item destructed." << std::endl;
}

void Item::handleEvent(const sf::Event& event) {
	switch (event.type)
	{
		default:
			break;
	}
}

void Item::update(float deltaTime)
{
	updateTimer += deltaTime;

	if (updateTimer >= Item::UPDATE_TIME)
	{
		updateFrame();
		updateTimer -= Item::UPDATE_TIME;
	}
}

void Item::reset()
{
	sprite.setPosition(rand() % borderx, rand() % bordery);
}
