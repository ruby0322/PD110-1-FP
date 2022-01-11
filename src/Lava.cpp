#include "Lava.hpp"

Lava::Lava(const sf::Vector2f& pos) {
	sprite.setPosition(pos);
}

void Lava::update(std::vector<Player*> players) {
	for (auto& player : players) {
	if (player->sprite.getGlobalBounds().intersects(sprite.getGlobalBounds()))
		player->dealDamage(Lava::DAMAGE);
	}
}