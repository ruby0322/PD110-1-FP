#include "Entity.hpp"

#ifndef PLAYER_HPP
#define PLAYER_HPP

class Player : public Entity
{
public:
	static const float MAX_V;
	static const int MAX_HP = 100;

	Player(const sf::Vector2f& border, std::vector<sf::Texture> frames, int number);
	~Player();

	void reset(const sf::Vector2f& newPos);
	void dealDamage(int damage);

private:
	int hp;
	int number;

	bool pressingW;
	bool pressingA;
	bool pressingS;
	bool pressingD;

	sf::Vector2f border;

	bool rebouncingx;
	bool rebouncingy;

	void checkBorder();
	void control(const sf::Event& event);
	void update(const sf::Event& event, float deltaTime) override;
};


#endif