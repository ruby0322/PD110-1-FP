#include "Tile.hpp"

Tile::Tile(int type, const sf::Vector2f& pos) :
	type(type)
{
	sprite.setPosition(pos);
	switch (type)
	{
		case Tile::TYPE_GRASS:
			texture.loadFromFile("content/Image/Tile/Grass/tile0" + Generator::RandNumStr(0, 61) + ".png");
			break;
		case Tile::TYPE_ROCK:
			texture.loadFromFile("content/Image/Tile/Rock/floor_" + Generator::RandNumStr(1, 9) + ".png");
			break;
		case Tile::TYPE_SPAWNPOINT_ONE:
		case Tile::TYPE_SPAWNPOINT_TWO:
			texture.loadFromFile("content/Image/Tile/rrro_start.png");
			break;
		case Tile::TYPE_PLANK:
			texture.loadFromFile("content/Image/Tile/plank.png");
		default:
			break;
	}
	sprite.setTexture(texture);
	sprite.scale(Tile::TILE_SIZE / (float)sprite.getTexture()->getSize().x, Tile::TILE_SIZE / (float)sprite.getTexture()->getSize().y);
	sprite.setOrigin(sprite.getTextureRect().width / 2.f, sprite.getTextureRect().height / 2.f);
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