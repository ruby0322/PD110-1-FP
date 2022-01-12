#include "Status.hpp"

const float Status::SPEED_UPGRADE_RATE = 1.f;
const float Status::BULLET_UPGRADE_RATE = .8f;

Status::Status()
{
	reset();
}

Status::~Status()
{
}

void Status::speedUpgrade()
{
	speedUpgradeTimer = 0.f;
	speedBoosted = true;
}

void Status::bulletUpgrade()
{
	bulletUpgradeTimer = 0.f;
	bulletBoosted = true;
}

float Status::getDamage(float defaultDamage) const
{
	return defaultDamage + (defaultDamage * Status::BULLET_UPGRADE_RATE * bulletBoosted);
}

float Status::getVelocity(float defaultVelocity) const
{
	return defaultVelocity + (defaultVelocity * Status::SPEED_UPGRADE_RATE * speedBoosted);
}

bool Status::isReloading() const
{
	return reloading;
}

bool Status::isBulletBoosted() const
{
	return bulletBoosted;
}

bool Status::isHealing() const
{
	return healing;
}

bool Status::isSpeedBoosted() const
{
	return speedBoosted;
}

void Status::reload()
{
	reloading = true;
	reloadingTimer = 0.f;
}

void Status::heal()
{
	healing = true;
	healingTimer = 0.f;
}

void Status::update(float deltaTime)
{
	if (speedBoosted)
	{
		speedUpgradeTimer += deltaTime;
		if (speedUpgradeTimer >= Status::SPEED_UPGRADE_DURATION)
		{
			speedBoosted = false;
			speedUpgradeTimer = 0.f;
		}
	}
	if (bulletBoosted)
	{
		bulletUpgradeTimer += deltaTime;
		if (bulletUpgradeTimer >= Status::BULLET_UPGRADE_DURATION)
		{
			bulletBoosted = false;
			bulletUpgradeTimer = 0.f;
		}
	}
	if (reloading)
	{
		reloadingTimer += deltaTime;
		if (reloadingTimer >= Status::RELOAD_DURATION)
		{
			reloading = false;
			reloadingTimer = 0.f;
		}
	}
	if (healing)
	{
		healingTimer += deltaTime;
		if (healingTimer >= Status::HEAL_DURATION)
		{
			healing = false;
			healingTimer = 0.f;
		}
	}
}

void Status::updateKeys(int number, const sf::Event& event)
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
					case sf::Keyboard::V:
						pressingV = true;
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
					case sf::Keyboard::V:
						pressingV = false;
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
					case sf::Keyboard::Slash:
						pressingV = true;
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
					case sf::Keyboard::Slash:
						pressingV = false;
						break;
					default:
						break;
				}
				break;
			default:
				break;
		}
	}
}

void Status::reset()
{
	pressingW = pressingA = pressingS = pressingD = pressingV = false;
	speedBoosted = bulletBoosted = reloading = healing = false;
	speedUpgradeTimer = bulletUpgradeTimer = reloadingTimer = healingTimer = 0.f;
}