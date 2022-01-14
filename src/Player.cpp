#include "Player.hpp"

const float Player::DEFAULT_VELOCITY = .5f;
const float Player::DEFAULT_DAMAGE = 20.f;
const float Player::MAX_HP = 100.f;
const float Player::DRIVING_SOUND_INTERVAL = 1.f;
const float Player::OMEGA = 3.f;
const float Player::HEAL_AMOUT = .032f;

Player::Player(const sf::Vector2f& border, int number, std::vector<Projectile*>* projectiles) :
	Entity(),
	hp(Player::MAX_HP),
	point(0)
{
	this->projectiles = projectiles;
	direction = 0.f;
	drivingSoundTimer = 0.f;
	this->border = border;
	this->number = number;
	sf::Texture tex;
	if (number == 1)
	{
		sprite.scale(.05f, .05f);
		tex.loadFromFile("content/Image/Tank/blue_tank_small.png");
	}
	else
	{
		sprite.scale(.052f, .052f);
		tex.loadFromFile("content/Image/Tank/red_tank_small.png");
	}

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
	if (number == 1)
	{
		Projectile* bullet = new Projectile(Projectile::TYPE_BLUE_BULLET, status.getDamage(Player::DEFAULT_DAMAGE), sprite.getPosition(), direction, status.isBulletBoosted());
		projectiles->push_back(bullet);
	}
	else
	{
		Projectile* bullet = new Projectile(Projectile::TYPE_RED_BULLET, status.getDamage(Player::DEFAULT_DAMAGE), sprite.getPosition(), direction, status.isBulletBoosted());
		projectiles->push_back(bullet);
	}
	SoundManager::PlaySoundEffect(SoundManager::TYPE_FIRE_SHOT);
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

void Player::checkProjectiles()
{
	for (auto& projectile : *projectiles)
	{
		// getCollider().checkCollision(projectile->getCollider(), .95f);
		if (projectile->sprite.getGlobalBounds().intersects(sprite.getGlobalBounds()))
		{

			if (number == 1)
			{
				if (projectile->getType() == Projectile::TYPE_RED_BULLET)
				{
					dealDamage(projectile->getDamage());
					projectile->kill();
					SoundManager::PlaySoundEffect(SoundManager::TYPE_TANK_SHOT);
				}
			}
			else
			{
				if (projectile->getType() == Projectile::TYPE_BLUE_BULLET)
				{
					dealDamage(projectile->getDamage());
					projectile->kill();
					SoundManager::PlaySoundEffect(SoundManager::TYPE_TANK_SHOT);
				}
			}
		}
	}
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
		shoot();
		status.reload();
	}

	checkProjectiles();
	checkBorder();
	status.update(deltaTime);
	updateTimer += deltaTime;
	drivingSoundTimer += deltaTime;
	if (status.isHealing())
		heal(Player::HEAL_AMOUT);
}

void Player::dealDamage(float damage)
{
	hp -= damage;
	if (hp <= 0)
		kill();
}

void Player::heal(float amount)
{
	hp += amount;
	if (hp > 100.f)
		hp = 100.f;
}

float Player::getHp() const
{
	return hp;
}

int Player::getPoint() const
{
	return point;
}

void Player::win()
{
	++point;
}

bool Player::isVictorious() const
{
	return point >= 3;
}

void Player::reset(const sf::Vector2f& newPos)
{
	hp = Player::MAX_HP;
	revive();
	vx = vy = 0;
	direction = 0.f;
	status.reset();
	sprite.setRotation(direction);
	sprite.setPosition(newPos);
}

int Player::getNumber() const
{
	return number;
}

void Player::newGame()
{
	reset(sf::Vector2f(0.f, 0.f));
	point = 0;
}

float Player::getDirection() const
{
	return direction;
}