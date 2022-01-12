#include "Entity.hpp"
#include "SoundManager.hpp"

#ifndef PLAYER_HPP
#define PLAYER_HPP

class Player : public Entity
{
public:
	static const float PI;
	static const float MAX_V;
	static const float OMEGA;
	static const float DRIVING_SOUND_INTERVAL;
	static const int MAX_HP = 100;

	Player(const sf::Vector2f& border, std::vector<sf::Texture> frames, int number);
	~Player();

	void reset(const sf::Vector2f& newPos);
	void dealDamage(int damage);
	int getNumber() const;


private:
	float direction;
	float drivingSoundTimer;

	int hp;
	int number;

	bool pressingW;
	bool pressingA;
	bool pressingS;
	bool pressingD;

	sf::Vector2f border;

	void checkBorder();
	void handleEvent(const sf::Event& event) override;
	void update(float deltaTime) override;
	bool isDriving() const;
};


#endif