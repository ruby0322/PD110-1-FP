#include "Platform/Platform.hpp"
#include <string>

class Entity
{
public:
	float currFrame;
	int frameCnt;
	float currTime;
	std::vector<sf::Texture> frames;

	sf::Sprite sprite;
	bool isAlive;
	float vx;
	float vy;

	static float UPDATE_TIME;

	Entity(const std::vector<sf::Texture>& frames);
	~Entity();

	bool collidesWith(const Entity& anotherEntity);
	void updateFrame();
	void updateMovement();
	virtual void update(const sf::Event& event, float deltaTime);
	sf::Sprite getSprite() const;
};

class Player : public Entity
{

public:
	static float MAX_V;
	static float UPDATE_TIME;

	Player(int borderx, int bordery, std::vector<sf::Texture> frames, int number);
	~Player();

private:
	int number;

	bool pressingW;
	bool pressingA;
	bool pressingS;
	bool pressingD;

	int borderx;
	int bordery;

	bool rebouncingx;
	bool rebouncingy;

	void checkBorder();
	void control(const sf::Event& event);
	void update(const sf::Event& event, float deltaTime) override;
};

class Item : public Entity
{
	static float UPDATE_TIME;

public:
	Item(int borderx, int bordery, const std::vector<sf::Texture>& frames);
	~Item();

	void reset();
	void update(const sf::Event& event, float deltaTime) override;

	int borderx;
	int bordery;
};

class Projectile : public Entity
{
public:
	Projectile(const std::vector<sf::Texture>& frames, int type);
	~Projectile();

private:
	void checkCollision(Entity& anotherEntity);
	int type;
};
