#include "Entity.hpp"
#include <iostream>
#include <random>

float Entity::UPDATE_TIME = .01f;
float Player::UPDATE_TIME = .01f;
float Player::MAX_V = .8f;
float Item::UPDATE_TIME = .01f;

Entity::Entity(const std::vector<sf::Texture>& frames) :
	isAlive(true)
{
	currTime = 0;
	currFrame = 0.f;
	this->frames = std::vector<sf::Texture>(frames);
	frameCnt = frames.size();
	sprite.setTexture(frames[0]);
	sprite.scale(2.f, 2.f);
}

Entity::~Entity()
{
}

sf::Sprite Entity::getSprite() const {
	return sprite;
}

void Entity::updateFrame()
{
	currFrame += .2f;
	if (currFrame >= frameCnt)
		currFrame = 0;
	sprite.setTexture(frames[(int)currFrame]);
}

void Entity::updateMovement()
{
	sprite.move(vx, vy);
}

void Entity::update(const sf::Event& event, float deltaTime)
{
	switch (event.type)
	{
		default:
			break;
	}
	currTime += deltaTime;
	if (currTime >= Entity::UPDATE_TIME)
		currTime -= Entity::UPDATE_TIME;
}

Player::Player(int borderx, int bordery, std::vector<sf::Texture> frames, int number) :
	Entity(frames)
{
	pressingW = pressingA = pressingS = pressingD = false;
	this->borderx = borderx;
	this->bordery = bordery;
	this->rebouncingx = false;
	this->rebouncingy = false;
	this->number = number;
	sprite.scale(.3f, .3f);
}

Player::~Player()
{
}

void Player::control(const sf::Event& event)
{
	if (number == 1)
	{
		switch (event.type)
		{
			case sf::Event::KeyPressed:
				switch (event.key.code)
				{
					case sf::Keyboard::A:
						pressingA = true;
						break;
					case sf::Keyboard::D:
						pressingD = true;
						break;
					case sf::Keyboard::W:
						pressingW = true;
						break;
					case sf::Keyboard::S:
						pressingS = true;
						break;
					default:
						break;
				}
				break;
			case sf::Event::KeyReleased:
				switch (event.key.code)
				{
					case sf::Keyboard::A:
						pressingA = false;
						break;
					case sf::Keyboard::D:
						pressingD = false;
						break;
					case sf::Keyboard::W:
						pressingW = false;
						break;
					case sf::Keyboard::S:
						pressingS = false;
						break;
					default:
						break;
				}
				break;
			default:
				break;
		}
	}
	else if (number == 2)
	{
		switch (event.type)
		{
			case sf::Event::KeyPressed:
				switch (event.key.code)
				{
					case sf::Keyboard::Left:
						pressingA = true;
						break;
					case sf::Keyboard::Right:
						pressingD = true;
						break;
					case sf::Keyboard::Up:
						pressingW = true;
						break;
					case sf::Keyboard::Down:
						pressingS = true;
						break;
					default:
						break;
				}
				break;
			case sf::Event::KeyReleased:
				switch (event.key.code)
				{
					case sf::Keyboard::Left:
						pressingA = false;
						break;
					case sf::Keyboard::Right:
						pressingD = false;
						break;
					case sf::Keyboard::Up:
						pressingW = false;
						break;
					case sf::Keyboard::Down:
						pressingS = false;
						break;

					default:
						break;
				}
				break;
			default:
				break;
		}
	}
	vx = vy = 0;
	if (pressingA) vx -= Player::MAX_V;
	if (pressingD) vx += Player::MAX_V;
	if (pressingW) vy -= Player::MAX_V;
	if (pressingS) vy += Player::MAX_V;
}

void Player::checkBorder()
{
	auto pos = sprite.getPosition();

	if (pos.x < 0)
		sprite.setPosition(0, pos.y);
	if (pos.x > borderx)
		sprite.setPosition(borderx, pos.y);
	pos = sprite.getPosition();
	if (pos.y < 0)
		sprite.setPosition(pos.x, 0);
	if (pos.y > bordery)
		sprite.setPosition(pos.x, bordery);
}

void Player::update(const sf::Event& event, float deltaTime)
{
	control(event);
	if (currTime >= Player::UPDATE_TIME)
	{
		updateMovement();
		updateFrame();
		currTime -= Player::UPDATE_TIME;
	}
	checkBorder();
	currTime += deltaTime;
}

Item::Item(int borderx, int bordery, const std::vector<sf::Texture>& frames) :
	Entity(frames),
	borderx(borderx),
	bordery(bordery)
{
	sprite.setPosition(rand() % borderx, rand() % bordery);
}

Item::~Item()
{
}

void Item::update(const sf::Event& event, float deltaTime)
{
	currTime += deltaTime;
	switch (event.type)
	{
		default:
			break;
	}
	if (currTime >= Item::UPDATE_TIME)
	{
		updateFrame();
		currTime -= Item::UPDATE_TIME;
	}
}

bool Entity::collidesWith(const Entity& anotherEntity)
{
	return this->sprite.getGlobalBounds().intersects(anotherEntity.sprite.getGlobalBounds());
}

void Item::reset()
{
	sprite.setPosition(rand() % borderx, rand() % bordery);
}

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
	if (this->collidesWith(anotherEntity))
	{
		isAlive = false;
	}

}
