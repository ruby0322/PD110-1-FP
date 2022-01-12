#include "Projectile.hpp"

Projectile::Projectile(const std::vector<sf::Texture>& frames, int type) :
	Entity(frames),
	type(type)
{
	this->sprite.setPosition(sf::Vector2f(100, 100));
}

Projectile::~Projectile()
{
	std::cout << "[Projectile] Some projectile destructed." << std::endl;
}

int Projectile::getDamage() const
{
	return damage;
}