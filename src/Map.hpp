#include "Tile.hpp"
#include "Lava.hpp"
#include "Player.hpp"
#include "Item.hpp"
#include "Box.hpp"
#include "Wall.hpp"

#ifndef MAP_HPP
#define MAP_HPP

class Map
{
private:
	std::vector<Tile*> tiles;
	std::vector<Lava*> lavas;
	std::vector<Box*> boxes;
	std::vector<Wall*> walls;

	sf::RenderTexture bufferMap;

	std::vector<Item*>* items;
	std::vector<Projectile*>* projectiles;
	std::vector<Player*>* players;

	void clear();
	void renderBufferMap();

public:
	static const int MAP_SIZE = 30;


	Map();
	~Map();

	void setTargets(std::vector<Item*>* items, std::vector<Projectile*>* projectiles, std::vector<Player*>* players);
	void loadMap(int matrix[Map::MAP_SIZE][Map::MAP_SIZE]);
	void update(float deltaTime);
	void draw(sf::RenderTexture& buffer);
	std::vector<Tile*> getTiles() const;
};

#endif