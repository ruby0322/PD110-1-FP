#include "Platform/Platform.hpp"
#include "Player.hpp"
#include "Tile.hpp"
#include "Box.hpp"

#ifndef LAVA_HPP
#define LAVA_HPP

class Lava {
private:
	static const int DAMAGE = 15;

	sf::Sprite sprite;
	sf::Texture texture;

	float timer1;
	float timer2;

	std::vector<Player*>* players;
	std::vector<Box*>* boxes;

public:

	static const int DAMAGE_INTERVAL = 3;

	Lava(const sf::Vector2f& pos, std::vector<Player*>* players, std::vector<Box*>* boxes);
	~Lava();
	void draw(sf::RenderTexture& bufferMap) const;
	void update(float deltaTime);
};

#endif