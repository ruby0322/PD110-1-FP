#include "Player.hpp"

const float Player::MAX_V = .5f;

Player::Player(const sf::Vector2f& border, std::vector<sf::Texture> frames, int number) :
	Entity(frames),
	hp(Player::MAX_HP)
{
	pressingW = pressingA = pressingS = pressingD = false;
	this->border = border;
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
	if (pressingA)
		vx -= Player::MAX_V;
	if (pressingD)
		vx += Player::MAX_V;
	if (pressingW)
		vy -= Player::MAX_V;
	if (pressingS)
		vy += Player::MAX_V;
}

void Player::checkBorder()
{
	auto pos = sprite.getPosition();

	if (pos.x < 0)
		sprite.setPosition(0, pos.y);
	if (pos.x > border.x)
		sprite.setPosition(border.x, pos.y);
	pos = sprite.getPosition();
	if (pos.y < 0)
		sprite.setPosition(pos.x, 0);
	if (pos.y > border.y)
		sprite.setPosition(pos.x, border.y);
}

void Player::update(const sf::Event& event, float deltaTime)
{
	control(event);
	if (currTime >= Entity::UPDATE_TIME)
	{
		updateMovement();
		updateFrame();
		currTime -= Entity::UPDATE_TIME;
	}
	checkBorder();
	currTime += deltaTime;
}

void Player::dealDamage(int damage) {
	hp -= damage;
	if (hp <= 0) isAlive = false;
	std::cout << "[Player" << number <<  "] " << "a damage of 5 was dealt, " << hp << " left." << std::endl;
}

void Player::reset(const sf::Vector2f& newPos) {
	hp = Player::MAX_HP;
	sprite.setPosition(newPos);
}