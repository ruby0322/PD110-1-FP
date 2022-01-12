#include "Item.hpp"

Item::Item(int type, const sf::Vector2f& pos, std::vector<Player*>* players) :
	Entity(),
	type(type)
{
	this->players = players;
	sprite.setPosition(pos);
	sf::Texture tex;
	switch (type) {
		case Item::TYPE_HEALTH_POTION:
		tex.loadFromFile("content/Image/Item/health_potion.png");
		frames.push_back(tex);
		break;
		case Item::TYPE_BULLET_UPGRADE:
		tex.loadFromFile("content/Image/Item/bullet_upgrade.png");
		frames.push_back(tex);
		break;
		case Item::TYPE_SPEED_UPGRADE:
		tex.loadFromFile("content/Image/Item/speed_upgrade.png");
		frames.push_back(tex);
		break;
		default:
		break;
	}
	sprite.setTexture(frames[0]);
	sprite.scale(.06f, .06f);
}

Item::~Item()
{
	std::cout << "[Item] Some item destructed." << std::endl;
}

void Item::handleEvent(const sf::Event& event) {
	switch (event.type)
	{
		default:
			break;
	}
}

void Item::update(float deltaTime)
{
	updateTimer += deltaTime;
	for (auto& player : *players) {
		if (player->sprite.getGlobalBounds().intersects(sprite.getGlobalBounds())) {
			switch (type) {
				case Item::TYPE_HEALTH_POTION:
				player->status.heal();
				break;
				case Item::TYPE_SPEED_UPGRADE:
				player->status.speedUpgrade();
				break;
				case Item::TYPE_BULLET_UPGRADE:
				player->status.bulletUpgrade();
				break;
				default:
				break;
			}
			SoundManager::PlaySoundEffect(SoundManager::TYPE_ITEM_PICKED);
			kill();
		}
	}

}

