#include "Platform/Platform.hpp"
#include "Player.hpp"

#ifndef LAVA_HPP
#define LAVA_HPP

class Lava {
private:
	static const int DAMAGE = 5;

	sf::Sprite sprite;

public:
	Lava(const sf::Vector2f& pos);
	~Lava();
	void update(std::vector<Player*> players);
};

#endif