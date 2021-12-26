#include "Entity.hpp"
#include "Platform/Platform.hpp"

class Map
{
public:
	Map(int);
	~Map();

	void render(sf::RenderWindow&) const;

private:

	int mapSize;
	Tile** map;
};