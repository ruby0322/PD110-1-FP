#include "Wall.hpp"

Wall::Wall(const sf::Vector2f& pos, std::vector<Player*>* players, std::vector<Projectile*>* projectiles)
{
	texture.loadFromFile("content/Image/Tile/Wall/tile00" + Generator::RandNumStr(0, 1) + ".png");
	this->players = players;
	this->projectiles = projectiles;
	sprite.setTexture(texture);
	sprite.setPosition(pos);
	sprite.scale(Tile::TILE_SIZE / (float)sprite.getTexture()->getSize().x, Tile::TILE_SIZE / (float)sprite.getTexture()->getSize().y);
	collider.setTarget(&sprite);
	sprite.setOrigin(sprite.getTextureRect().width / 2.f, sprite.getTextureRect().height / 2.f);
}

Wall::~Wall()
{
}

void Wall::update()
{
	for (auto& player : *players)
	{
		collider.checkCollision(player->getCollider(), 1.f);
	}
	for (auto& projectile : *projectiles)
	{
		if (collider.checkCollision(projectile->getCollider(), 1.f))
		{
			projectile->kill();
		}
	}
}

void Wall::draw(sf::RenderTexture& buffer) const
{
	buffer.draw(sprite);
}