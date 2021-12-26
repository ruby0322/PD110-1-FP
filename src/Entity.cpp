#include "Entity.hpp"
#include <iostream>
#include <random>

float Entity::UPDATE_TIME = .01f;
float Entity::REBOUND_COEFFICIENT = .9f;
float Entity::FRICTION_COEFFICIENT = .1f;
float Player::UPDATE_TIME = .01f;
float Player::REBOUND_COEFFICIENT = .3f;
float Player::A = .03f;
float Player::MAX_V = 3.8f;
float Entity::MAX_V = 3.8f;
float Item::UPDATE_TIME = .01f;

Entity::Entity(std::vector<sf::Texture> frames, float mass) :
	mass(mass),
	isAlive(true)
{
	fax = fay = ax = ay = vx = vy = 0.f;
	Fa = Fd = Fw = Fs = false;
	currTime = 0;
	currFrame = 0.f;
	this->frames = std::vector<sf::Texture>(frames);
	frameCnt = frames.size();
	sprite.setTexture(frames[currFrame]);
	sprite.scale(2.f, 2.f);
}

Entity::~Entity()
{
}

void Entity::updateFrame()
{
	currFrame += .2f;
	if (currFrame >= frameCnt)
	{
		currFrame = 0;
	}
	sprite.setTexture(frames[(int)(currFrame)]);
}

void Entity::updateMovement()
{
	vx += ax;
	vy += ay;
	if (vx > Entity::MAX_V)
		vx = Entity::MAX_V;
	if (vx < -Entity::MAX_V)
		vx = -Entity::MAX_V;
	if (vy > Entity::MAX_V)
		vy = Entity::MAX_V;
	if (vy < -Entity::MAX_V)
		vy = -Entity::MAX_V;
	// vx += fax;
	// vy += fay;
	sprite.move(vx, vy);
	if (abs(vx) < .0005f)
		vx = 0;
	if (abs(vy) < .0005f)
		vy = 0;
	// if (vx > 0)
	// {
	// 	fax = -Entity::FRICTION_COEFFICIENT * mass;
	// }
	// else if (vx < 0)
	// {
	// 	fax = Entity::FRICTION_COEFFICIENT * mass;
	// } else fax = 0;

	// if (vy > 0)
	// {
	// 	fay = -Entity::FRICTION_COEFFICIENT * mass;
	// }
	// else if (vy < 0)
	// {
	// 	fay = Entity::FRICTION_COEFFICIENT * mass;
	// } else fay = 0;
}

void Entity::update(sf::Event event, float deltaTime)
{
	switch (event.type)
	{
		default:
			break;
	}
	currTime += deltaTime;
	if (currTime >= Entity::UPDATE_TIME)
	{
		currTime -= Entity::UPDATE_TIME;
	}
}

Player::Player(int borderx, int bordery, std::vector<sf::Texture> frames, float mass, int number) :
	Entity(frames, mass)
{
	this->borderx = borderx;
	this->bordery = bordery;
	this->rebouncingx = false;
	this->rebouncingy = false;
	this->number = number;
}

Player::~Player()
{
}

void Player::control(sf::Event event)
{
	if (number == 1)
	{
		switch (event.type)
		{
			case sf::Event::KeyPressed:
				switch (event.key.code)
				{
					case sf::Keyboard::A:
						Fa = true;
						break;
					case sf::Keyboard::D:
						Fd = true;
						break;
					case sf::Keyboard::W:
						Fw = true;
						break;
					case sf::Keyboard::S:
						Fs = true;
						break;
					default:
						break;
				}
				break;
			case sf::Event::KeyReleased:
				switch (event.key.code)
				{
					case sf::Keyboard::A:
						Fa = false;
						break;
					case sf::Keyboard::D:
						Fd = false;
						break;
					case sf::Keyboard::W:
						Fw = false;
						break;
					case sf::Keyboard::S:
						Fs = false;
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
						Fa = true;
						break;
					case sf::Keyboard::Right:
						Fd = true;
						break;
					case sf::Keyboard::Up:
						Fw = true;
						break;
					case sf::Keyboard::Down:
						Fs = true;
						break;
					default:
						break;
				}
				break;
			case sf::Event::KeyReleased:
				switch (event.key.code)
				{
					case sf::Keyboard::Left:
						Fa = false;
						break;
					case sf::Keyboard::Right:
						Fd = false;
						break;
					case sf::Keyboard::Up:
						Fw = false;
						break;
					case sf::Keyboard::Down:
						Fs = false;
						break;

					default:
						break;
				}
				break;
			default:
				break;
		}
	}

	ax = ay = 0;
	if (Fa)
		ax -= Player::A;
	if (Fd)
		ax += Player::A;
	if (Fw)
		ay -= Player::A;
	if (Fs)
		ay += Player::A;
}

void Player::checkRebound()
{
	auto pos = sprite.getPosition();
	if ((pos.x > borderx || pos.x < 0) && !rebouncingx)
	{
		vx = -vx * Player::REBOUND_COEFFICIENT;
		ax = -ax * Player::REBOUND_COEFFICIENT;
		rebouncingx = true;
	}
	else if (0 < pos.x && pos.x < borderx)
	{
		rebouncingx = false;
	}

	if ((pos.y > bordery || pos.y < 0) && !rebouncingy)
	{
		vy = -vy * Player::REBOUND_COEFFICIENT;
		ay = -ay * Player::REBOUND_COEFFICIENT;
		rebouncingy = true;
	}
	else if (0 < pos.y && pos.y < bordery)
	{
		rebouncingy = false;
	}
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

void Player::update(sf::Event event, float deltaTime)
{
	control(event);
	currTime += deltaTime;
	if (currTime >= Player::UPDATE_TIME)
	{
		updateMovement();
		updateFrame();
		currTime -= Player::UPDATE_TIME;
	}
	checkRebound();
}

Item::Item(int borderx, int bordery, std::vector<sf::Texture> frames, float mass) :
	Entity(frames, mass),
	borderx(borderx),
	bordery(bordery)
{
	sprite.setPosition(rand() % borderx, rand() % bordery);
}

Item::~Item()
{
}

void Item::update(sf::Event event, float deltaTime)
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

bool Entity::collidesWith(Entity& entity)
{
	return this->sprite.getGlobalBounds().intersects(entity.sprite.getGlobalBounds());
}

void Item::reset()
{
	sprite.setPosition(rand() % borderx, rand() % bordery);
}

Projectile::Projectile(std::vector<sf::Texture> frames, float mass, int type) :
	Entity(frames, mass),
	type(type)
{
	this->sprite.setPosition(sf::Vector2f(100, 100));
}

Projectile::~Projectile()
{
}

void Projectile::checkCollision(Entity& entity)
{
	if (this->collidesWith(entity))
	{
		isAlive = false;
	}

}
