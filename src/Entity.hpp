#include "Platform/Platform.hpp"

#ifndef ENTITY_HPP
#define ENTITY_HPP

class Entity
{
public:
	static const float UPDATE_TIME;

	float currFrame;
	int frameCnt;
	float currTime;
	std::vector<sf::Texture> frames;

	sf::Sprite sprite;
	bool isAlive;
	float vx;
	float vy;

	Entity(const std::vector<sf::Texture>& frames);
	~Entity();

	bool collidesWith(const Entity& anotherEntity);
	void updateFrame();
	void updateMovement();
	virtual void update(const sf::Event& event, float deltaTime);
};

#endif