#include "Projectile.hpp"

Projectile::Projectile(const std::vector<sf::Texture>& frames, int type) :
	Entity(frames),
	type(type)
{
	this->sprite.setPosition(sf::Vector2f(100, 100));
}

Projectile::~Projectile()
{
}

void Projectile::checkCollision(Entity& anotherEntity)
{
	if (collidesWith(anotherEntity))
	{
		isAlive = false;
	}
}
