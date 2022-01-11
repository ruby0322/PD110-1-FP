#include "Platform/Platform.hpp"
#include "Player.hpp"
#include "Tile.hpp"

#ifndef LAVA_HPP
#define LAVA_HPP

class Lava {
private:
	static const int DAMAGE = 5;

	sf::Sprite sprite;
	sf::Texture texture;

	float timer1;
	float timer2;

public:

	static const int DAMAGE_INTERVAL = 3;

	Lava(const sf::Vector2f& pos);
	~Lava();
	void draw(sf::RenderTexture& bufferMap) const;
	void update(std::vector<Player*> players, float deltaTime);
};

#endif