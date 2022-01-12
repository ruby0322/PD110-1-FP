#include "Player.hpp"

const float Player::DEFAULT_VELOCITY = .5f;
const float Player::DEFAULT_DAMAGE = 8.f;
const float Player::MAX_HP = 100.f;
const float Player::DRIVING_SOUND_INTERVAL = 1.f;
const float Player::OMEGA = 2.5f;

Player::Player(const sf::Vector2f& border, int number) :
	Entity(),
	hp(Player::MAX_HP)
{
	direction = 0.f;
	drivingSoundTimer = 0.f;
	this->border = border;
	this->number = number;
	sprite.scale(.06f, .06f);
	sf::Texture tex;
	if (number == 1)
		tex.loadFromFile("content/Image/Tank/blue_tank_small.png");
	else
		tex.loadFromFile("content/Image/Tank/red_tank_small.png");
	frames.push_back(tex);
	sprite.setTexture(tex);
	resetCenter();
}

Player::~Player()
{
	std::cout << "[Player] Player" << number << " destructed." << std::endl;
}

void Player::shoot()
{
	if (number == 1) {
		Projectile* bullet = new Projectile(Projectile::TYPE_BLUE_BULLET, sprite.getPosition(), direction);
		projectiles->push_back(bullet);
	}
	else {
		Projectile* bullet = new Projectile(Projectile::TYPE_RED_BULLET, sprite.getPosition(), direction);
		projectiles->push_back(bullet);
	}
}

bool Player::isDriving() const
{
	return (vx != 0) || (vy != 0);
}

void Player::handleEvent(const sf::Event& event)
{
	status.updateKeys(number, event);
	vx = vy = 0;
	float deltaAngle = 0;

	if (status.pressingA)
		deltaAngle -= Player::OMEGA;
	if (status.pressingD)
		deltaAngle += Player::OMEGA;

	direction += deltaAngle;
	float angle = direction * (Generator::PI / 180);
	if (status.pressingW)
	{
		vx += status.getVelocity(Player::DEFAULT_VELOCITY) * sin(angle);
		vy -= status.getVelocity(Player::DEFAULT_VELOCITY) * cos(angle);
	}
	if (status.pressingS)
	{
		vx -= status.getVelocity(Player::DEFAULT_VELOCITY) * sin(angle);
		vy += status.getVelocity(Player::DEFAULT_VELOCITY) * cos(angle);
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
				SoundManager::PlaySoundEffect(SoundManager::TYPE_TANK_ONE_DRIVING);
			else
				SoundManager::PlaySoundEffect(SoundManager::TYPE_TANK_TWO_DRIVING);
			drivingSoundTimer = 0.f;
		}
	}
	else
	{
		if (number == 1)
			SoundManager::KillSound(SoundManager::TYPE_TANK_ONE_DRIVING);
		else
			SoundManager::KillSound(SoundManager::TYPE_TANK_TWO_DRIVING);
	}
	if (status.pressingV && !status.isReloading())
	{
		// shoot();
		status.reload();
	}

	checkBorder();
	status.update(deltaTime);
	updateTimer += deltaTime;
	drivingSoundTimer += deltaTime;
}

void Player::dealDamage(float damage)
{
	hp -= damage;
	if (hp <= 0)
		kill();
	// std::cout << "[Player" << number << "] "
	// 		  << "a damage of 5 was dealt, " << hp << " left." << std::endl;
}

void Player::heal(float amount)
{
	hp += amount;
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