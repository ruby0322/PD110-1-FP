#include "Collider.hpp"
#include "Item.hpp"
#include "Player.hpp"
#include "Projectile.hpp"
#include "Tile.hpp"
#include "SoundManager.hpp"

// Marcos / Preprocessor
#ifndef BOX_HPP
	#define BOX_HPP

class Box
{
private:
	static const int MAX_HP = 40;
	static const int MAX_CONTAINING_CNT = 3;

	float hp;

	std::vector<int> containings;
	sf::Texture texture;

	std::vector<Item*>* items;
	std::vector<Projectile*>* projectiles;
	std::vector<Player*>* players;

	Collider collider;

	void dropItems();

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