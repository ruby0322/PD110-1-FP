
#ifndef STATUS_HPP
#define STATUS_HPP

class Status {
private:

	static const int SPEED_UPGRADE_DURATION = 7;
	static const int BULLET_UPGRADE_DURATION = 7;
	static const int HEAL_DURATION = 5;
	static const int RELOAD_DURATION = 1;
	static const float SPEED_UPGRADE_RATE;
	static const float BULLET_UPGRADE_RATE;

	bool speedBoosted;
	bool bulletBoosted;
	bool reloading;
	bool healing;

	float speedUpgradeTimer;
	float bulletUpgradeTimer;
	float reloadingTimer;
	float healingTimer;

public:

	bool pressingW;
	bool pressingA;
	bool pressingS;
	bool pressingD;
	bool pressingV;

	Status();
	~Status();

	void speedUpgrade();
	void bulletUpgrade();
	void reload();
	void heal();
	bool isReloading() const;
	bool isBulletBoosted() const;
	bool isHealing() const;
	bool isSpeedBoosted() const;
	void updateKeys(int number, const sf::Event& event);

	float getDamage(float defaultDamage) const;
	float getVelocity(float defaultVelocity) const;

	void update(float deltaTime);
	void reset();

};

#endif