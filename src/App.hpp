#include "Platform/Platform.hpp"
#include "Entity.hpp"
#include <vector>

class App
{
public:
	void run();
	void init(float, float, const char*);

	App();
	~App();

private:
	util::Platform platform;
	sf::RenderWindow window;
	sf::RenderTexture buffer;

	sf::Clock clock;

	std::vector<Player*> players;
	std::vector<Entity*> entities;
	std::vector<Item*> items;
	std::vector<Projectile*> projectiles;
	std::vector<sf::Text*> texts;

	sf::Font font;
	sf::Text scoreText;

	sf::Sound scoreSound;

	sf::View mainGameView;


	int score;

	void draw();
	void update(sf::Event);
	void updateEntities(sf::Event, float);
};
