#include "Collider.hpp"

Collider::Collider()
{
}

Collider::~Collider()
{
}

void Collider::setTarget(sf::Sprite* spritePtr) {
	targetSprite = spritePtr;
}

sf::Vector2f Collider::getPosition() const
{
	return targetSprite->getPosition();
}

sf::Vector2f Collider::getHalfSize() const
{
	sf::IntRect spriteSize = targetSprite->getTextureRect();
	sf::Vector2f spriteScale = targetSprite->getScale();
	return sf::Vector2f(spriteSize.width * spriteScale.x, spriteSize.height * spriteScale.y) / 2.f;
}

void Collider::move(float deltaX, float deltaY)
{
	targetSprite->move(deltaX, deltaY);
}

bool Collider::checkCollision(Collider& other, float push)
{
	sf::Vector2f otherPos = other.getPosition();
	sf::Vector2f otherHalfSize = other.getHalfSize();
	sf::Vector2f thisPos = getPosition();
	sf::Vector2f thisHalfSize = getHalfSize();

	float deltaX = otherPos.x - thisPos.x;
	float deltaY = otherPos.y - thisPos.y;

	float intersectX = abs(deltaX) - (otherHalfSize.x + thisHalfSize.x);
	float intersectY = abs(deltaY) - (otherHalfSize.y + thisHalfSize.y);

	if (intersectX < 0.f && intersectY < 0.f)
	{
		push = std::min(std::max(push, 0.f), 1.f);
		if (intersectX > intersectY)
		{
			if (deltaX > 0.f)
			{
				move(intersectX * (1.f - push), 0.f);
				other.move(-intersectX * push, 0.f);
			}
			else
			{
				move(-intersectX * (1.f - push), 0.f);
				other.move(intersectX * push, 0.f);
			}
		}
		else {
			if (deltaY > 0.f)
			{
				move(0.f, intersectY * (1.f - push));
				other.move(0.f, -intersectY * push);
			}
			else
			{
				move(0.f, -intersectY * (1.f - push));
				other.move(0.f, intersectY * push);
			}
		}
		return true;
	}

	return false;
}