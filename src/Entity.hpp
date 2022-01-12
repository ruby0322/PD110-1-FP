#include "Collider.hpp"
#include "Platform/Platform.hpp"

#ifndef ENTITY_HPP
	#define ENTITY_HPP

class Entity
{
private:
	Collider collider;
	bool isAlive;

public:
	static const float UPDATE_TIME;

	int frameCnt;
	float updateTimer;
	float currFrame;
	std::vector<sf::Texture> frames;

	sf::Sprite sprite;
	float vx;
	float vy;

	Entity();
	Entity(const std::vector<sf::Texture>& frames);
	virtual ~Entity();

	bool collidesWith(const Entity& anotherEntity);
	void setFrame(int frameIndex);
	void updateFrame();
	void updateMovement();
	void kill();
	bool isDead() const;
	void resetCenter();

	Collider& getCollider();
	virtual void handleEvent(const sf::Event& event);
	virtual void update(float deltaTime);
};

#endif