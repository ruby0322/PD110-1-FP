#include "Entity.hpp"
#include "Generator.hpp"

#ifndef PROJECTILE_HPP
#define PROJECTILE_HPP

class Projectile : public Entity
{
public:

	static const int TYPE_BLUE_BULLET = 0;
	static const int TYPE_RED_BULLET = 1;
	static const float DEFAULT_VELOCITY;

	Projectile(int type, const sf::Vector2f& pos, float direction);
	~Projectile();
	float getDamage() const;

private:

	int type;
	float damage;

};

#endif