#include "Lava.hpp"

Lava::Lava(const sf::Vector2f& pos, std::vector<Player*>* players, std::vector<Box*>* boxes) :
	timer1(0),
	timer2(0)
{
	this->players = players;
	this->boxes = boxes;
	texture.loadFromFile("content/Image/Lava/lava.png");
	sprite.setPosition(pos);
	sprite.setTexture(texture);
	sprite.scale(Tile::TILE_SIZE / (float)sprite.getTexture()->getSize().x, Tile::TILE_SIZE / (float)sprite.getTexture()->getSize().y);
	sprite.setOrigin(sprite.getTextureRect().width / 2.f, sprite.getTextureRect().height / 2.f);
}

Lava::~Lava()
{
}

void Lava::draw(sf::RenderTexture& bufferMap) const
{
	bufferMap.draw(sprite);
}

void Lava::update(float deltaTime)
{
	if ((*players)[0]->sprite.getGlobalBounds().intersects(sprite.getGlobalBounds()))
		timer1 += deltaTime;
	else
		timer1 = 2.99f;
	if ((*players)[1]->sprite.getGlobalBounds().intersects(sprite.getGlobalBounds()))
		timer2 += deltaTime;
	else
		timer2 = 2.99f;

	if (timer1 > Lava::DAMAGE_INTERVAL)
	{
		timer1 -= Lava::DAMAGE_INTERVAL;
		(*players)[0]->dealDamage(Lava::DAMAGE);
		SoundManager::PlaySoundEffect(SoundManager::TYPE_LAVA_TOUCHED);
	}
	if (timer2 > Lava::DAMAGE_INTERVAL)
	{
		timer2 -= Lava::DAMAGE_INTERVAL;
		(*players)[1]->dealDamage(Lava::DAMAGE);
		SoundManager::PlaySoundEffect(SoundManager::TYPE_LAVA_TOUCHED);
	}
	for (auto& box : *boxes)
	{
		if (box->sprite.getGlobalBounds().intersects(sprite.getGlobalBounds()))
			box->dealDamage(Lava::DAMAGE * .01f);
	}
}