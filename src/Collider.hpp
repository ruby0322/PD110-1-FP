#include "Platform/Platform.hpp"

#ifndef COLLIDER_HPP
	#define COLLIDER_HPP

class Collider
{
public:
	Collider();
	~Collider();

	void setTarget(sf::Sprite* spritePtr);
	void move(float deltaX, float deltaY);
	sf::Vector2f getPosition() const;
	sf::Vector2f getHalfSize() const;
	bool checkCollision(Collider& other, float push);

private:
	sf::Sprite* targetSprite;
};

#endif