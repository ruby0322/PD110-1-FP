#include "Platform/Platform.hpp"

#ifndef TILE_HPP
#define TILE_HPP

class Tile
{
private:
	int type;
	sf::Sprite sprite;
	sf::Texture texture;

public:
	static const int TYPE_SPAWNPOINT_ONE = 0;
	static const int TYPE_SPAWNPOINT_TWO = 1;
	static const int TYPE_ROCK = 2;
	static const int TYPE_GRASS = 3;
	static const int TYPE_LAVA = 4;
	static const int TYPE_WALL = 5;
	static const int TYPE_BOX = 6;

	static const int TILE_SIZE = 32;


	Tile(int type, const sf::Vector2f& pos);
	~Tile();

	void draw(sf::RenderTexture& bufferMap) const;

	int getType() const;
	sf::Sprite getSprite() const;
};

#endif