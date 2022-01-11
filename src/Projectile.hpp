#include "Entity.hpp"

#ifndef PROJECTILE_HPP
#define PROJECTILE_HPP

class Projectile : public Entity
{
public:
	Projectile(const std::vector<sf::Texture>& frames, int type);
	~Projectile();

private:
	void checkCollision(Entity& anotherEntity);
	int type;
};

#endif