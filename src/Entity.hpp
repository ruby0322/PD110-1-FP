#include "Platform/Platform.hpp"
#include <string>

class Entity
{
	static float MAX_V;
	static float UPDATE_TIME;
	static float REBOUND_COEFFICIENT;
	static float FRICTION_COEFFICIENT;

public:
	float mass;

	bool Fa;
	bool Fd;
	bool Fw;
	bool Fs;

	bool isAlive;

	float vx;
	float vy;

	float ax;
	float ay;

	float fax;
	float fay;

	float currFrame;
	int frameCnt;
	float currTime;
	sf::Sprite sprite;
	std::vector<sf::Texture> frames;

	Entity(std::vector<sf::Texture>, float);
	~Entity();
	virtual void update(sf::Event, float);
	void updateFrame();
	void updateMovement();
	bool collidesWith(Entity&);
};

class Player : public Entity
{
	static float MAX_V;
	static float A;
	static float UPDATE_TIME;
	static float REBOUND_COEFFICIENT;

public:
	Player(int, int, std::vector<sf::Texture>, float, int);
	~Player();

	void checkRebound();
	void control(sf::Event);
	void update(sf::Event, float) override;

private:
	int number;

	int borderx;
	int bordery;

	bool rebouncingx;
	bool rebouncingy;
};

class Item : public Entity
{
	static float UPDATE_TIME;

public:
	Item(int, int, std::vector<sf::Texture>, float);
	~Item();

	void reset();
	void update(sf::Event, float) override;

	int borderx;
	int bordery;
};

class Tile : public Entity
{
public:
	void render() const;

private:
	int type;
};

class Projectile : public Entity
{
public:
	Projectile(std::vector<sf::Texture> frames, float mass, int type);
	~Projectile();

private:
	void checkCollision(Entity&);
	int type;
};
