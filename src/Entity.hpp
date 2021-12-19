#include "Platform/Platform.hpp"
#include <string>

class Entity
{
public:
	Entity(sf::Sprite);
	~Entity();

	sf::Sprite sprite;
	virtual void update(sf::Event);
};

class Player : public Entity
{
public:
	Player(sf::Sprite);
	~Player();

	void update(sf::Event) override;
};