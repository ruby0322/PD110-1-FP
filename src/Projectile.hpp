#include "Entity.hpp"

#ifndef PROJECTILE_HPP
#define PROJECTILE_HPP

class Projectile : public Entity
{
public:
	Projectile(const std::vector<sf::Texture>& frames, int type);
	~Projectile();
	int getDamage() const;

private:
	int type;
	int damage;
};

#endif