#include "Map.hpp"

Map::Map()
{
}

Map::~Map()
{
	size_t tileCnt = tiles.size();
	size_t lavaCnt = lavas.size();
	size_t boxCnt = boxes.size();
	for (size_t i = 0; i < tileCnt; ++i)
		delete[] tiles[i];
	for (size_t i = 0; i < lavaCnt; ++i)
		delete[] lavas[i];
	for (size_t i = 0; i < boxCnt; ++i)
		delete[] boxes[i];
}

void Map::setTargets(std::vector<Item*>* items, std::vector<Projectile*>* projectiles, std::vector<Player*>* players)
{
	this->projectiles = projectiles;
	this->items = items;
	this->players = players;
}

void Map::loadMap(int matrix[Map::MAP_SIZE][Map::MAP_SIZE])
{
	if (!tiles.empty())
		tiles.clear();
	for (int i = 0; i < Map::MAP_SIZE; ++i)
		for (int j = 0; j < Map::MAP_SIZE; ++j)
			if (matrix[i][j] != -1)
			{
				if (matrix[i][j] == Tile::TYPE_LAVA) {
					Tile* tile = new Tile(Tile::TYPE_ROCK, sf::Vector2f(Tile::TILE_SIZE * j, Tile::TILE_SIZE * i));
					tiles.push_back(tile);
					Lava* lava = new Lava(sf::Vector2f(Tile::TILE_SIZE * j, Tile::TILE_SIZE * i));
					lavas.push_back(lava);
				} else if (matrix[i][j] == Tile::TYPE_BOX) {
					Tile* tile = new Tile(Tile::TYPE_ROCK, sf::Vector2f(Tile::TILE_SIZE * j, Tile::TILE_SIZE * i));
					tiles.push_back(tile);
					Box* box = new Box(sf::Vector2f(Tile::TILE_SIZE * j, Tile::TILE_SIZE * i), items, projectiles, players);
					boxes.push_back(box);
				} else {
					Tile* tile = new Tile(matrix[i][j], sf::Vector2f(Tile::TILE_SIZE * j, Tile::TILE_SIZE * i));
					tiles.push_back(tile);
				}
			}

	bufferMap.create(Tile::TILE_SIZE * Map::MAP_SIZE, Tile::TILE_SIZE * Map::MAP_SIZE);
	bufferMap.clear(sf::Color(0, 0, 0, 255));
	for (const auto& tile : tiles)
		tile->draw(bufferMap);
	for (const auto& lava : lavas)
		lava->draw(bufferMap);
	for (const auto& box : boxes)
		box->draw(bufferMap);
	bufferMap.display();
}

void Map::draw(sf::RenderTexture& buffer)
{
	buffer.draw(sf::Sprite(bufferMap.getTexture()));
}

std::vector<Tile*> Map::getTiles() const
{
	return tiles;
}

void Map::update(std::vector<Player*>& players, float deltaTime)
{
	for (auto& lava : lavas)
	{
		lava->update(players, deltaTime);
	}
	for (auto& box : boxes)
		box->update();
}