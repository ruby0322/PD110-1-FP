#include "Entity.hpp"
#include "Player.hpp"
#include "SoundManager.hpp"

#ifndef ITEM_HPP
	#define ITEM_HPP

class Item : public Entity
{
private:
	static const int HEALTH_POTION_HEAL = 50;

	std::vector<Player*>* players;
	int type;

public:
	static const int TYPE_HEALTH_POTION = 0;
	static const int TYPE_SPEED_UPGRADE = 1;
	static const int TYPE_BULLET_UPGRADE = 2;

	Item(int type, const sf::Vector2f& pos, std::vector<Player*>* players);
	~Item() override;

	void handleEvent(const sf::Event& event) override;
	void update(float deltaTime) override;
};

#endif