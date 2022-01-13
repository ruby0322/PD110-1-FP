#include "Entity.hpp"

const float Entity::UPDATE_TIME = .01f;

Entity::Entity(const std::vector<sf::Texture>& frames) :
	isAlive(true)
{
	updateTimer = 0;
	currFrame = 0.f;
	this->frames = std::vector<sf::Texture>(frames);
	frameCnt = frames.size();
	sprite.setTexture(frames[0]);
	sprite.setOrigin(sprite.getTextureRect().width / 2.f, sprite.getTextureRect().height / 2.f);
	collider.setTarget(&sprite);
}

Entity::Entity() :
	isAlive(true)
{
	updateTimer = 0;
	currFrame = 0.f;
	frameCnt = 0;
	collider.setTarget(&sprite);
	resetCenter();
}

Entity::~Entity()
{
}

void Entity::resetCenter()
{
	sprite.setOrigin(sprite.getTextureRect().width / 2.f, sprite.getTextureRect().height / 2.f);
}

bool Entity::isDead() const
{
	return !isAlive;
}

Collider& Entity::getCollider()
{
	return collider;
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

void Entity::update(float deltaTime)
{
	updateTimer += deltaTime;
	if (updateTimer >= Entity::UPDATE_TIME)
		updateTimer -= Entity::UPDATE_TIME;
}

void Entity::handleEvent(const sf::Event& event)
{
	switch (event.type)
	{
		default:
			break;
	}
}

bool Entity::collidesWith(const Entity& anotherEntity)
{
	return this->sprite.getGlobalBounds().intersects(anotherEntity.sprite.getGlobalBounds());
}

void Entity::setFrame(int frameIndex)
{
	sprite.setTexture(frames[frameIndex]);
}

void Entity::kill()
{
	isAlive = false;
}

void Entity::revive()
{
	isAlive = true;
}

void Entity::draw(sf::RenderTexture& buffer) const
{
	buffer.draw(sprite);
}

void Entity::draw(sf::RenderWindow& window) const
{
	window.draw(sprite);
}