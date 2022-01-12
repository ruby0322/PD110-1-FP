#include "Projectile.hpp"

const float Projectile::DEFAULT_VELOCITY = 2.f;

Projectile::Projectile(int type, const sf::Vector2f& pos, float direction) :
	Entity(frames),
	type(type)
{
	sprite.setPosition(pos);
	sprite.setRotation(direction);
	sf::Texture tex;
	switch (type)
	{
		case Projectile::TYPE_BLUE_BULLET:
		tex.loadFromFile("content/Image/Bullet/");
		break;
		case Projectile::TYPE_RED_BULLET:
		tex.loadFromFile("content/Image/Bullet/");
		break;
		default:
		break;
	}
	frames.push_back(tex);
	sprite.setTexture(tex);
	resetCenter();
	float angle = direction * (Generator::PI / 180);
	vx += Projectile::DEFAULT_VELOCITY * sin(angle);
	vy -= Projectile::DEFAULT_VELOCITY * cos(angle);
}

Projectile::~Projectile()
{
	std::cout << "[Projectile] Some projectile destructed." << std::endl;
}

float Projectile::getDamage() const
{
	return damage;
}