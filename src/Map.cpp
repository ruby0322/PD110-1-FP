#include "Map.hpp"

Map::Map()
{
}

Map::~Map()
{
}

void Map::loadMap(int matrix[Map::MAP_SIZE][Map::MAP_SIZE])
{
	if (!tiles.empty())
		tiles.clear();
	for (int i = 0; i < Map::MAP_SIZE; ++i)
		for (int j = 0; j < Map::MAP_SIZE; ++j)
			if (matrix[i][j] != -1) {
				Tile* tile = new Tile(matrix[i][j], sf::Vector2f(Tile::TILE_SIZE * j, Tile::TILE_SIZE * i));
				tiles.push_back(tile);
			}

	bufferMap.create(Tile::TILE_SIZE * Map::MAP_SIZE, Tile::TILE_SIZE * Map::MAP_SIZE);
	bufferMap.clear(sf::Color(0, 0, 0, 255));
	for (const auto& tile : tiles)
		tile->draw(bufferMap);
	bufferMap.display();
}

void Map::draw(sf::RenderTexture& buffer)
{
	buffer.draw(sf::Sprite(bufferMap.getTexture()));
}

std::vector<Tile*> Map::getTiles() const {
	return tiles;
}