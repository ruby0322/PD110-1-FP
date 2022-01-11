#include "Item.hpp"
#include "Projectile.hpp"
#include "Tile.hpp"
#include "Player.hpp"

#ifndef BOX_HPP
#define BOX_HPP

class Box
{
private:
	static const int MAX_HP = 50;

	int hp;

	std::vector<int> containings;
	sf::Sprite sprite;
	sf::Texture texture;

	std::vector<Item*>* items;
	std::vector<Projectile*>* projectiles;
	std::vector<Player*>* players;

public:

	Box(const sf::Vector2f& pos, std::vector<Item*>* items, std::vector<Projectile*>* projectiles, std::vector<Player*>* players);
	~Box();

	void draw(sf::RenderTexture& bufferMap) const;
	void update();
};

#endif