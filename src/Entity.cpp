#include "Entity.hpp"
#include <iostream>

Entity::Entity(sf::Sprite sprite) :
	sprite(sprite)
{
}

Entity::~Entity()
{
}

void Entity::update(sf::Event event)
{
	switch (event.type)
	{
		case sf::Event::KeyPressed:
			std::cout << "[Entity] Keypressed detected" << std::endl;
			std::cout << std::flush;
			break;
		default:
			break;
	}
}

Player::Player(sf::Sprite sprite) :
	Entity(sprite)
{
}

Player::~Player()
{
}

void Player::update(sf::Event event)
{
	switch (event.type)
	{
		case sf::Event::KeyPressed:
			switch (event.key.code) {
				case sf::Keyboard::A:
				sprite.move(-5, 0);
				break;
				case sf::Keyboard::D:
				sprite.move(5, 0);
				break;
				case sf::Keyboard::W:
				sprite.move(0, -5);
				break;
				case sf::Keyboard::S:
				sprite.move(0, 5);
				break;
				default:
				break;
			}
			std::cout << "[Player] Keypressed detected" << std::endl;
			std::cout << std::flush;
			break;
		default:
			break;
	}
}