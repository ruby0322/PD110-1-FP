#include "Entity.hpp"
#include "Generator.hpp"

#ifndef PROJECTILE_HPP
	#define PROJECTILE_HPP

class Projectile : public Entity
{
public:
	static const int BULLET_SIZE = 8;

	static const int TYPE_BLUE_BULLET = 0;
	static const int TYPE_RED_BULLET = 1;
	static const float DEFAULT_VELOCITY;

	Projectile(int type, float damage, const sf::Vector2f& pos, float direction, bool scale);
	~Projectile() override;
	float getDamage() const;
	int getType() const;
	void update(float deltaTime) override;
	void handleEvent(const sf::Event& event) override;

private:
	int type;
	float damage;
};

#endif