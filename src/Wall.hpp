#include "Platform/Platform.hpp"
#include "Collider.hpp"
#include "Player.hpp"
#include "Projectile.hpp"
#include "Generator.hpp"
#include "Tile.hpp"

#ifndef WALL_HPP
#define WALL_HPP

class Wall {
private:

	std::vector<Player*>* players;
	std::vector<Projectile*>* projectiles;

	sf::Sprite sprite;
	sf::Texture texture;

	Collider collider;

public:
	Wall(const sf::Vector2f& pos, std::vector<Player*>* players, std::vector<Projectile*>* projectiles);
	~Wall();

	void update();
	void draw(sf::RenderTexture& buffer) const;
};

#endif