#include "Map.hpp"

Map::Map()
{
	bufferMap.create(Tile::TILE_SIZE * Map::MAP_SIZE, Tile::TILE_SIZE * Map::MAP_SIZE);
}

Map::~Map()
{
	clear();
}

void Map::setTargets(std::vector<Item*>* items, std::vector<Projectile*>* projectiles, std::vector<Player*>* players)
{
	this->projectiles = projectiles;
	this->items = items;
	this->players = players;
}

void Map::clear()
{

	if (!tiles.empty())
	{
		size_t tileCnt = tiles.size();
		for (size_t i = 0; i < tileCnt; ++i)
			delete tiles[i];
		tiles.clear();
	}

	if (!lavas.empty())
	{
		size_t lavaCnt = lavas.size();
		for (size_t i = 0; i < lavaCnt; ++i)
			delete lavas[i];
		lavas.clear();
	}

	if (!boxes.empty())
	{
		size_t boxCnt = boxes.size();
		for (size_t i = 0; i < boxCnt; ++i)
			delete boxes[i];
		boxes.clear();
	}

	if (!walls.empty())
	{
		size_t wallCnt = walls.size();
		for (size_t i = 0; i < wallCnt; ++i)
			delete walls[i];
		walls.clear();
	}
}

void Map::renderBufferMap()
{
	bufferMap.clear(sf::Color(0, 0, 0, 255));
	for (const auto& tile : tiles)
		tile->draw(bufferMap);
	for (const auto& lava : lavas)
		lava->draw(bufferMap);
	for (const auto& box : boxes)
		box->draw(bufferMap);
	for (const auto& wall : walls)
		wall->draw(bufferMap);
	bufferMap.display();
}

void Map::loadMap(int matrix[Map::MAP_SIZE][Map::MAP_SIZE])
{
	clear();
	for (int i = 0; i < Map::MAP_SIZE; ++i)
		for (int j = 0; j < Map::MAP_SIZE; ++j)
			if (matrix[i][j] != -1)
			{
				sf::Vector2f pos(Tile::TILE_SIZE * j + Tile::TILE_SIZE / 2.f, Tile::TILE_SIZE * i + Tile::TILE_SIZE / 2.f);
				if (matrix[i][j] == Tile::TYPE_LAVA)
				{
					Tile* tile = new Tile(Tile::TYPE_ROCK, pos);
					tiles.push_back(tile);
					Lava* lava = new Lava(pos, players, &boxes);
					lavas.push_back(lava);
				}
				else if (matrix[i][j] == Tile::TYPE_BOX)
				{
					Tile* tile = new Tile(Tile::TYPE_ROCK, pos);
					tiles.push_back(tile);
					Box* box = new Box(pos, items, projectiles, players);
					boxes.push_back(box);
				}
				else if (matrix[i][j] == Tile::TYPE_WALL)
				{
					Tile* tile = new Tile(Tile::TYPE_ROCK, pos);
					tiles.push_back(tile);
					Wall* wall = new Wall(pos, players, projectiles);
					walls.push_back(wall);
				}
				else
				{
					Tile* tile = new Tile(matrix[i][j], pos);
					tiles.push_back(tile);
				}
			}
}

void Map::draw(sf::RenderTexture& buffer)
{
	renderBufferMap();
	buffer.draw(sf::Sprite(bufferMap.getTexture()));
}

std::vector<Tile*> Map::getTiles() const
{
	return tiles;
}

void Map::update(float deltaTime)
{
	for (auto& lava : lavas)
		lava->update(deltaTime);

	int boxCnt = boxes.size();
	for (int i = 0; i < boxCnt; ++i) {
		if (boxes[i]->isAlive)
			boxes[i]->update();
		else {
			delete boxes[i];
			boxes.erase(boxes.begin() + i--);
		}
	}

	for (auto& wall : walls)
		wall->update();

	boxCnt = boxes.size();
	for (int i = 0; i < boxCnt; ++i)
	{
		for (int j = 0; j < boxCnt; ++j)
		{
			if (i == j)
				continue;
			boxes[i]->getCollider().checkCollision(boxes[j]->getCollider(), .5f);
		}
	}
}