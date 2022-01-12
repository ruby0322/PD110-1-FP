#include "Box.hpp"

Box::Box(const sf::Vector2f& pos, std::vector<Item*>* items, std::vector<Projectile*>* projectiles, std::vector<Player*>* players) :
	isAlive(true)
{
	this->items = items;
	this->projectiles = projectiles;
	this->players = players;
	hp = Box::MAX_HP;
	texture.loadFromFile("content/Image/Box/box1.png");
	sprite.setTexture(texture);
	sprite.setPosition(pos);
	sprite.scale(Tile::TILE_SIZE / (float)sprite.getTexture()->getSize().x, Tile::TILE_SIZE / (float)sprite.getTexture()->getSize().y);
	sprite.setOrigin(sprite.getTextureRect().width / 2.f, sprite.getTextureRect().height / 2.f);
	collider.setTarget(&sprite);

	containings = Generator::RandIntVec(0, 2, Box::MAX_CONTAINING_CNT);
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

void Box::dropItems()
{
	for (int itemType : containings)
	{
		Item* newItem = new Item(itemType, sprite.getPosition(), players);
		items->push_back(newItem);
	}
}

void Box::dealDamage(float damage)
{
	hp -= damage;
	if (hp <= 0)
	{
		isAlive = false;
		SoundManager::PlaySoundEffect(SoundManager::TYPE_BOX_DESTROYED);
		dropItems();
	}
}

void Box::update()
{
	for (auto& projectile : *projectiles)
		if (projectile->sprite.getGlobalBounds().intersects(sprite.getGlobalBounds()))
		{
			dealDamage(projectile->getDamage());
			projectile->kill();
		}
	for (auto& player : *players)
		collider.checkCollision(player->getCollider(), .7f);
}