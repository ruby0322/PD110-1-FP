#include "Platform/Platform.hpp"

class Tile
{
private:
	int type;
	sf::Sprite sprite;
	sf::Texture texture;

public:
	static const int TYPE_GRASS = 0;
	static const int TYPE_ROCK = 1;
	static const int TYPE_WALL = 2;
	static const int TYPE_SPAWNPOINT_ONE = 3;
	static const int TYPE_SPAWNPOINT_TWO = 4;

	static const int TILE_SIZE = 32;


	Tile(int type, const sf::Vector2f& pos);
	~Tile();

	void draw(sf::RenderTexture& bufferMap) const;
};