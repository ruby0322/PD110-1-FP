#include "Box.hpp"

Box::Box(const sf::Vector2f& pos, std::vector<Item*>* items, std::vector<Projectile*>* projectiles, std::vector<Player*>* players)
{
	this->items = items;
	this->projectiles = projectiles;
	this->players = players;
	hp = Box::MAX_HP;
	isAlive = true;
	texture.loadFromFile("content/Image/Box/box1.png");
	sprite.setTexture(texture);
	sprite.setPosition(pos);
	sprite.scale(Tile::TILE_SIZE / (float)sprite.getTexture()->getSize().x, Tile::TILE_SIZE / (float)sprite.getTexture()->getSize().y);
	sprite.setOrigin(sprite.getTextureRect().width / 2.f, sprite.getTextureRect().height / 2.f);
	collider.setTarget(&sprite);
}

Box::~Box()
{
}

Collider& Box::getCollider()
{
	return collider;
}

void Box::draw(sf::RenderTexture& bufferMap) const
{
	bufferMap.draw(sprite);
}

void Box::update()
{
	for (auto& projectile : *projectiles)
	{
		if (projectile->sprite.getGlobalBounds().intersects(sprite.getGlobalBounds()))
		{
			hp -= projectile->getDamage();
			if (hp <= 0)
				break;
		}
	}
	if (hp <= 0)
	{
		isAlive = false;
	}
	for (auto& player : *players) {
		if (collider.checkCollision(player->getCollider(), .8f))
			std::cout << "[Box] Collied with player" << player->getNumber() << std::endl;
	}
}