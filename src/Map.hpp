#include "Platform/Platform.hpp"
#include "Tile.hpp"

class Map
{
private:
	static const int MAP_SIZE = 30;
	std::vector<Tile*> tiles;
	sf::RenderTexture bufferMap;

public:
	Map();
	~Map();

	void loadMap(int matrix[Map::MAP_SIZE][Map::MAP_SIZE]);
	void draw(sf::RenderTexture& buffer);
	std::vector<Tile*> getTiles() const;
};