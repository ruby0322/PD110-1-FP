#include "Projectile.hpp"

const float Projectile::DEFAULT_VELOCITY = .8f;

Projectile::Projectile(int type, float damage, const sf::Vector2f& pos, float direction, bool scale) :
	Entity(),
	type(type),
	damage(damage)
{
	sprite.setRotation(direction);
	sf::Texture tex;
	switch (type)
	{
		case Projectile::TYPE_BLUE_BULLET:
			tex.loadFromFile("content/Image/Projectile/BlueBullet/bullet_blue_rrro.png");
			break;
		case Projectile::TYPE_RED_BULLET:
			tex.loadFromFile("content/Image/Projectile/RedBullet/bullet_red_rrro.png");
			break;
		default:
			break;
	}
	frames.push_back(tex);
	sprite.setTexture(frames[0]);
	if (scale)
		sprite.scale(1.8f * Projectile::BULLET_SIZE / (float)sprite.getTexture()->getSize().x, 1.8f * Projectile::BULLET_SIZE / (float)sprite.getTexture()->getSize().x);
	else
		sprite.scale(Projectile::BULLET_SIZE / (float)sprite.getTexture()->getSize().x, Projectile::BULLET_SIZE / (float)sprite.getTexture()->getSize().x);
	resetCenter();
	float angle = direction * (Generator::PI / 180);
	vx = Projectile::DEFAULT_VELOCITY * sin(angle);
	vy = -Projectile::DEFAULT_VELOCITY * cos(angle);
	sprite.setPosition(pos.x + 30 * vx, pos.y + 30 * vy);
}

Projectile::~Projectile()
{
	std::cout << "[Projectile] Some projectile destructed." << std::endl;
}

int Projectile::getType() const
{
	return type;
}

float Projectile::getDamage() const
{
	return damage;
}

void Projectile::update(float deltaTime)
{
	updateTimer += deltaTime;
	if (updateTimer >= Entity::UPDATE_TIME)
	{
		updateMovement();
		updateTimer -= Entity::UPDATE_TIME;
	}
}

void Projectile::handleEvent(const sf::Event& event)
{
	switch (event.type)
	{
		default:
			break;
	}
}