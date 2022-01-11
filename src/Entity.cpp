#include "Entity.hpp"

const float Entity::UPDATE_TIME = .01f;

Entity::Entity(const std::vector<sf::Texture>& frames) :
	isAlive(true)
{
	currTime = 0;
	currFrame = 0.f;
	this->frames = std::vector<sf::Texture>(frames);
	frameCnt = frames.size();
	sprite.setTexture(frames[0]);
	sprite.scale(2.f, 2.f);
}

Entity::~Entity()
{
}

void Entity::updateFrame()
{
	currFrame += .2f;
	if (currFrame >= frameCnt)
		currFrame = 0;
	sprite.setTexture(frames[(int)currFrame]);
}

void Entity::updateMovement()
{
	sprite.move(vx, vy);
}

void Entity::update(const sf::Event& event, float deltaTime)
{
	switch (event.type)
	{
		default:
			break;
	}
	currTime += deltaTime;
	if (currTime >= Entity::UPDATE_TIME)
		currTime -= Entity::UPDATE_TIME;
}



bool Entity::collidesWith(const Entity& anotherEntity)
{
	return this->sprite.getGlobalBounds().intersects(anotherEntity.sprite.getGlobalBounds());
}


