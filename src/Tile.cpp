#include "Tile.hpp"

Tile::Tile(int type, const sf::Vector2f& pos) :
	type(type)
{
	sprite.setPosition(pos);
	switch (type)
	{
		case Tile::TYPE_GRASS:
			texture.loadFromFile("content/Image/Tile/grass.png");
			break;
		case Tile::TYPE_ROCK:
			texture.loadFromFile("content/Image/Tile/rock.jpg");
			break;
		case Tile::TYPE_WALL:
			texture.loadFromFile("content/Image/Tile/wall.png");
			break;
		case Tile::TYPE_SPAWNPOINT_ONE:
		case Tile::TYPE_SPAWNPOINT_TWO:
			texture.loadFromFile("content/Image/Tile/rrro_start.png");
			break;
		default:
			break;
	}
	sprite.setTexture(texture);
	sprite.scale(Tile::TILE_SIZE / (float)sprite.getTexture()->getSize().x, Tile::TILE_SIZE / (float)sprite.getTexture()->getSize().y);
}

Tile::~Tile()
{
}

void Tile::draw(sf::RenderTexture& bufferMap) const
{
	bufferMap.draw(sprite);
}

int Tile::getType() const
{
	return type;
}

sf::Sprite Tile::getSprite() const
{
	return sprite;
}