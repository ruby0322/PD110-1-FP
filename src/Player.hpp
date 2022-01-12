#include "Entity.hpp"
#include "Generator.hpp"
#include "Projectile.hpp"
#include "SoundManager.hpp"
#include "Status.hpp"

#ifndef PLAYER_HPP
	#define PLAYER_HPP

class Player : public Entity
{
public:
	static const float DEFAULT_VELOCITY;
	static const float DEFAULT_DAMAGE;
	static const float OMEGA;
	static const float DRIVING_SOUND_INTERVAL;
	static const float MAX_HP;

	Status status;

	Player(const sf::Vector2f& border, int number, std::vector<Projectile*>* projectiles);
	~Player() override;

	void reset(const sf::Vector2f& newPos);
	void dealDamage(float damage);
	void heal(float amount);
	int getNumber() const;
	float getHp() const;

	void handleEvent(const sf::Event& event) override;
	void update(float deltaTime) override;

private:
	float direction;
	float drivingSoundTimer;

	float hp;
	int number;

	sf::Vector2f border;

	std::vector<Projectile*>* projectiles;

	void checkBorder();
	bool isDriving() const;
	void shoot();
	void checkProjectiles();
};

#endif