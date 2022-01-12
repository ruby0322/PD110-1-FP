#include "Collider.hpp"
#include "Item.hpp"
#include "Player.hpp"
#include "Projectile.hpp"
#include "Tile.hpp"

#ifndef BOX_HPP
	#define BOX_HPP

class Box
{
private:
	static const int MAX_HP = 50;

	float hp;

	std::vector<int> containings;
	sf::Texture texture;

	std::vector<Item*>* items;
	std::vector<Projectile*>* projectiles;
	std::vector<Player*>* players;

	Collider collider;

public:
	sf::Sprite sprite;
	Box(const sf::Vector2f& pos, std::vector<Item*>* items, std::vector<Projectile*>* projectiles, std::vector<Player*>* players);
	~Box();

	void draw(sf::RenderTexture& bufferMap) const;
	void update();
	Collider& getCollider();
	void dealDamage(float damage);
	bool isAlive;
};

#endif