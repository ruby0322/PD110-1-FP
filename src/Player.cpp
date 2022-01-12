#include "Player.hpp"

const float Player::MAX_V = .5f;
const float Player::DRIVING_SOUND_INTERVAL = 1.f;
const float Player::OMEGA = 2.5f;
const float Player::PI = 3.1415926535;

Player::Player(const sf::Vector2f& border, std::vector<sf::Texture> frames, int number) :
	Entity(frames),
	hp(Player::MAX_HP)
{
	direction = 0.f;
	drivingSoundTimer = 0.f;
	pressingW = pressingA = pressingS = pressingD = false;
	this->border = border;
	this->number = number;
	sprite.scale(.06f, .06f);
}

Player::~Player()
{
	std::cout << "[Player] Player" << number << "destructed." << std::endl;
}

bool Player::isDriving() const
{
	return (vx != 0) || (vy != 0);
}

void Player::handleEvent(const sf::Event& event)
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
	float deltaAngle = 0;
	if (pressingA)
	{
		deltaAngle -= Player::OMEGA;
	}
	if (pressingD)
	{
		deltaAngle += Player::OMEGA;
	}
	direction += deltaAngle;
	float angle = direction * (Player::PI / 180);
	if (pressingW)
	{
		vx += MAX_V * sin(angle);
		vy -= MAX_V * cos(angle);
	}
	if (pressingS)
	{
		vx -= MAX_V * sin(angle);
		vy += MAX_V * cos(angle);
	}
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

void Player::update(float deltaTime)
{
	sprite.setRotation(direction);
	if (updateTimer >= Entity::UPDATE_TIME)
	{
		updateMovement();
		updateFrame();
		updateTimer -= Entity::UPDATE_TIME;
	}
	if (isDriving())
	{
		if (drivingSoundTimer >= Player::DRIVING_SOUND_INTERVAL)
		{
			if (number == 1)
			{
				SoundManager::PlaySoundEffect(SoundManager::TYPE_TANK_ONE_DRIVING);
			}
			else
			{
				SoundManager::PlaySoundEffect(SoundManager::TYPE_TANK_TWO_DRIVING);
			}
			drivingSoundTimer -= Player::DRIVING_SOUND_INTERVAL;
		}
	}
	else
	{
		if (number == 1)
		{
			SoundManager::KillSound(SoundManager::TYPE_TANK_ONE_DRIVING);
		}
		else
		{
			SoundManager::KillSound(SoundManager::TYPE_TANK_TWO_DRIVING);
		}
	}
	checkBorder();
	updateTimer += deltaTime;
	drivingSoundTimer += deltaTime;
}

void Player::dealDamage(int damage)
{
	hp -= damage;
	if (hp <= 0) kill();
	std::cout << "[Player" << number << "] "
			  << "a damage of 5 was dealt, " << hp << " left." << std::endl;
}

void Player::reset(const sf::Vector2f& newPos)
{
	hp = Player::MAX_HP;
	direction = 0.f;
	sprite.setRotation(direction);
	sprite.setPosition(newPos);
}

int Player::getNumber() const
{
	return number;
}