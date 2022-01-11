#include "Platform/Platform.hpp"
#include "Tile.hpp"
#include "Lava.hpp"

class Player;

class Map
{
private:
	static const int MAP_SIZE = 30;
	std::vector<Tile*> tiles;
	std::vector<Lava*> lavas;
	sf::RenderTexture bufferMap;

public:
	Map();
	~Map();

	void loadMap(int matrix[Map::MAP_SIZE][Map::MAP_SIZE]);
	void update(std::vector<Player*>& players);
	void draw(sf::RenderTexture& buffer);
	std::vector<Tile*> getTiles() const;
};